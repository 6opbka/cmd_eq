#include"renderer.h"
#include<ncurses.h>
#include<unistd.h>
#include<string>
#include <iostream>

using namespace std;

Renderer::Renderer(AudioState& audio_state, AudioControls& audio_controls):
    audio_state(audio_state),
    audio_controls(audio_controls),
    running(true)
{
    ui.enable_debug_mode(true);
}

Renderer::~Renderer()
{
    stop();
    endwin();
}


void Renderer::stop(){
    running = false;
}

bool Renderer::is_running() const{
    return running;
}

void Renderer::read_audio_state(){


    ui.set_vol(audio_state.volume.load());
    ui.set_time_left(audio_state.time_left.load());
    ui.set_playing(audio_state.playing.load());
    ui.set_cursor_pos(audio_state.cursor_pos.load());
    ui.set_last_sample(audio_state.last_sample.load());
}


void Renderer::update(float time_delta){
    
    read_audio_state();
    render(time_delta);
    read_input();
}

void Renderer::render(float time_delta){
        // std::cout<<"mmm\n";
        erase();

        double fps = (time_delta > 0.0) ? 1.0 / time_delta : 0.0;
        ui.set_fps(fps);
        ui.set_frame_num(frame_num);

        ui.compose_frame();

        frame_num++;
        refresh();
}

void Renderer::init(){
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    // attron(A_ALTCHARSET);
    keypad(stdscr,TRUE);
    nodelay(stdscr, TRUE);
}




void Renderer::read_input(){
    int ch = getch();
    switch (ch)
    {
    case 'q':
        running = false;
        break;

    case ' ':
        {
        bool playing = audio_state.playing.load();
        audio_controls.command.store(
        playing ? AudioCommand::Pause : AudioCommand::Play);
    break;
    }
    
    default:
        break;
    }
}

