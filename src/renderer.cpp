#include"src/renderer.h"
#include<ncurses.h>
#include<unistd.h>
#include<string>
#include<chrono>

using namespace std;

Renderer::Renderer(/* args */)
{
    target_frametime = 1/(float)target_fps;
}

Renderer::~Renderer()
{
    stop();
    endwin();
}

void Renderer::start(){
    if(running) return;
    running = true;
    thread_ = thread(&Renderer::loop,this);
}

void Renderer::stop(){
    running = false;
    if(thread_.joinable()){
        thread_.join();
    }
}

bool Renderer::is_running() const{
    return running;
}

void Renderer::render(){
}

void Renderer::loop(){
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr,TRUE);
    nodelay(stdscr, TRUE);

    using clock = std::chrono::steady_clock;

    auto last_time = clock::now();
    while (running) {
        auto frame_start = clock::now();

        double delta =
            std::chrono::duration<double>(frame_start - last_time).count();
        last_time = frame_start;

        erase();

        double fps = (delta > 0.0) ? 1.0 / delta : 0.0;
        std::string s = "FPS: " + std::to_string((int)fps);
        mvprintw(0, 0, "%s", s.c_str());

        read_input();
        refresh();

        double frame_time =
            std::chrono::duration<double>(clock::now() - frame_start).count();

        if (frame_time < target_frametime) {
            std::this_thread::sleep_for(
                std::chrono::duration<double>(target_frametime - frame_time));
        }
    }
}


void Renderer::read_input(){
    int ch = getch();
    switch (ch)
    {
    case 'q':
        running = true;
        break;
    
    default:
        break;
    }
}

