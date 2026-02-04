#define MINIAUDIO_IMPLEMENTATION

#include "audio.h"
#include <iostream>
#include <thread>

AudioPlayer::AudioPlayer()
{
    if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
    std::cerr << "Failed to init engine\n";
    }
}

AudioPlayer::~AudioPlayer()
{
    
    ma_engine_uninit(&engine);
    
}

int AudioPlayer::init(){



    ma_sound sound;
    if (ma_sound_init_from_file(&engine, file_path, 0, NULL, NULL, &sound) != MA_SUCCESS) {
        std::cerr << "Failed to load sound\n";
        ma_engine_uninit(&engine);
        return -1;
    }

    float length = 0.0f;

    if(ma_sound_get_length_in_seconds(&sound,&length)){
        std::cerr << "Failed to get the sound time\n";
        
    }
    // std::cout << "Length: " << length << " sec\n";


    ma_sound_start(&sound);

    // ждём пока звук играет
    while (ma_sound_is_playing(&sound)) {
        std::this_thread::sleep_for(std::chrono::milliseconds((int)length));
    }

    ma_sound_uninit(&sound);
    ma_engine_uninit(&engine);
    return 0;

}

void AudioPlayer::add_track(char* path){
    file_path = path;
}   