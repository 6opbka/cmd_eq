#pragma once
#include<atomic>

struct AudioState
{   
    std::atomic<float> volume {1.0f};
    std::atomic<float> time_left {0.0f};
    std::atomic<bool> playing {false};
    std::atomic<int> frame_count {0};
    std::atomic<float> cursor_pos {0.0f};
    std::atomic<float> last_sample{0.0f};
};

enum class AudioCommand{
    None,
    Play,
    Pause,
};

struct AudioControls
{   
    std::atomic<AudioCommand> command {AudioCommand::None};
};