cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(OpenGlTest VERSION 0.1.0 LANGUAGES CXX)

add_subdirectory(src)

set(SRCS
	main.cpp
	)

add_executable(app ${SRCS})