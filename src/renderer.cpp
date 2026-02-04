#include"renderer.h"
#include<ncurses.h>
#include<unistd.h>
#include<string>
#include <iostream>

using namespace std;

Renderer::Renderer():
    running(true)
{
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

void Renderer::update(float time_delta){
    
    render(time_delta);
}

void Renderer::render(float time_delta){
        // std::cout<<"mmm\n";
        erase();

        double fps = (time_delta > 0.0) ? 1.0 / time_delta : 0.0;
        std::string s = "FPS: " + std::to_string((int)fps);
        mvprintw(0, 0, "%s", s.c_str());

        read_input();
        refresh();
}

void Renderer::init(){
    initscr();
    noecho();
    cbreak();
    curs_set(0);
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
    
    default:
        break;
    }
}

