#pragma once
#include <SDL2/SDL.h>
#include "window.hpp"
#include "HTTPRequest.hpp"
#include "json.hpp"
#include "buttons.hpp"
#include <iostream>

class Application {
public:
  Application(Window* Window) : mWindow { Window }
  {}

  SDL_Surface* GetWindowSurface() {
    return mWindow->GetSurface();
  }

  void Quit() {
    SDL_Event QuitEvent { SDL_QUIT };
    SDL_PushEvent(&QuitEvent);
  }

private:
  Window* mWindow;
  size_t MaxURLsCount = 30;
};