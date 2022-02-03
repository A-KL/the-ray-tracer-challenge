class SDLWindowRenderer :
	public SDLCanvas
{
public:
	SDLWindowRenderer(unsigned int, unsigned int, int);

	SDLWindowRenderer(SDL_Window*, int);

	virtual ~SDLWindowRenderer();

private:
	SDL_Window* _window;
};
