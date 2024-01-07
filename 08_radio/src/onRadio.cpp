#include <SDL2/SDL.h>
//#include <iostream>
#include "window.hpp"

#include "buttons.hpp"
#include "layer.hpp"
#include "application.hpp"
// #include "grids.hpp"

int main() {
  //SDL_Init(SDL_INIT_EVERYTHING);

  Window GameWindow;
  Application App { &GameWindow };
  Layer UI;
  // StationsGrid Stations;

  // nlohmann::json stationsInfo = App.getDefaultUrls();
  // Stations.fill(stationsInfo, App, UI);

  //Layer World;
  playRadioButton first_button { &App, 50, 50 };
  // UI.SubscribeToEvents(&first_button);
  // playRadioButton first_button;
  UI.SubscribeToEvents(&first_button);

  // Button second_button { &App, 200, 50 };
  // UI.SubscribeToEvents(&second_button);

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

      // if (World.HandleEvent(&Event)) {
      //   continue;
      // }
    }

    GameWindow.RenderFrame();
    //SDL_Delay(10);
  }
}