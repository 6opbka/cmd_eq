#pragma once
#include<thread>
#include<atomic>
#include "data.h"
#include "ui.h"
#include "double_buffer.h"
#include <vector>


class Renderer{
    public:
    Renderer(AudioState& audio_state, AudioControls& audio_controls,DoubleBuffer& double_buffer);
    ~Renderer();

    
    void stop();
    bool is_running() const;
    void update(float time_delta);
    void init();

    int num_bars = 0;
    std::vector<int> bar_heights;

    
    private:
    bool running = false;
    int frame_num = 0;
    AudioState& audio_state;
    AudioControls& audio_controls;
    DoubleBuffer& double_buffer;

    void read_audio_state();
    std::vector<float> read_audio_buffer();
    UI ui;

    

    
    void render(float time_delta);
    void read_input();
    
};
