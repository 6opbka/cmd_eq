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

void UI::set_frame_count(int frame_count_){
    frame_count = frame_count_;
}

void UI::set_cursor_pos(float cursor_pos_){
    cursor_pos = cursor_pos_;
}

void UI::set_last_sample(float sample_){
    last_sample = sample_;
}   

void UI::compose_frame(){
    // set fields
    std::string vol_ = "Vol: "+std::to_string(volume);
    std::string time_left_ = "Time left: "+std::to_string(time_left);
    std::string playing_ = "Playing: "+std::to_string(playing);
    std::string frame_count_ = "Frame count:" + std::to_string(frame_count);
    std::string cursor_pos_ = "Cursor pos:" + std::to_string(cursor_pos);
    std::string last_sample_ = "Last sample:" + std::to_string(last_sample);
    
    // print at pos
    mvprintw(0, 0, "%s", vol_.c_str());
    mvprintw(1, 0, "%s", time_left_.c_str());
    mvprintw(2, 0, "%s", playing_.c_str());
    mvprintw(3, 0, "%s", frame_count_.c_str());
    mvprintw(4, 0, "%s", cursor_pos_.c_str());
    mvprintw(5, 0, "%s", last_sample_.c_str());


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