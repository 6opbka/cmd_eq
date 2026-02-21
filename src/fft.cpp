#include "fft.h"
#include <iostream>
#include <vector>


FFT::FFT(RingBuffer& ring_buffer, DoubleBuffer& double_buffer):
    ring_buffer(ring_buffer),
    double_buffer(double_buffer)
{}

void FFT::init(){
    cfg = kiss_fft_alloc(fft_size,is_inverse_fft,NULL,NULL);
    cx_in = new kiss_fft_cpx[fft_size];
    cx_out = new kiss_fft_cpx[fft_size];
}

void FFT::start(){
    running = true;
    thread_ = std::thread(&FFT::loop,this);
}

void FFT::loop(){
    std::vector<float> buf(fft_size);

    while(running){
        ring_buffer.get_last(buf.data(),fft_size);
        
        // Hann window
        for (int i = 0; i < fft_size; i++)
        {
         float w = 0.5f* (1.0f-cosf(2.0f*M_PI*i/(fft_size-1)));
         buf[i] *= w;
        }

        // Fill the complex part of the cx_in
        for (int i = 0; i < fft_size; i++)
        {
            cx_in[i].r = buf[i];
            cx_in[i].i = 0.0f;

        }


        // Filling double buffer with magnitudes
        kiss_fft(cfg,cx_in,cx_out);
        float* out = double_buffer.write_buffer();
        for (int i = 0; i < fft_size/2; i++)
        {
            float real = cx_out[i].r;
            float img = cx_out[i].i;

            float mag = sqrt((real*real)+(img*img));
            out[i] = mag;

        }
        double_buffer.swap(); // Swapping buffers
        std::this_thread::sleep_for(std::chrono::milliseconds(5)); 
    }

}

void FFT::stop(){
    running = false;

    if (thread_.joinable())
        thread_.join();

    free(cfg);
    delete[] cx_in;
    delete[] cx_out;
}



FFT::~FFT(){
    stop();
}