cmake_minimum_required(VERSION 3.0)

project(source)

set(SRCS
    Event/eventloop.cpp

    application.cpp
    )
    
set(HEADERS
    Event/eventloop.h
    
    application.h
    )

add_library(srcs ${SRCS} ${HEADERS})