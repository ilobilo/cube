// Copyright (C) 2024 ilobilo

#pragma once

#include <ncurses.h>

#include <type_traits>
#include <locale>

#include <cstddef>

using ssize_t = std::make_signed_t<std::size_t>;

struct terminal
{
    terminal()
    {
        std::locale::global(std::locale(""));

        initscr();
        cbreak();
        noecho();
        curs_set(0);

        clear();
        refresh();
    }

    ~terminal()
    {
        endwin();
    }

    ssize_t width() { return COLS; }
    ssize_t height() { return LINES; }

    void refresh() { ::refresh(); }
    void clear() { ::clear(); }

    void printoff(std::size_t xoff, std::size_t yoff, const char *str)
    {
        mvprintw(yoff, xoff, "%s", str);
    }

    void putoff(std::size_t xoff, std::size_t yoff, char ch)
    {
        mvaddch(yoff, xoff, ch);
    }
};