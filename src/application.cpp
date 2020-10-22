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
    std::cout << "Key event: " << event->getData() << std::endl;
}

void test(TimeoutEvent *event)
{
    std::cout << "Timeout raised" << std::endl;
}

Application::Application()
{
    eventLoop.start();
    std::cout << "Event Loop Started, waiting for events" << std::endl;

    eventLoop.registerEventType<TimeoutEvent>();
    std::cout << "Registered Timeout Event" << std::endl;
    eventLoop.registerEventType<KeyEvent>();
    std::cout << "Registered Key Event" << std::endl;
    
    eventLoop.connectToEvent<TimeoutEvent>(test);
    std::cout << "Function test listen to Timeout events" << std::endl;
    eventLoop.connectToEvent<KeyEvent>(test2);
    std::cout << "Function test2 listen to Timeout events" << std::endl;

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

    std::cout << "Enter something: " << std::endl;
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

    std::cout << "Terminate the event loop" << std::endl;
    eventLoop.stop();
    
    timerRunning = false;

    return eventLoop.wait();
}