#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <iostream>

#include "UVProgress.h"

int main()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Event event;

	SDL_Window* window = SDL_CreateWindow(
		"EQ Test",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		320, 240, 0);

	SDL_Renderer* sdl = SDL_CreateRenderer(window, -1, 0);

	SDL_SetRenderDrawColor(sdl, 0, 0, 0, 0);

	SDL_RenderClear(sdl);

	UIRect rect{ 10, 10, 230, 12 };

	UIRect rect2{ 10, 32, 230, 12 };

	UVProgress<Uint8> level_left(rect, 0, 255, 200, 110);

	UVProgress<Uint8> level_right(rect2, 0, 255, 200, 50);

	do
	{
		auto value_l = rand() % 255;
		auto value_r = rand() % 255;

		auto animated_l = level_left.Get();
		auto animated_r = level_right.Get();

		auto d_l = (value_l - animated_l) / abs(value_l - animated_l);
		auto d_r = (value_r - animated_r) / abs(value_r - animated_r);

		while (true)
		{
			if (animated_l != value_l)
			{
				level_left.Set(animated_l);
				level_left.Draw(sdl);

				animated_l += d_l;
			}

			if (animated_r != value_r)
			{
				level_right.Set(animated_r);
				level_right.Draw(sdl);

				animated_r += d_r;
			}

			if (animated_l == value_l && animated_r == value_r)
			{
				break;
			}

			SDL_RenderPresent(sdl);
			SDL_Delay(5);
		}

		SDL_PollEvent(&event);
		SDL_Delay(50);
	} while (event.type != SDL_QUIT);

	SDL_DestroyRenderer(sdl);

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}
