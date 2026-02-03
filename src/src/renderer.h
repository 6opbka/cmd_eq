#pragma once
#include<thread>
#include<atomic>

class Renderer{
    public:
    Renderer();
    ~Renderer();

    void start();
    void stop();
    bool is_running() const;
    
    private:
    std::atomic<bool> running = false;


    std::thread thread_;
    
    void loop();
    void render();
    void read_input();

    int target_fps = 30;
    float target_frametime = 0;
    
};
