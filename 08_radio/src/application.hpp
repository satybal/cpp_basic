#pragma once
#include <SDL2/SDL.h>
#include "window.hpp"
#include "HTTPRequest.hpp"
#include "json.hpp"
#include "buttons.hpp"
// #include "layer.hpp"
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

  void ShowStream(const char* arg) {
    std::cout << arg << std::endl;
  }

  // void fillStationsGrid(Layer &ui) {
  //   auto urls = getDefaultUrls();
  //   auto flag = true;

  //   auto start_x = 250;
  //   auto start_y = 50;

  //   auto iconSize = 100;
  //   auto distance = 100;

  //   while (flag) {
  //     SelectGenreButton 

  //   }
  // }

  nlohmann::json getDefaultUrls() {

    http::Request request{"http://all.api.radio-browser.info/json/stations/bycountry/russia"};
	  const auto response = request.send("GET");

    nlohmann::json m_json = nlohmann::json::parse(std::string{response.body.begin(), response.body.end()});

    nlohmann::json SearchResults;
    for (size_t i = 0; i < MaxURLsCount; ++i) {
      SearchResults.push_back(m_json[i]);
    }

    return SearchResults;
  }

private:
  Window* mWindow;
  size_t MaxURLsCount = 30;
};