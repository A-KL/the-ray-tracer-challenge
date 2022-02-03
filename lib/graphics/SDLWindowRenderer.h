class SDLWindowRenderer :
	public SDLCanvas
{
public:
	SDLWindowRenderer(const char*, int, int, int);

	SDLWindowRenderer(SDL_Window*, int);

	virtual ~SDLWindowRenderer();

private:
	SDL_Window* _window;
};
