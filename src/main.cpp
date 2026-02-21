#include "renderer.h"
#include "audio.h"
#include "data.h"
#include "coordinator.h"
#include "ring_buffer.h"
#include "double_buffer.h"
#include "fft.h"


int main() {
    AudioState audio_state;
    AudioControls audio_controls;
    RingBuffer ring_buffer(4096);
    DoubleBuffer double_buffer;
    

    Renderer renderer(audio_state, audio_controls, double_buffer);
    AudioPlayer audio_player(audio_state, audio_controls, ring_buffer);
    FFT fft(ring_buffer,double_buffer);

    Coordinator coordinator(renderer,audio_player,fft);
    coordinator.loop();

    return 0;
}
