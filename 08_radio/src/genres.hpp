#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <map>
#include <iostream>

#include "window.hpp"
#include "channels.hpp"


using GenreInfo = std::pair<const char*, const char*>;

class genreButton {
public:
  genreButton(Window* Window, const GenreInfo* Genre, ChannelsGrid *Channels, int y) :
    window{Window}, 
    genre{Genre},
    channels{Channels},
    m_y{y}
  {
    Update();
  }

  bool HandleEvent(const SDL_Event* Event) {
    if (
      Event->type == SDL_MOUSEBUTTONDOWN &&
      Event->button.button == SDL_BUTTON_LEFT &&
      isHovered
    ) {

      channels->fillGrid(getGenreData().second);

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
class GenresGrid {
public:
    GenresGrid( Window* Window, ChannelsGrid* Channels ) : 
        window{Window},
        channels{Channels} 
    {
        fillGrid();
        channels->fillGrid(defaultURL);
    }

    void fillGrid() {
        auto y = start_y;

        for (const auto &genre: genreUrls) {
            buttons.push_back({ window, &genre, channels, y });

            y += (distance_y + size);
        }

        // for (auto &button: buttons) {
        //     ui->SubscribeToEvents(&button);
        // }

        // channels->fillGrid(defaultURL);
    }

    bool HandleEvent(const SDL_Event* Event) {
        for (auto &button : buttons) {
            auto but = &button;

            if (but->HandleEvent(Event)) {
                return true;
            }
        }

        return false;
    }

private:
 
    Window* window;
    ChannelsGrid* channels;
    std::vector<genreButton> buttons;
    
    int start_x = 50;
    int start_y = 170;

    int distance_y = 40;

    int size = 50;
    const char* defaultURL = "http://all.api.radio-browser.info/json/stations/bycountry/russia";


    const std::vector<std::pair<const char*, const char*>> genreUrls {
        { "Джаз",   "http://nl1.api.radio-browser.info/json/stations/bytag/jaz" },
        { "Рок",    "http://nl1.api.radio-browser.info/json/stations/bytag/rock" },
        { "Попса",  "http://nl1.api.radio-browser.info/json/stations/bytag/pop" },
        { "Релакс", "http://nl1.api.radio-browser.info/json/stations/bytag/relax" }
    };

};
