cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(EventLoop VERSION 0.1.0 LANGUAGES CXX)

add_subdirectory(src)

set(SRCS
	main.cpp
	)

add_executable(app ${SRCS})

target_link_libraries(app srcs)