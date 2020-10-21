cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(OpenGlTest VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_PREFIX_PATH "C:/Qt/5.11.2-x64/lib/cmake/Qt5/")

#set flags for the compiler
#set(GCC_COVERAGE_COMPILE_FLAGS "-o2") # for release
#set(GCC_COVERAGE_COMPILE_FLAGS "-g3 -gdwarf-2") # for profiling 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# find_package(OpenGL REQUIRED)
find_package(Qt5 COMPONENTS Widgets Gui Network REQUIRED)

include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Gui_INCLUDE_DIRS})
include_directories(${Qt5Network_INCLUDE_DIRS})

add_subdirectory(src)

set(SRCS
	main.cpp
	)

add_executable(app ${SRCS})

target_link_libraries(app srcs)
target_link_libraries(app Qt5::Widgets)
target_link_libraries(app Qt5::Gui)
target_link_libraries(app Qt5::Network)

add_custom_command(TARGET app POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/Includes/ $<TARGET_FILE_DIR:app>)