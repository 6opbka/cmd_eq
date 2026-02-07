#pragma once
#include<thread>
#include<atomic>
#include "data.h"
#include "ui.h"


class Renderer{
    public:
    Renderer(AudioState& audio_state, AudioControls& audio_controls);
    ~Renderer();

    
    void stop();
    bool is_running() const;
    void update(float time_delta);
    void init();

    
    private:
    bool running = false;
    int frame_num = 0;
    AudioState& audio_state;
    AudioControls& audio_controls;
    void read_audio_state();
    UI ui;

    

    
    void render(float time_delta);
    void read_input();
    
};
