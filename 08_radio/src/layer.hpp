#pragma once

#include "buttons.hpp"

class Layer {
public:
  bool HandleEvent(const SDL_Event* Event) {
    for (const auto Handler : PlayButtons) {
      if (Handler->HandleEvent(Event)) {
        return true;
      }
    }

    for (const auto Handler : GenreButtons) {
      if (Handler->HandleEvent(Event)) {
        return true;
      }
    }

    return false;
  }

  void SubscribeToEvents(playRadioButton* Receiver) {
    PlayButtons.push_back(Receiver);
  }

  void SubscribeToEvents(genreButton* Receiver) {
    GenreButtons.push_back(Receiver);
  }

private:
  std::vector<playRadioButton*> PlayButtons;
  std::vector<genreButton*> GenreButtons;
};
