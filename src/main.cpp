// Copyright (C) 2024 ilobilo

import cube;
import std;

auto main() -> int
{
    cube cube { };

    volatile bool should_run = true;
    while (should_run)
    {
        cube.rotate(-10, { 0, 1, 0 });
        cube.draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 15));
    }

    return 0;
}