class SDL_Window;
class SDL_Renderer;

namespace Graphics
{
class Window
{
public:
    Window(const char* title, int width, int height);
    ~Window();

    void SetColor(unsigned short r, unsigned short g, unsigned short b);

    void DrawLine(double x0, double y0, double x1, double y1);
    
    void DrawPixel(double x, double y);
    
    void DrawCircle(double x, double y, int radius);

    void Update();

private:
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
};
} // namespace Graphics
