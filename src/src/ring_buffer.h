#pragma once
#include <vector>
#include <atomic>

class RingBuffer
{
private:
    std::vector<float> samples;
    size_t size;
    std::atomic<size_t> write_pos;
public:
    RingBuffer(size_t size);
    ~RingBuffer();
    void push(float sample);
    void get_last(float* out, size_t N);

};

