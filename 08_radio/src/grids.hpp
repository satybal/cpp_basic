#pragma once

#include <SDL2/SDL.h>
#include "buttons.hpp"
#include <vector>
#include "application.hpp"
#include "layer.hpp"

class StationsGrid {
public:
    StationsGrid( Application *App, Layer *UI ) : ui{UI}, app{App} {}


    void fill(nlohmann::json &stationsInfo) {
        auto x = start_x;
        auto y = start_y;

        //std::cout << stationsList[0] << std::endl;
        playRadioButton button { app, "some string", x, y };
        ui->SubscribeToEvents(&button);

        playRadioButton button1 { app, "some other string", x + 200, y };
        ui->SubscribeToEvents(&button1);

        // for (auto station: stationsList) {
            // {
            //     playRadioButton button { &app, x, y };
            //     buttons.push_back(button);
            //     ui.SubscribeToEvents(&button);
            // }

            // x += (distance_x + size);
            // if (x >= 800 - size) {
            //     y += (distance_y + size);

            //     if (y >= 600 - size) {
            //         break;
            //     } else {
            //         x = start_x;
            //     }
            // }

        // }
    }

private:
 
    Application *app;
    Layer *ui;
    
    int start_x = 250;
    int start_y = 50;

    int distance_x = 100;
    int distance_y = 50;

    int size = 100;
};

