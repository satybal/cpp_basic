#pragma once

#include <SDL2/SDL.h>
#include "buttons.hpp"
#include <vector>
#include "application.hpp"
#include "layer.hpp"

using RadioStationInfo = std::map<const char*, std::string>;

class ChannelsGrid {
public:
    ChannelsGrid( Application *App, Layer *UI ) : app{App}, ui{UI} {
        channels = getChannels(defaultURL);
        fillGrid();
    }

    void fillGrid() {
        auto x = start_x;
        auto y = start_y;

        playRadioButton button { app, &(channels[0]), x, y };
        ui->SubscribeToEvents(&button);

        playRadioButton button1 { app, &(channels[1]), x+200, y };
        ui->SubscribeToEvents(&button1);

        // playRadioButton button1 { app, "some other string", x + 200, y };
        // ui->SubscribeToEvents(&button1);

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
    std::vector<RadioStationInfo> channels;
    
    int start_x = 250;
    int start_y = 50;

    int distance_x = 100;
    int distance_y = 50;

    int size = 100;

    size_t MaxURLsCount = 30;
    const char* defaultURL = "http://all.api.radio-browser.info/json/stations/bycountry/russia";

    const std::vector<RadioStationInfo> getChannels(const char* url) {

        http::Request request{url};
        const auto response = request.send("GET");

        nlohmann::json m_json = nlohmann::json::parse(std::string{response.body.begin(), response.body.end()});

        std::vector<RadioStationInfo> results;
        for (size_t i = 0; i < MaxURLsCount; ++i) {
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

