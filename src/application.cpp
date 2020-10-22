#include "application.h"

#include <iostream>

class KeyEvent : public Event
{
public:
    KeyEvent(const std::string& data) : data(data) {};

    inline std::string getData() const { return data; }

private:
    std::string data;
};

class TimeoutEvent : public Event
{
public:
    TimeoutEvent() {}
};

void test2(KeyEvent *event)
{
    std::cout << "Key pressed" << std::endl;
    std::cout << event->getData() << std::endl;
}

void test(TimeoutEvent *event)
{
    std::cout << "Timeout raised" << std::endl;
}

Application::Application()
{
    eventLoop.start();

    eventLoop.registerEventType<TimeoutEvent>();
    eventLoop.registerEventType<KeyEvent>();
    
    eventLoop.connectToEvent<TimeoutEvent>(test);
    eventLoop.connectToEvent<KeyEvent>(test2);
/*
    timerRunning = true;
    std::thread t (&Application::timer, this);

    t.detach();
*/
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
    std::string str;
    KeyEvent* event;

    do
    {
        std::cin >> str;
        event = new KeyEvent(str);
        eventLoop.queueEvent(event);

        if(str == "tOn")
        {
            timerRunning = true;
            std::thread t (&Application::timer, this);

            t.detach();
        }
        else if(str == "tOff")
            timerRunning = false;

    } while (str != "quit");

    eventLoop.stop();

    return eventLoop.wait();
}