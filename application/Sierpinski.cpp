#include "graphics/Window.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "graphics/Utils.h"
#include <random>
#include <array>

struct Point
{
    long double x;
    long double y;

    void MoveTo(const Point& other)
    {
        x = (x + other.x) / 2.;
        y = (y + other.y) / 2.;
    }
};

constexpr int N = 1000000;

int main()
{
    Graphics::Window w("Voronoi", 1200, 800);
  
    std::array<Point, 3> vertices;
    vertices[0] = Point{0, 800};
    vertices[1] = Point{1200, 800};
    vertices[2] = Point{600, 0};

    // draw vertices
    for (const auto& p : vertices)
        w.DrawPixel(p.x, p.y);

    Point movingPoint({100,100});
    std::mt19937_64 gen;
    std::uniform_int_distribution<> dis(0,2);

    for (int i = 0; i < N; ++i)
    {
        int pointId = dis(gen);
        movingPoint.MoveTo(vertices[pointId]);
        //std::cout << movingPoint.x << " , " << movingPoint.y << "\n";
        w.DrawPixel(movingPoint.x, movingPoint.y);
    }
    w.Update();
    Graphics::KeepAlive();
}
