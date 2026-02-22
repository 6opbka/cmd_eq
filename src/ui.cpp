#include "ui.h"
#include<ncurses.h>
#include<unistd.h>
#include<string>
#include<iostream>


UI::UI(){
}

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

void UI::set_bar_heights(std::vector<float>& bar_heights){
    
}

void UI::compose_frame(float* spectrum, int bands){
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
    visualiser(spectrum, bands);


    // if debug enabled
    if(!debug_mode) return;
    int bottom = LINES-1;
    int right = COLS-1;
    mvprintw(bottom,right-6,"%d",fps);
    mvprintw(bottom,right-3,"%d",frame_num);

}

void UI::draw_bar(Vector2 pos, int height){
    for(int i = 0; i<height;i++){
        mvprintw(pos.y-i,pos.x,"%s","#");
    }
}

void UI::visualiser(float* spectrum, int bands){
    int offset = (COLS - bands) / 2;

    float max_val = 0.0f;
    for (int b = 0; b < bands; b++)
        max_val = std::max(spectrum[b], max_val);

    int win_height = 20;

    int center_y = LINES / 2;
    int bottom   = center_y + win_height / 2;
    int top      = bottom - win_height;

    for(int b = 0; b < bands; b++){
        float normalized = (max_val > 0.0f)
                           ? spectrum[b] / max_val
                           : 0.0f;

        int bar_height = static_cast<int>(normalized * win_height);

        Vector2 pos{ b + offset, bottom };
        draw_bar(pos, bar_height);
    }

    Vector2 top_left  = { offset+1,        top-1 };
    Vector2 bot_right = { offset+bands+1,  bottom };

    draw_rect(top_left, bot_right);
}


// Draws square with corners at a (top left) and b (bottom right)

// a-----
// |     |
// |     |
// ------b
void UI::draw_rect(Vector2 a, Vector2 b){
    int left   = std::min(a.x, b.x);
    int right  = std::max(a.x, b.x);
    int top    = std::min(a.y, b.y);
    int bottom = std::max(a.y, b.y);

    int width  = right - left;
    int height = bottom - top;
    
    
    draw_vertical_bar({left, top+1}, height);
    draw_vertical_bar({right, top+1}, height);
    draw_horizontal_bar({left+1, top}, width-1);
    draw_horizontal_bar({left+1, bottom}, width-1);
}

void UI::draw_horizontal_bar(Vector2 pos, int width){
    std::string bar(width,'_');
    mvprintw(pos.y,pos.x,"%s",bar.c_str());
}



void UI::draw_vertical_bar(Vector2 pos, int height){
    for(int i = 0; i < height; i++){
        mvprintw(pos.y + i, pos.x, "|");
    }
}