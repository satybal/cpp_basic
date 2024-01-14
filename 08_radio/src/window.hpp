#pragma once
#include <SDL2/SDL.h>

class Window {
public:
  Window() {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDLWindow = SDL_CreateWindow(
      "onRadio",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      770, 580, 0
    );

    SDLWindowSurface = SDL_GetWindowSurface(SDLWindow);

    Update();
  }

  void Update() {

    SDL_FillRect(
      SDLWindowSurface,
      &GenresRect,
      SDL_MapRGB(SDLWindowSurface->format, 219, 219, 180)
    );

    SDL_FillRect(
      SDLWindowSurface,
      &StationsRect,
      SDL_MapRGB(SDLWindowSurface->format, 247, 247, 200)
    );

  }

  void RenderFrame() {
    SDL_UpdateWindowSurface(SDLWindow);
  }

  SDL_Surface* GetSurface() {
    return SDLWindowSurface;
  }

private:
  SDL_Window* SDLWindow;
  SDL_Surface* SDLWindowSurface;
  SDL_Rect GenresRect { 0, 0, 200, 580 };
  SDL_Rect StationsRect {200, 0, 570, 580 };
};