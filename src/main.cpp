#include "renderer.h"
#include "audio.h"
#include "data.h"
#include "coordinator.h"


int main() {
    AudioState audio_state;
    AudioControls audio_controls;

    Renderer renderer(audio_state,audio_controls);
    AudioPlayer audio_player(audio_state,audio_controls);

    Coordinator coordinator(renderer,audio_player);
    coordinator.loop();

    return 0;
}
