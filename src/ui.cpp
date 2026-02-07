#include "ui.h"
#include<ncurses.h>
#include<unistd.h>
#include<string>


UI::UI(){}

UI::~UI(){}

void UI::enable_debug_mode(bool enable){
    debug_mode = enable;
}


void UI::set_fps(int fps_){
    fps = fps_;
}

void UI::set_frame_num(int frame_num_){
    frame_num = frame_num_;
}


void UI::set_vol(double vol){
    volume = vol*100;
}

void UI::set_time_left(double time){
    time_left = time;
}

void UI::set_playing(bool playing_){
    playing = playing_;
}

void UI::compose_frame(){
    // set fields
    std::string vol_ = "Vol: "+std::to_string(volume);
    std::string time_left_ = "Time left: "+std::to_string(time_left);
    std::string playing_ = "Playing: "+std::to_string(playing);

    // print at pos
    mvprintw(0, 0, "%s", vol_.c_str());
    mvprintw(1, 0, "%s", time_left_.c_str());
    mvprintw(2, 0, "%s", playing_.c_str());

    // draw_bar((COLS-1)/2,(LINES-1)/2,5);
    visualise();


    // if debug enabled
    if(!debug_mode) return;
    int bottom = LINES-1;
    int right = COLS-1;
    mvprintw(bottom,right-6,"%d",fps);
    mvprintw(bottom,right-3,"%d",frame_num);

}

void UI::draw_bar(int x, int y, int height){
    for(int i = y; i<height+y;i++){
        mvprintw(i,x,"%s","#");
    }
}

void UI::visualise(){
    for(int i = 60; i< 90;i++){
        draw_bar(i,(LINES-1)/2,5);
    }
}