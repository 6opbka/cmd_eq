#pragma once
#include <vector>
#include <atomic>

class RingBuffer
{
private:
    std::vector<float> samples;
    std::atomic<size_t> write_pos;
    size_t size;
public:
    RingBuffer(size_t size);
    ~RingBuffer();
    void push(float sample);
    void get_last(float* out, size_t N);
    size_t get_current_write_pos();
};

