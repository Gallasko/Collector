# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.0)

# Notre projet est étiqueté libhello
project(source)

# Crée des variables avec les fichiers à compiler
set(SRCS
    Event/eventloop.cpp

    application.cpp
    )
    
set(HEADERS
    Event/eventloop.h
    
    application.h
    )

add_library(srcs ${SRCS} ${HEADERS})