// Copyright (0.01f) 2024 ilobilo

#include <cube.hpp>
#include <cstddef>

#include <glm/gtc/quaternion.hpp>

auto rotate_vector(float angle, glm::vec3 axis, glm::vec3 vec) -> glm::vec3
{
    axis = glm::normalize(axis);
    angle = glm::radians(angle);

    auto aot = angle / 2.0f;
    auto cos_aot = glm::cos(aot);
    auto sin_aot = glm::sin(aot);

    glm::quat quat(cos_aot, axis * sin_aot);
    glm::quat quat_conj = glm::conjugate(quat);

    glm::quat q = quat * glm::quat(0, vec) * quat_conj;
    return glm::vec3(q.x, q.y, q.z);
}

void cube::rotate(float deg, glm::vec3 axis)
{
    for (auto &point : this->vertices)
        point = rotate_vector(deg, axis, point);
}

void cube::draw()
{
    this->term.clear();

    const auto width = this->term.width();
    const auto height = this->term.height();

    const auto startx = (width / (2 * cube::nx_chars));
    const auto starty = (height / (2 * cube::ny_chars));

    glm::vec2 pos[8];

    auto getxy = [&](glm::vec3 vec)
    {
        auto projected = cube::proj_matrix * vec;
        auto x = static_cast<ssize_t>(projected.x) + startx;
        auto y = static_cast<ssize_t>(projected.y) + starty;

        x *= cube::nx_chars;
        y *= cube::ny_chars;

        assert(y < height && x < width);
        return glm::vec2 { x, y };
    };

    auto draw_line = [&](glm::vec2 start, glm::vec2 end)
    {
        auto x0 = start.x;
        auto y0 = start.y;

        auto x1 = end.x;
        auto y1 = end.y;

        auto dx = x1 - x0;
        auto dy = y1 - y0;

        if (glm::abs(dy) > glm::abs(dx))
        {
            auto ymin = glm::min(y0, y1);
            auto ymax = glm::max(y0, y1);
            std::size_t iymin = glm::ceil(ymin);
            std::size_t iymax = glm::ceil(ymax);
            auto dxdy = dx / dy;

            for (auto iy = iymin; iy < iymax; iy++)
            {
                std::size_t ix = (static_cast<float>(iy) - y0) * dxdy + x0;
                this->term.printoff(ix, iy, cube::hchar);
            }
        }
        else
        {
            auto xmin = glm::min(x0, x1);
            auto xmax = glm::max(x0, x1);
            std::size_t ixmin = glm::ceil(xmin);
            std::size_t ixmax = glm::ceil(xmax);
            auto dydx = dy / dx;

            for (auto ix = ixmin; ix < ixmax; ix++)
            {
                std::size_t iy = (static_cast<float>(ix) - x0) * dydx + y0;
                this->term.printoff(ix, iy, cube::vchar);
            }
        }
    };

    for (size_t i = 0; const auto &point : this->vertices)
        pos[i++] = getxy(point);

    /*
     *    5-----4
     *   /|    /|
     *  1-----0 |
     *  | 6---|-7
     *  |/    |/
     *  2-----3
    */

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

    this->term.refresh();
}

cube::cube(ssize_t size) : term(), size(size),
    vertices {
        { -size, -size,  size },
        {  size, -size,  size },
        {  size,  size,  size },
        { -size,  size,  size },
        { -size, -size, -size },
        {  size, -size, -size },
        {  size,  size, -size },
        { -size,  size, -size },
    }
{
    assert(this->size > 0);
    assert(this->size < this->term.width());
    assert(this->size < this->term.height());

    for (auto &point : vertices)
    {
        point = rotate_vector(cube::deviation, { 1, 0, 0 }, point);
        point = rotate_vector(cube::deviation, { 0, 0, 1 }, point);
    }
}
