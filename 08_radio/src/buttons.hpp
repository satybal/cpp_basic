#pragma once

#include <iostream>

class Button {
public:
  virtual bool HandleEvent(const SDL_Event* Event) {
    return false;
  }
};

// ############################## PLAY BUTTON #############################

using RadioStationInfo = std::map<const char*, std::string>;

class playRadioButton : public Button {
public:
  playRadioButton(Window* Window, const RadioStationInfo* Channel, int x, int y) :
    window{Window}, 
    channel{Channel},
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
  Window* window;
  SDL_Surface* SDLWindowSurface = window->GetSurface();
  const RadioStationInfo *channel;

  int m_x, m_y;
  const int size_x = 90;
  const int size_y = 90;

  SDL_Color BGColor { 176, 176, 130, 255 };
  SDL_Color HoverColor { 194, 194, 145, 255 };
  SDL_Rect Rect { m_x, m_y, size_x, size_y };


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
  }

  bool isHovered { false };

};

// ############################## GENRES BUTTON #############################

using GenreInfo = std::pair<const char*, const char*>;
class ChannelsGrid;

class genreButton : public Button {
public:
  genreButton(Window* Window, const GenreInfo* Genre, ChannelsGrid *Channels, int y) :
    window{Window}, 
    genre{Genre},
    channels{Channels},
    m_y{y}
  {
    Update();
  }

  bool HandleEvent(const SDL_Event* Event) override {
    if (
      Event->type == SDL_MOUSEBUTTONDOWN &&
      Event->button.button == SDL_BUTTON_LEFT &&
      isHovered
    ) {

      getGenreData();
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

  const GenreInfo getGenreData() {
    const auto value = *genre;
    std::cout << value.first << ": " << value.second << std::endl;

    return value;
  }

private:
  Window* window;
  SDL_Surface* SDLWindowSurface = window->GetSurface();
  const GenreInfo *genre;
  ChannelsGrid* channels;

  int m_x = 50;
  int m_y;
  const int size_x = 100;
  const int size_y = 50;

  SDL_Color BGColor { 176, 176, 130, 255 };
  SDL_Color HoverColor { 194, 194, 145, 255 };
  SDL_Rect Rect { m_x, m_y, size_x, size_y };


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
  }

  bool isHovered { false };

};
