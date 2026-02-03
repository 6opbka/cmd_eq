#pragma once
#include "miniaudio.h"

// Main audio handler class
// Basically a wrapper around miniaudio lib

class AudioPlayer
{
private:
    ma_engine engine;
    char* file_path;
public:
    AudioPlayer();
    ~AudioPlayer();
    void add_track(char* path);
    int init();

    
};

