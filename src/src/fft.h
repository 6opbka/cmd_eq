#pragma once
#include "kiss_fft.h"   
#include "ring_buffer.h"
#include "double_buffer.h"
#include <thread>

class FFT{

private:
    int fft_size = 1024;
    int is_inverse_fft = 0;
    

    kiss_fft_cfg cfg;
    kiss_fft_cpx* cx_in;
    kiss_fft_cpx* cx_out;

    std::thread thread_;

    RingBuffer& ring_buffer;
    DoubleBuffer& double_buffer;

    


public:

    bool running = false;

    FFT(RingBuffer& ring_buffer, DoubleBuffer& double_buffer);
    
    void start();
    void stop();
    void init();
    void loop();

    ~FFT();
};

