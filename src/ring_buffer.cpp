#include "ring_buffer.h"


RingBuffer::RingBuffer(size_t):
    samples(size),
    size(size),
    write_pos(0)
{}

RingBuffer::~RingBuffer()
{}

void RingBuffer::push(float sample){
    samples[write_pos%size] = sample;
    write_pos.fetch_add(1);
}

void RingBuffer::get_last(float* out, size_t N){
    size_t pos = write_pos.load();
    for (size_t i = 0; i < N; ++i) {
    out[i] = samples[(pos + size - N + i) % size];
    }
}