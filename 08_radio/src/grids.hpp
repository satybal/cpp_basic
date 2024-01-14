#pragma once

#include <SDL2/SDL.h>
#include "buttons.hpp"
#include <vector>
#include "application.hpp"
#include "layer.hpp"

//############################# CHANNELS GRID ###############################

using RadioStationInfo = std::map<const char*, std::string>;

class ChannelsGrid {
public:
    ChannelsGrid( Application *App, Layer *UI ) : app{App}, ui{UI} {
        fillGrid(defaultURL);
    }

    void fillGrid(const char* url) {
        channels = getChannels(url);
        
        auto x = start_x;
        auto y = start_y;

        for (const auto &channel: channels) {
            buttons.push_back({ app, &channel, x, y });

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

        for (auto &button: buttons) {
            ui->SubscribeToEvents(&button);
        }
    }

private:
 
    Application *app;
    Layer *ui;
    std::vector<RadioStationInfo> channels;
    std::vector<playRadioButton> buttons;
    
    int start_x = 220;
    int start_y = 20;

    int distance_x = 20;
    int distance_y = 50;

    int size = 90;

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

//############################# CHANNELS GRID ###############################

using GenreInfo = std::pair<const char*, const char*>;

class GenresGrid {
public:
    GenresGrid( Application *App, Layer *UI ) : app{App}, ui{UI} {
        fillGrid();
    }

    void fillGrid() {
        auto y = start_y;

        for (const auto &genre: genreUrls) {
            buttons.push_back({ app, &genre, y });

            y += (distance_y + size);
        }

        for (auto &button: buttons) {
            ui->SubscribeToEvents(&button);
        }
    }

private:
 
    Application *app;
    Layer *ui;
    std::vector<genreButton> buttons;
    
    int start_x = 50;
    int start_y = 170;

    int distance_y = 40;

    int size = 50;

    const std::vector<std::pair<const char*, const char*>> genreUrls {
        { "Джаз",   "https://nl1.api.radio-browser.info/json/stations/bytag/jaz" },
        { "Рок",    "https://nl1.api.radio-browser.info/json/stations/bytag/rock" },
        { "Попса",  "https://nl1.api.radio-browser.info/json/stations/bytag/pop" },
        { "Релакс", "https://nl1.api.radio-browser.info/json/stations/bytag/relax" }
    };

};

