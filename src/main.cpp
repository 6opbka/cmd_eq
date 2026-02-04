#include <ncurses.h>
#include <unistd.h>
#include "renderer.h"
#include "audio.h"
#include <thread>
#include <chrono>
#include <string>
#include <iostream>
#include <audio_state.h>
#include <coordinator.h>

using namespace std::chrono_literals;

int main(void) {
    
    Renderer renderer;
    AudioPlayer audio_player;
    Coordinator coordinator(renderer,audio_player);
    coordinator.loop();

    return 0;
}
