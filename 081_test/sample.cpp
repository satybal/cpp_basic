#include <string.h>

#include <iostream>

#include <curl/curl.h>

#include <SDL2/SDL.h>

std::string sBuffer;

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
{
    sBuffer.append((char*)buffer, size * nmemb);
    return size * nmemb;
}

void SDLAudioCallback(void *data, Uint8 *buffer, int length)
{
    memcpy(buffer, sBuffer.data(), length);
    sBuffer.erase(0, length);    
}

int main() {    
    
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    SDL_Window *window = SDL_CreateWindow("Sample Audio", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);

    SDL_AudioDeviceID device;    

    SDL_AudioSpec wantSpec, haveSpec;

    SDL_zero(wantSpec);    
    wantSpec.freq = 22050;
    wantSpec.format = AUDIO_U8;
    wantSpec.channels = 1;
    wantSpec.samples = 2048;
    wantSpec.callback = SDLAudioCallback;

    device = SDL_OpenAudioDevice(NULL, 0, &wantSpec, &haveSpec, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
    if (device == 0)
    {
        std::cout << "Failed to open audio: " << SDL_GetError() << std::endl;
    }  

    SDL_PauseAudioDevice(device, 0);    

    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();

    if(curl) {

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_URL, "http://ep256.hostingradio.ru:8052/europaplus256.mp3");
        res = curl_easy_perform(curl);
    }

    SDL_Event event;
    bool run = true;
    while(run) {
        while(SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:                 
                    break;
                case SDL_QUIT:
                    run = false;
                    break;
                default:
                    break;
            }
        }    
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}