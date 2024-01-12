#pragma once
#include <SDL2/SDL.h>
#include "application.hpp"

using RadioStationInfo = std::map<const char*, std::string>;

class Button {
public:
  virtual bool HandleEvent(const SDL_Event* Event) {
    return false;
  }
};

class playRadioButton : public Button {
public:
  playRadioButton() {}
  playRadioButton(Application* App,const RadioStationInfo* Channel, int x, int y) :
    app{App}, 
    SDLWindowSurface{app->GetWindowSurface()},
    channel{Channel},
    m_x{x}, m_y{y}
  {
    Update();
  }

  ~playRadioButton() {}

  bool HandleEvent(const SDL_Event* Event) override {
    if (
      Event->type == SDL_MOUSEBUTTONDOWN &&
      Event->button.button == SDL_BUTTON_LEFT &&
      isHovered
    ) {
      //app->Quit();

      getChannelData();

      return true;

    } else if (Event->type == SDL_MOUSEMOTION) {

      if (isHovered != IsWithinBounds(Event->motion.x, Event->motion.y )) {

        isHovered = !isHovered;
        Update();

      }

      return isHovered;
    }    

    return false;  
  }

  const RadioStationInfo getChannelData() {
    const auto value = *channel;

    for (const auto&[key, val]: value) {
      std::cout << key << ": " << val << std::endl;
    }

    return value;
  }

private:
  Application* app;
  SDL_Surface* SDLWindowSurface;
  const RadioStationInfo *channel;

  int m_x, m_y;
  const int size_x = 90;
  const int size_y = 90;

  SDL_Color BGColor { 21, 42, 61, 255 };
  SDL_Color HoverColor { 219, 90, 20, 255 };
  SDL_Rect Rect { m_x, m_y, size_x, size_y };
  SDL_Rect InnerRect { m_x + 5, m_y + 5, size_x - 10, size_y - 10 };


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

};
