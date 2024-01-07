#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
// #include <curl/curl.h>
//#include <cpr/cpr.h>
#include <thread>
#include "HTTPRequest.hpp"
#include <future>
#include <iostream>
#include "json.hpp"
using json = nlohmann::json;


static const char *MY_COOL_MP3 = "../main_theme.mp3";

// cpr::Response getReq(std::string uri) {
//   return cpr::Get(cpr::Url{uri});
// }

const auto stream() {
    http::Request request{"http://ep256.hostingradio.ru:8052/europaplus256.mp3"};
	return request.send("GET");
}

int main(int argc, char **argv) {
    // CURL *curl = curl_easy_init();

    // if(curl) {
    //     CURLcode res;
    //     curl_easy_setopt(curl, CURLOPT_URL, "http://all.api.radio-browser.info/json/stations/bycountry/russia");
    //     res = curl_easy_perform(curl);
    //     curl
    //     curl_easy_cleanup(curl);
    // }

    int result = 0;
    int flags = MIX_INIT_MP3;

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Failed to init SDL\n");
        exit(1);
    }

    if (flags != (result = Mix_Init(flags))) {
        printf("Could not initialize mixer (result: %d).\n", result);
        printf("Mix_Init: %s\n", Mix_GetError());
        exit(1);
    }

    http::Request request{"http://all.api.radio-browser.info/json/stations/bycountry/russia"};
	const auto response = request.send("GET");
    std::cout << response.status.reason << std::endl;
    auto str = std::string{response.body.begin(), response.body.end()};
    json m_json = json::parse(str);
    

    std::cout << m_json[0] << std::endl;
    std::cout << m_json[1] << std::endl;
    std::cout << m_json[2] << std::endl;
    std::cout << m_json[3] << std::endl;

    return 0;


    std::future<const http::Response> res = std::async(stream);
    SDL_Delay(1000);
    auto resultat = res.get();

    Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024);
    Mix_Music *music = Mix_LoadMUS(MY_COOL_MP3);
    Mix_PlayMusic(music, 0);

    while (!SDL_QuitRequested()) {
        SDL_Delay(1000);
    }

    Mix_FreeMusic(music);
    SDL_Quit();

    return 0;


	// http::Request request{"http://ep256.hostingradio.ru:8052/europaplus256.mp3"};
	// const auto response = request.send("GET");
	//Mix_Music *music = Mix_LoadMUS_RW(request.send("GET"));
	// return 0;
//   cpr::Response r = cpr::Get(cpr::Url{"http://ep256.hostingradio.ru:8052/europaplus256.mp3"});
//   return 0;
// std::thread t(getReq, "http://ep256.hostingradio.ru:8052/europaplus256.mp3");
// std::istream *s = getReq("http://ep256.hostingradio.ru:8052/europaplus256.mp3");

//SDL_RWops *mus = request.send("GET");
// SDL_Delay(1000);

// t.detach();
//   t.
//   SDL_RWops *mus = getReq("http://ep256.hostingradio.ru:8052/europaplus256.mp3");
//   SDL_RWops* SDL_AllocRW(t);

//cpr::Response r = cpr::Get(cpr::Url{"http://ep256.hostingradio.ru:8052/europaplus256.mp3"});
}