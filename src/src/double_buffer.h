#pragma once
#include <atomic>

class DoubleBuffer
{
private:

    float buffers[2][1024]{};
    std::atomic<int> current{0};
    
public:
    DoubleBuffer();
    ~DoubleBuffer();
    float* write_buffer();
    float* read_buffer();
    void swap();
};

