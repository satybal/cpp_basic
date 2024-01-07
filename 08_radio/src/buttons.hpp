#pragma once
#include <SDL2/SDL.h>
#include "application.hpp"

class Button {
public:
  virtual bool HandleEvent(const SDL_Event* Event) {
    return false;
  }
};

class playRadioButton : public Button {
public:
  playRadioButton(Application* App, int x, int y) :
    SDLWindowSurface{App->GetWindowSurface()},
    App{App}, 
    m_x{x}, m_y{y}
  {
    Update();
  }

  bool HandleEvent(const SDL_Event* Event) override {
    if (
      Event->type == SDL_MOUSEBUTTONDOWN &&
      Event->button.button == SDL_BUTTON_LEFT &&
      isHovered
    ) {
// here is button event
      App->Quit();
      // App->ShowStream("http://");
      return true;

    } else if (
      Event->type == SDL_MOUSEMOTION
    ) [[likely]] {

      if (isHovered != IsWithinBounds(
        Event->motion.x, Event->motion.y
      )) {

        isHovered = !isHovered;
        Update();

      }

      return isHovered;
    }    

    return false;  
  }

// private:
  Application* App;

  bool IsWithinBounds(int x, int y) {
    if (x < Rect.x) return false;
    if (x > Rect.x + Rect.w) return false;
    if (y < Rect.y) return false;
    if (y > Rect.y + Rect.h) return false;

    return true;
  }

  void Update() {
    auto [r, g, b, a] { isHovered ? HoverColor : BGColor };
    SDL_FillRect(
      SDLWindowSurface,
      &Rect,
      SDL_MapRGB(SDLWindowSurface->format, r, g, b)
    );

    SDL_FillRect(
      SDLWindowSurface,
      &InnerRect,
      SDL_MapRGB(SDLWindowSurface->format, 21, 42, 61)
    );
  }

  bool isHovered { false };

  int m_x, m_y;
  const int size_x = 100;
  const int size_y = 100;

  SDL_Surface* SDLWindowSurface;
  SDL_Color BGColor { 21, 42, 61, 255 };
  SDL_Color HoverColor { 219, 90, 20, 255 };
  SDL_Rect Rect { m_x, m_y, size_x, size_y };
  SDL_Rect InnerRect { m_x + 5, m_y + 5, size_x - 10, size_y - 10 };

};
