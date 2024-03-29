#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <map>
#include <iostream>
#include "window.hpp"
#include "HTTPRequest.hpp"
#include "json.hpp"


using RadioStationInfo = std::map<const char*, std::string>;

class playRadioButton {
public:
  playRadioButton(Window* Window, const RadioStationInfo* Channel, int x, int y) :
    window{Window}, 
    channel{Channel},
    m_x{x}, m_y{y}
  {
    Update();
  }

  bool HandleEvent(const SDL_Event* Event) {
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

class ChannelsGrid {
public:
    ChannelsGrid( Window* Window ) : window{Window} {}

    void fillGrid(const char* url) {
        channels.clear();
        buttons.clear();

        channels = getChannels(url);
        
        auto x = start_x;
        auto y = start_y;

        for (const auto &channel: channels) {
            buttons.push_back({ window, &channel, x, y });

            x += (distance_x + size);
            if (x >= (770 - size)) {
                y += (distance_y + size);

                if (y >= 580 - size) {
                    break;
                } else {
                    x = start_x;
                }
            }
        }
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
    size_t urlsCount = 30;

    std::vector<RadioStationInfo> channels;
    std::vector<playRadioButton> buttons;
    
    int start_x = 220;
    int start_y = 20;

    int distance_x = 20;
    int distance_y = 50;

    int size = 90;

    const std::vector<RadioStationInfo> getChannels(const char* url) {
        http::Request request{url};
        const auto response = request.send("GET");

        nlohmann::json m_json = nlohmann::json::parse(std::string{response.body.begin(), response.body.end()});

        std::vector<RadioStationInfo> results;
        for (size_t i = 0; i < urlsCount; ++i) {
            results.push_back(
                {
                    { "name", m_json[i]["name"].template get<std::string>() },
                    { "url", m_json[i]["url"].template get<std::string>() },
                    { "image", m_json[i]["favicon"].template get<std::string>() }
                } 
            );
        }

        return results;
    }
};
