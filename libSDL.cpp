#include "libSDL.h"
#include <SDL.h>
#include <iostream>

void drawPoint(SDL_Renderer* renderer, int coluna, int linha) {
	SDL_RenderDrawPoint(renderer, coluna, linha);
}


void present(SDL_Renderer* renderer) {
	SDL_RenderPresent(renderer);
}


void drawColor(SDL_Renderer* renderer, int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}


void background(SDL_Renderer* renderer, int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderClear(renderer);
}


void destroy(SDL_Window* window) {
	SDL_Event event;
	bool open = true;

	while (open) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT)
				open = false;
		}

		SDL_UpdateWindowSurface(window);
	}

	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyWindow(window);
	SDL_Quit();
}


void init(SDL_Renderer** renderer, SDL_Window** window, int nCol, int nLin) {
	SDL_Init(SDL_INIT_VIDEO);
	*window = SDL_CreateWindow("SDL2 Pixel Drawing",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, nCol, nLin, 0);
	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForSDLRenderer(*window, *renderer);
	ImGui_ImplSDLRenderer_Init(*renderer);
}
