// Copyright (C) 2024 ilobilo

#pragma once

#include <glm/glm.hpp>
#include <term.hpp>

#include <utility>

struct cube
{
    // for 8x16 font
    static inline constexpr ssize_t nx_chars = 2;
    static inline constexpr ssize_t ny_chars = 1;

    static inline constexpr auto vchar = "▓▓";
    static inline constexpr auto hchar = "▓▓";

    static inline constexpr glm::mat3 proj_matrix
    {
        { 1, 0, 0 },
        { 0, 1, 0 },
        { 0, 0, 0 }
    };

    static inline constexpr glm::vec3 default_verticies[8]
    {
        { -1, -1,  1 },
        {  1, -1,  1 },
        {  1,  1,  1 },
        { -1,  1,  1 },
        { -1, -1, -1 },
        {  1, -1, -1 },
        {  1,  1, -1 },
        { -1,  1, -1 }
    };

    private:
    terminal term;

    glm::vec3 vertices[8];

    std::pair<ssize_t, ssize_t> getstarts();
    void draw_line(glm::vec2 start, glm::vec2 end);

    public:
    void rotate(float deg, glm::vec3 axis);
    bool draw();

    cube();
};
