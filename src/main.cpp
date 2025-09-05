// Copyright (C) 2024 ilobilo

#include <cube.hpp>

#include <thread>
#include <chrono>

auto main() -> int
{
    using namespace std::chrono_literals;

    cube cube { };
    cube.rotate(-15, { 1, 0, 0 });
    cube.rotate(-10, { 0, 0, 1 });

    while (true)
    {
        cube.rotate(-3.5f, { 0, 1, 0 });
        cube.draw();
        std::this_thread::sleep_for(1000ms / 30);
    }

    return EXIT_SUCCESS;
}
