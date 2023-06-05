#include <chrono>
#include <deque>
#include <iostream>
#include <optional>

struct fps_counter
{
    
    size_t frame_count_interval;
    size_t frame_counter{0};
    std::deque<std::chrono::high_resolution_clock::time_point> time_points;

    fps_counter(size_t interval = 100) : frame_count_interval(interval){}


    std::optional<float> tik()
    {
        auto now = std::chrono::high_resolution_clock::now();

        time_points.push_back(now);
        ++frame_counter;

        if (time_points.size() > frame_count_interval)
        {
            time_points.pop_front();
        }

        if (frame_counter % frame_count_interval == 0 && time_points.size() > 1)
        { 
            auto elapsed = std::chrono::duration<float>(time_points.back() - time_points.front()).count();
            auto fps = (time_points.size() - 1) / elapsed;
            return fps;
        }
        else
        {
            return std::nullopt;
        }
    }
};
