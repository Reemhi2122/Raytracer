#include <stdio.h>
#include <SDL.h>
#include <ctime>
#include "RayTracer.h"

void CalulateInput(SDL_Event event, Sint32& posX, Sint32& posY, int& curScene, bool& recieveInput) {
	switch (event.key.keysym.sym)
	{
	case SDLK_d:
		posX++;
		break;
	case SDLK_a:
		posX--;
		break;
	case SDLK_w:
		posY++;
		break;
	case SDLK_s:
		posY--;
		break;
	case SDLK_i:
		recieveInput = !recieveInput;
		SDL_SetRelativeMouseMode((SDL_bool)recieveInput);
		break;
	case SDLK_LEFT:
		curScene--;
		break;
	case SDLK_RIGHT:
		curScene++;
		break;
	}	
}

int main(int, char*[]) {
	bool quit = false;
	std::clock_t start;

	SDL_Init(SDL_INIT_VIDEO);

	float aspectRatio = 16.f / 16.f;
	int imageWidth = 512;
	int imageHeight = static_cast<int>(imageWidth / aspectRatio);

	RayTracer rayTracer = RayTracer();
	SDL_Event event;
	SDL_Window* window = SDL_CreateWindow("RayTracing v0.1 Stan Vogels", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, imageWidth, imageHeight, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	bool recieveInput = false;
	SDL_SetRelativeMouseMode(SDL_FALSE);
	rayTracer.Initialize();
	
	while (!quit)
	{
		int curScene = 0;
		Sint32 curX = 0, curY = 0, posX = 0, posY = 0;
		SDL_GetRelativeMouseState(&curX, &curY);

		start = std::clock();
		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
			case SDL_KEYDOWN:
				CalulateInput(event, posX, posY, curScene, recieveInput);
				if(recieveInput || curScene !=0) rayTracer.ResetAccumulator();
				break;
			case SDL_QUIT:
				quit = true;
				break;
			}
		}

		if(recieveInput) rayTracer.CalculateCameraAngle(curX, curY, posX, posY);
		rayTracer.CreateTexture(renderer, std::clock(), curScene);
		printf("ms: %f \n", (std::clock() - (double)start) / (double)(CLOCKS_PER_SEC / 1000));
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}