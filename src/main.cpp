#include <ncurses.h>
#include <unistd.h>
#include "src/renderer.h"
#include "src/audio.h"
#include <thread>
#include <chrono>
#include <string>
#include <iostream>

using namespace std::chrono_literals;

int main(void) {
    Renderer renderer;
    AudioPlayer audio_player;

    renderer.start();
    char* path = "shrekophone.mp3";
    audio_player.add_track(path);
    audio_player.init();

    while (renderer.is_running())
    {
        std::this_thread::sleep_for(100ms);
    }




    return 0;
}
