#define MINIAUDIO_IMPLEMENTATION

#include "audio.h"
#include <iostream>
#include <thread>
#include <cstring>

AudioPlayer::AudioPlayer(AudioState& audio_state, AudioControls& audio_controls):
    audio_state(audio_state),
    audio_controls(audio_controls)
{}

AudioPlayer::~AudioPlayer()
{
    stop();
}

bool AudioPlayer::init(){
    // Decoder init
    if (ma_decoder_init_file(file_path, nullptr, &decoder) != MA_SUCCESS) {
        return false;
    }

    // Device config
    ma_device_config config = ma_device_config_init(ma_device_type_playback);

    config.playback.format   = decoder.outputFormat;
    config.playback.channels = decoder.outputChannels;
    config.sampleRate        = decoder.outputSampleRate;

    config.dataCallback = data_callback;
    config.pUserData    = this;

    if (ma_device_init(nullptr, &config, &device) != MA_SUCCESS) {
        ma_decoder_uninit(&decoder);
        return false;
    }

    ma_uint64 total_frames;
    ma_decoder_get_length_in_pcm_frames(&decoder,&total_frames);
    track_length_frames = total_frames;
    track_length = (float)(total_frames/decoder.outputSampleRate);

    return true;
}

void AudioPlayer::loop() {
    playing = true;

    while (running) {

        update_cursor_pos();
        update_time_left();
        if (track_ended()) {
            playing = false;
        }

        process_input();
        update_state();

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    update_state();
}

void AudioPlayer::start(){
    if(running) return;
    ma_device_start(&device);
    running = true;
    thread_ = std::thread(&AudioPlayer::loop,this);
}

void AudioPlayer::stop() {
    if(!running) return;
    ma_device_stop(&device);
    ma_device_uninit(&device);
    ma_decoder_uninit(&decoder);
    running = false;
}

void AudioPlayer::add_track(char* path){
    file_path = path;
}   

void AudioPlayer::process_input(){
    AudioCommand cmd = audio_controls.command.exchange(AudioCommand::None);
    switch (cmd)
    {
    case AudioCommand::Pause:
        ma_device_stop(&device);
        playing = false;
        break;
    
    case AudioCommand::Play:
        ma_device_start(&device);
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
    audio_state.frame_count.store(frame_count);
    audio_state.cursor_pos.store(cursor_pos);
}

void AudioPlayer::data_callback(
    ma_device* device,
    void* output,
    const void* input,
    ma_uint32 frameCount){

    auto* self = static_cast<AudioPlayer*>(device->pUserData);
    ma_uint64 frames_read_ = 0;
    ma_decoder_read_pcm_frames(&self->decoder,output,frameCount,&frames_read_);
    
    // Filling the remaining space with zeroes
    if(frames_read_<frameCount){
        ma_uint32 channels = self->decoder.outputChannels;
        float* out = static_cast<float*>(output);
        std::memset(out+frames_read_*channels,0,(frameCount-frames_read_)*channels*sizeof(float));
    }

    self->on_audio(static_cast<float*>(output),frameCount,frames_read_);
}

void AudioPlayer::on_audio(const float* samples, ma_uint32 frame_count_, ma_uint32 frames_read_){
    frame_count.store(frame_count_);
    played_frames.fetch_add(frames_read_);
    audio_state.last_sample.store(samples[0]);
}

bool AudioPlayer::track_ended(){

    return played_frames.load()>=track_length_frames;
}

void AudioPlayer::update_cursor_pos(){
    cursor_pos = (float)played_frames.load() / (float)track_length_frames;
}

void AudioPlayer::update_time_left(){
    time_left = (float)(track_length_frames - played_frames.load()) / (float)decoder.outputSampleRate;
}