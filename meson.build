project('ratl', 'cpp', default_options: ['cpp_std=c++20'])

add_project_link_arguments(['-lstdc++fs'], language: 'cpp')

cpp = meson.get_compiler('cpp')

catch2 = dependency('catch2')

ratl = declare_dependency(include_directories: ['./inc'])

subdir('test')
