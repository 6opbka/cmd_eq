#pragma once
#include "miniaudio.h"
#include "data.h"
#include <thread>
#include <atomic>

// Main audio handler class
// Basically a wrapper around miniaudio lib

class AudioPlayer
{
private:
    ma_engine engine;
    ma_sound sound;
    float track_length = 0.0f;

    AudioState& audio_state;
    AudioControls& audio_controls;

    char* file_path;

    std::atomic<bool> running{false};
    std::thread thread_;

    float volume = 1.0f;
    float time_left = 0.0f;
    bool playing = false;

    
    
public:
    AudioPlayer(AudioState& audio_state,AudioControls& audio_controls);
    ~AudioPlayer();
    void process_input();
    void update_state();
    void add_track(char* path);
    void loop();
    void start();
    void stop();
    bool init();
};

