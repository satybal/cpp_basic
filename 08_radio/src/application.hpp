#pragma once

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

  // void updateChannels(const char* url) {

  // }

private:
  Window* mWindow;
};