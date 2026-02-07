#pragma once

class UI
{
private:
    bool debug_mode = false;
    int fps = 0;
    int frame_num = 0;

    int volume = 0;

    double time_left = 0.0;
    bool playing = false;

    void draw_bar(int x, int y, int height);
    void visualise();

public:
    void enable_debug_mode(bool enable);
    void set_fps(int fps);
    void set_frame_num(int frame_num);

    void set_vol(double vol);
    void set_time_left(double time);
    void set_playing(bool playing);

    void compose_frame();
    

    UI();
    ~UI();
};

