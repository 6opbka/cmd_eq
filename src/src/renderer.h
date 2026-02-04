#pragma once
#include<thread>
#include<atomic>

class Renderer{
    public:
    Renderer();
    ~Renderer();

    
    void stop();
    bool is_running() const;
    void update(float time_delta);
    void init();

    
    private:
    bool running = false;

    
    void render(float time_delta);
    void read_input();
    
};
