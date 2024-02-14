// Copyright (C) 2024 ilobilo

#pragma once

#include <glm/glm.hpp>
#include <term.hpp>

struct cube
{
    static inline constexpr ssize_t nx_chars = 2;
    static inline constexpr ssize_t ny_chars = 1;

    static inline constexpr auto vchar = "▓▓";
    static inline constexpr auto hchar = "▓▓";

    static inline constexpr float deviation = -15;
    static inline constexpr glm::mat3 proj_matrix
    {
        { 1, 0, 0 },
        { 0, 1, 0 },
        { 0, 0, 0 }
    };

    terminal term;

    ssize_t size;
    glm::vec3 vertices[8];

    void rotate(float deg, glm::vec3 axis);
    void draw();

    cube(ssize_t size);
};
