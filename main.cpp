#include <chrono>
#include <thread>
#include <stdlib.h>
#include <iostream>

#include "fps_counter.hpp"

void loop(int sleep_msec)
{
    fps_counter _fps_counter;

    while(1)
    {
        if (auto fps = _fps_counter.tik(); fps.has_value())
        {
            std::cout << "Thread" << sleep_msec << " " << fps.value() << " FPS" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_msec));
    }
}

int main()
{

    std::thread loop_10 (loop, 10);
    std::thread loop_20 (loop, 20);

    loop_10.join();
    loop_20.join();

    return 0;
}
