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
    ma_device device;
    ma_decoder decoder;


    float track_length = 0.0f;
    int track_length_frames = 0;

    AudioState& audio_state;
    AudioControls& audio_controls;

    char* file_path;

    std::atomic<bool> running{false};
    std::atomic<int> frame_count{0};
    std::atomic<ma_uint64> played_frames{0};
    std::thread thread_;

    float volume = 1.0f;
    float time_left = 0.0f;
    bool playing = false;
    float cursor_pos = 0.0f;
    

    static void data_callback(ma_device* device, void* output, const void* input, ma_uint32 frameCount);


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
    void on_audio(const float* samples, ma_uint32 frame_count, ma_uint32 frames_read_);
    bool track_ended();
    void update_cursor_pos();
    void update_time_left();

};

// Callback func. Should have this signature


