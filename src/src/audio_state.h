#pragma once
#include<atomic>

struct AudioState
{   
    std::atomic<float> volume {1.0f};
    std::atomic<float> time_left {0.0f};
    std::atomic<bool> playing {false};
};
