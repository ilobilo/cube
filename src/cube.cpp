// Copyright (C) 2024 ilobilo

#include <cube.hpp>
#include <cstddef>

#include <glm/gtc/quaternion.hpp>

static inline glm::vec3 rotate_vector(float angle, glm::vec3 axis, glm::vec3 vec)
{
    const auto mat = glm::rotate(
        glm::identity<glm::mat4>(),
        glm::radians(angle),
        glm::normalize(axis)
    );
    return mat * glm::vec4 { vec, 1.f };
}

void cube::rotate(float deg, glm::vec3 axis)
{
    for (auto &point : vertices)
        point = rotate_vector(deg, axis, point);
}

std::pair<ssize_t, ssize_t> cube::getstarts()
{
    const auto width = term.width();
    const auto height = term.height();

    return { (width / (2 * cube::nx_chars)), (height / (2 * cube::ny_chars)) };
}

void cube::draw_line(glm::vec2 start, glm::vec2 end)
{
    const auto x0 = start.x;
    const auto y0 = start.y;

    const auto x1 = end.x;
    const auto y1 = end.y;

    const auto dx = x1 - x0;
    const auto dy = y1 - y0;

    if (glm::abs(dy) > glm::abs(dx))
    {
        const auto ymin = glm::min(y0, y1);
        const auto ymax = glm::max(y0, y1);
        const std::size_t iymin = glm::ceil(ymin);
        const std::size_t iymax = glm::ceil(ymax);
        const auto dxdy = dx / dy;

        for (auto iy = iymin; iy < iymax; iy++)
        {
            const std::size_t ix = (static_cast<float>(iy) - y0) * dxdy + x0;
            term.printoff(ix, iy, cube::hchar);
        }
    }
    else
    {
        const auto xmin = glm::min(x0, x1);
        const auto xmax = glm::max(x0, x1);
        const std::size_t ixmin = glm::ceil(xmin);
        const std::size_t ixmax = glm::ceil(xmax);
        const auto dydx = dy / dx;

        for (auto ix = ixmin; ix < ixmax; ix++)
        {
            const std::size_t iy = (static_cast<float>(ix) - x0) * dydx + y0;
            term.printoff(ix, iy, cube::vchar);
        }
    }
}

bool cube::draw()
{
    const auto minsz = glm::min(term.height(), term.width());
    const auto size = ((static_cast<float>(minsz) / cube::ny_chars) / glm::sqrt(3)) / 2;
    const auto [startx, starty] = getstarts();

    const auto project = [startx, starty](glm::vec3 vec)
    {
        const auto projected = cube::proj_matrix * vec;
        const auto x = static_cast<ssize_t>(projected.x) + startx;
        const auto y = static_cast<ssize_t>(projected.y) + starty;
        return glm::vec2 { x * nx_chars, y * ny_chars };
    };

    glm::vec2 pos[8] { };
    for (std::size_t i = 0; const auto &point : vertices)
        pos[i++] = project(point * static_cast<float>(size));

    /*
     *    5-----4
     *   /|    /|
     *  1-----0 |
     *  | 6---|-7
     *  |/    |/
     *  2-----3
     */

    term.clear();

    draw_line(pos[1], pos[0]);
    draw_line(pos[0], pos[3]);
    draw_line(pos[3], pos[2]);
    draw_line(pos[2], pos[1]);

    draw_line(pos[5], pos[4]);
    draw_line(pos[4], pos[7]);
    draw_line(pos[7], pos[6]);
    draw_line(pos[6], pos[5]);

    draw_line(pos[1], pos[5]);
    draw_line(pos[0], pos[4]);
    draw_line(pos[2], pos[6]);
    draw_line(pos[3], pos[7]);

    term.refresh();

    return true;
}

cube::cube() : term { }
{
    term.refresh();

    for (std::size_t i = 0; auto &point : vertices)
        point = cube::default_verticies[i++];
}
