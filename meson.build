project('fltk_helloworld', 'cpp', version: '0.0.1')


inc = include_directories('src')

cmake = import('cmake')

deps = []

deps += cmake.subproject('fltk-1.3.8').dependency('fltk')

sources = files(
  'src/main.cpp'
  )

executable('fltk_helloworld', sources, include_directories: inc, dependencies: deps)
