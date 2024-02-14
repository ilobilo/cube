// Copyright (C) 2024 ilobilo

#include <cstdlib>
#include <csignal>

#include <cube.hpp>

#include <thread>
#include <chrono>

auto main() -> int
{
    cube cube(8);

    volatile bool should_run = true;
    while (should_run)
    {
        cube.rotate(-10, { 0, 1, 0 });
        cube.draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 15));
    }

    return EXIT_SUCCESS;
}
