#include "graphics/Window.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "graphics/Utils.h"

#include <vector>
#include <boost/polygon/voronoi.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/algorithms/append.hpp>
#include <boost/geometry/algorithms/intersection.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

#include <random>

typedef boost::polygon::point_data<double> VoronoiPoint;

typedef boost::geometry::model::d2::point_xy<double> Point;
typedef boost::geometry::model::polygon<Point> Polygon;


Point PolygonPoint(const boost::polygon::voronoi_vertex<double>* v, VoronoiPoint p1, VoronoiPoint p2, int direction)
{
    if (v)
        return Point(v->x(), v->y());

    constexpr double MagicNumber = 1e4;
    double x = (p1.y() - p2.y()) * direction * MagicNumber;
    double y = (p2.x() - p1.x()) * direction * MagicNumber;
    return Point(x, y);
}

//! @brief transforms a voronoi cell to a polygon
//! @param cell ... voronoi cell
//! @param points ... required for calculating infinite edges
//! @remark the voronoi cell may has infinite edges. They are...
Polygon ToPolygon(const boost::polygon::voronoi_cell<double>& cell, const std::vector<VoronoiPoint>& points)
{
    Polygon p;
    const auto* edge = cell.incident_edge();
    do
    {
        VoronoiPoint vp1 = points[edge->cell()->source_index()];
        VoronoiPoint vp2 = points[edge->twin()->cell()->source_index()];

        boost::geometry::append(p, PolygonPoint(edge->vertex0(), vp1, vp2, -1));
        boost::geometry::append(p, PolygonPoint(edge->vertex1(), vp1, vp2, 1));

        edge = edge->next();

    } while (edge != cell.incident_edge());

    boost::geometry::correct(p);
    return p;
}

Polygon Intersection(Polygon p1, Polygon p2)
{
    std::vector<Polygon> intersection;
    boost::geometry::intersection(p1, p2, intersection);
    if (intersection.size() != 1)
        throw "OMG, should not have happenend. #JFU";
    return intersection[0];
}

std::vector<Polygon> Voronoi(const Polygon& hull, const std::vector<VoronoiPoint>& points)
{
    boost::polygon::voronoi_diagram<double> vd;
    boost::polygon::construct_voronoi(points.begin(), points.end(), &vd);

    std::vector<Polygon> polygons;
    for (const auto& cell : vd.cells())
    {
        Polygon p = ToPolygon(cell, points);
        polygons.push_back(Intersection(p, hull));
    }
    return polygons;
}

void Draw(Graphics::Window& w, const VoronoiPoint& p)
{
    w.DrawCircle(p.x(), p.y(), 2);
}

void Draw(Graphics::Window& w, const Polygon& p)
{
    const auto vertices = p.outer();
    const auto size = vertices.size();
    for (auto i = 0; i < size; ++i)
    {
        int firstI = i;
        int secondI = (i + 1) % size;

        w.DrawLine(vertices[firstI].x(), vertices[firstI].y(), vertices[secondI].x(), vertices[secondI].y());
        w.DrawCircle(vertices[firstI].x(), vertices[firstI].y(), 3);
    }
}


int main(int argc, char *argv[])
{
    int numPoints = 10;
    if (argc == 2)
        numPoints = std::stoi(argv[1]);

    Graphics::Window w("Voronoi", 800, 800);

    Polygon hull;
    boost::geometry::append(hull, Point(100, 100));
    boost::geometry::append(hull, Point(100, 700));
    boost::geometry::append(hull, Point(700, 700));
    boost::geometry::append(hull, Point(700, 100));
    boost::geometry::correct(hull);

    std::mt19937 gen;
    std::uniform_real_distribution<double> doubles(110, 690);
    std::vector<VoronoiPoint> points;
    for (int i = 0; i < numPoints; ++i)
    {
        VoronoiPoint p(doubles(gen), doubles(gen));
        points.push_back(p);
        Draw(w, p);
    }

    auto polygons = Voronoi(hull, points);
    for (const auto& polygon : polygons)
        Draw(w, polygon);

    w.Update();
    Graphics::KeepAlive();
}
