#include "application.h"

void test(Event *event)
{
    std::cout << "Timeout raised" << std::endl;
}

Application::Application()
{
    eventLoop.start();

    eventLoop.registerEventType<TimeoutEvent>();
    eventLoop.connectToEvent<TimeoutEvent>(test);

    timerRunning = true;
    std::thread t (&Application::timer, this);

    t.detach();
}

Application::~Application()
{

}

void Application::timer()
{
    TimeoutEvent* event;

    while(timerRunning)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // wait 1 sec
        eventLoop.queueEvent(event);
    }
}

int Application::exec()
{   
    return eventLoop.wait();
}