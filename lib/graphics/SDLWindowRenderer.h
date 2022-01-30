class SDLWindowRenderer :
    public SDLRenderer
{
public:
    SDLWindowRenderer(unsigned int, unsigned int, int);

    SDLWindowRenderer(SDL_Window*, int);

    virtual ~SDLWindowRenderer();

private: 
    SDL_Window* _window;
};
