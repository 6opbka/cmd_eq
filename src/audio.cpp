#define MINIAUDIO_IMPLEMENTATION

#include "audio.h"
#include <iostream>
#include <thread>

AudioPlayer::AudioPlayer(AudioState& audio_state, AudioControls& audio_controls):
    audio_state(audio_state),
    audio_controls(audio_controls)
{
    if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
    std::cerr << "Failed to init engine\n";
    }
}

AudioPlayer::~AudioPlayer()
{
    stop();
    ma_sound_uninit(&sound);
    ma_engine_uninit(&engine);   
}

bool AudioPlayer::init(){
    if (ma_sound_init_from_file(&engine, file_path, 0, NULL, NULL, &sound) != MA_SUCCESS) {
        std::cerr << "Failed to load sound\n";
        return false;
    }

    if(ma_sound_get_length_in_seconds(&sound,&track_length)){
        std::cerr << "Failed to get the sound time\n";  
        track_length = 0.0f; 
        return false;
    }
    audio_state.time_left.store(track_length);
    audio_state.playing.store(false);
    return true;

}

void AudioPlayer::loop() {
    ma_sound_start(&sound);
    playing = true;

    while (running) {
        float cursor = 0.0f;
        ma_sound_get_cursor_in_seconds(&sound, &cursor);
        time_left = track_length - cursor;

        
        if (!ma_sound_is_playing(&sound) && playing) {
            if (cursor >= track_length - 0.01f) {
                playing = false;
            }
        }

        process_input();
        update_state();

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    update_state();
}

void AudioPlayer::start(){
    running = true;
    thread_ = std::thread(&AudioPlayer::loop,this);
}

void AudioPlayer::stop() {
    running = false;
    if (thread_.joinable())
        thread_.join();
}

void AudioPlayer::add_track(char* path){
    file_path = path;
}   

void AudioPlayer::process_input(){
    AudioCommand cmd = audio_controls.command.exchange(AudioCommand::None);
    switch (cmd)
    {
    case AudioCommand::Pause:
        ma_sound_stop(&sound);
        playing = false;
        break;
    
    case AudioCommand::Play:
        ma_sound_start(&sound);
        playing = true;
        break;

    default:
        break;
    }
    update_state();
}

void AudioPlayer::update_state(){

    audio_state.volume.store(volume);
    audio_state.playing.store(playing);
    audio_state.time_left.store(time_left);
}