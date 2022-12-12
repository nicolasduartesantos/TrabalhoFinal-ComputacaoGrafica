#pragma once

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"
#include <SDL.h>

void drawPoint(SDL_Renderer* renderer, int coluna, int linha);

void present(SDL_Renderer* renderer);

void drawColor(SDL_Renderer* renderer, int r, int g, int b, int a);

void background(SDL_Renderer* renderer, int r, int g, int b, int a);

void destroy(SDL_Window* window);

void init(SDL_Renderer** renderer, SDL_Window** window, int nCol, int nLin);
