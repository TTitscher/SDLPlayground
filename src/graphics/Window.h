class SDL_Window;
class SDL_Surface;

namespace Graphics
{
class Window
{
public:
    Window(const char* rTitle, int rWidth, int rHeigth);
    ~Window();

    void Update();

private:
    SDL_Window* mWindow;
    SDL_Surface* mSurface;
};
} // namespace Graphics
