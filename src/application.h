#ifndef APPLICATION_H
#define APPLICATION_H

#include "Event/eventloop.h"

//includes for timer
#include <chrono>
#include <thread>

class Application
{
public:
    Application();
    ~Application();

    void timer();

    int exec();

private:
    EventLoop eventLoop;

    bool timerRunning = false;
};

#endif