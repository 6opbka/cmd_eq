#include"renderer.h"
#include<ncurses.h>
#include<unistd.h>
#include<string>
#include<iostream>
#include<math.h>

using namespace std;

Renderer::Renderer(AudioState& audio_state, AudioControls& audio_controls, DoubleBuffer& double_buffer):
    audio_state(audio_state),
    audio_controls(audio_controls),
    double_buffer(double_buffer),
    running(true)
{
    ui.enable_debug_mode(true);
    num_bars = 32;
    bar_heights.resize(num_bars);
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
    read_audio_buffer();
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

        // Ugly, but compose frame only reads data and doesn't save the pointer.
        ui.compose_frame(read_audio_buffer().data(),64);


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

std::vector<float> Renderer::read_audio_buffer()
{
    float* magnitude = double_buffer.read_buffer();
    std::vector<float> bands_buf(64);

    int fft_size = 1024;
    int sample_rate = 44100;
    float min_log = log10f(20);
    float max_log = log10f(sample_rate/2);

    for(int b = 0; b < 64; b++){
        float start = powf(10, min_log + (max_log - min_log) * b / 64);
        float end   = powf(10, min_log + (max_log - min_log) * (b+1) / 64);

        int start_bin = start * fft_size / sample_rate;
        int end_bin   = end   * fft_size / sample_rate;

        float sum = 0.0f;
        for(int i = start_bin; i < end_bin; i++)
            sum += magnitude[i];

        bands_buf[b] = sum;
    }

    return bands_buf; // C++11+ RVO / move, копирования почти нет
}



void Renderer::read_input(){
    int ch = getch();
    switch (ch)
    {
    case 'q':
    {
        audio_controls.command.store(AudioCommand::Pause);
        running = false;
        break;
    }
        

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

