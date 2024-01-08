#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "buttons.hpp"

class Layer {
public:
  bool HandleEvent(const SDL_Event* Event) {
    for (const auto Handler : Subscribers) {
      if (Handler->HandleEvent(Event)) {
        return true;
      }
    }
    return false;
  }

  void SubscribeToEvents(playRadioButton* Receiver) {
    Subscribers.push_back(Receiver);
  }

private:
  std::vector<playRadioButton*> Subscribers;
};
