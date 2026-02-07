#include "coordinator.h"
#include<chrono>
#include <iostream>



Coordinator::Coordinator(Renderer& renderer, AudioPlayer& player):
    renderer(renderer),
    player(player)
{
    target_frametime = 1.0/target_fps;
    
}

Coordinator::~Coordinator()
{
}



void Coordinator::loop(){
    renderer.init();
    
    char* path = "shrekophone.mp3";
    player.add_track(path);
    player.init();
    player.start();


    // TODO: 
    // Need to put player into separate thread so that it is not blocking code further down.
    // Add data struct
    // Add sync method



    using clock = std::chrono::steady_clock;
    auto last_time = clock::now();

    // std::cout<<renderer.is_running();
    

    while (renderer.is_running())
    {
        auto frame_start = clock::now();
        double time_delta = std::chrono::duration<double>(frame_start-last_time).count();
        last_time = frame_start;

        renderer.update(time_delta);

        double frame_time = std::chrono::duration<double>(clock::now()-frame_start).count();
        if(frame_time<target_frametime){
            std::this_thread::sleep_for(std::chrono::duration<double>(target_frametime-frame_time));
        }
    }
    

}
