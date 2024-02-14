# Copyright (C) 2024 ilobilo

project('Cube', 'cpp',
    default_options : [
        'cpp_std=c++20'
    ]
)

sources = files(
    'src/main.cpp',
    'src/cube.cpp'
)

includes = include_directories('src')

executable('cube',
    dependencies : [
        dependency('curses'),
        dependency('glm')
    ],
    sources : sources,
    include_directories : includes,
    cpp_args : [
        '-Wall',
        '-Wextra'
    ]
)