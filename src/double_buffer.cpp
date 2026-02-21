#include "double_buffer.h"


DoubleBuffer::DoubleBuffer()
{
}

DoubleBuffer::~DoubleBuffer()
{
}


float* DoubleBuffer::write_buffer()
{
    return buffers[1 - current.load(std::memory_order_relaxed)];
}

float* DoubleBuffer::read_buffer()
{
    return buffers[current.load(std::memory_order_acquire)];
}

void DoubleBuffer::swap()
{
    int next = 1 - current.load(std::memory_order_relaxed);
    current.store(next, std::memory_order_release);
}