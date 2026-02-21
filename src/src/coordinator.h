#pragma once
#include "renderer.h"
#include "audio.h"
#include "fft.h"

// This guy should sync the data and do unified ticks. 


class Coordinator
{
private:
    Renderer& renderer;
    AudioPlayer& player;
    FFT& fft;

    int target_fps = 30;
    float target_frametime = 0.0f;

    
public:
    Coordinator(Renderer& renderer, AudioPlayer& player,FFT& fft);
    ~Coordinator();
    void loop();
};