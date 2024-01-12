#include <SDL2/SDL.h>
#include "window.hpp"
#include "buttons.hpp"
#include "layer.hpp"
#include "application.hpp"
#include "grids.hpp"

int main() {

  Window GameWindow;
  Application App { &GameWindow };
  Layer UI;
  ChannelsGrid Stations { &App, &UI };
  SDL_Event Event;

  while(true) {
    while(SDL_PollEvent(&Event)) {

      if (Event.type == SDL_QUIT) {
        SDL_Quit();
        return 0;
      }

      if (UI.HandleEvent(&Event)) {
        continue;
      }

    }

    GameWindow.RenderFrame();
    SDL_Delay(10);
  }
}

/*
{
  "bitrate":128,
  "changeuuid":"f4e2d3fb-3042-40a1-824d-954a9e87a6c8",
  "clickcount":179,
  "clicktimestamp":"2024-01-07 10:34:38",
  "clicktimestamp_iso8601":"2024-01-07T10:34:38Z",
  "clicktrend":15,
  "codec":"MP3",
  "country":"The Russian Federation",
  "countrycode":"RU",
  "favicon":"http://liveam.tv/img/2494.jpg",
  "geo_lat":null,
  "geo_long":null,
  "has_extended_info":false,
  "hls":0,
  "homepage":"http://www.europaplus.ru/",
  "iso_3166_2":null,
  "language":"",
  "languagecodes":"",
  "lastchangetime":"2022-08-09 05:39:48",
  "lastchangetime_iso8601":"2022-08-09T05:39:48Z",
  "lastcheckok":1,
  "lastcheckoktime":"2024-01-06 19:54:39",
  "lastcheckoktime_iso8601":"2024-01-06T19:54:39Z",
  "lastchecktime":"2024-01-06 19:54:39",
  "lastchecktime_iso8601":"2024-01-06T19:54:39Z",
  "lastlocalchecktime":"2024-01-06 19:54:39",
  "lastlocalchecktime_iso8601":"2024-01-06T19:54:39Z",
  "name":"\tЕвропа Плюс",
  "serveruuid":"21c53694-969a-40c7-8641-10a7cce163f9",
  "ssl_error":0,
  "state":"",
  "stationuuid":"4ba75473-8d53-4a71-b797-9a73798265c4",
  "tags":"",
  "url":"http://ep256.hostingradio.ru:8052/europaplus256.mp3",
  "url_resolved":"http://ep256.hostingradio.ru:8052/europaplus256.mp3",
  "votes":1762
}
*/