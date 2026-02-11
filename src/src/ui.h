#pragma once

class UI
{
private:
    bool debug_mode = false;
    int fps = 0;
    int frame_num = 0;
    float cursor_pos = 0.0f;
    float last_sample = 0.0f;

    int volume = 0;

    double time_left = 0.0;
    bool playing = false;

    int frame_count = 0;

    void draw_bar(int x, int y, int height);
    void visualise();

public:
    void enable_debug_mode(bool enable);
    void set_fps(int fps);
    void set_frame_num(int frame_num);

    void set_vol(double vol);
    void set_time_left(double time);
    void set_playing(bool playing);
    void set_frame_count(int frame_count);
    void set_cursor_pos(float cursor_pos_);
    void set_last_sample(float sample);

    void compose_frame();
    

    UI();
    ~UI();
};

