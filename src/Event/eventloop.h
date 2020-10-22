#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <unordered_map>
#include <functional>
#include <typeinfo>
#include <vector>

#include <condition_variable>
#include <future>
#include <thread>
#include <mutex>

#include "event.h"

#include <iostream>

class EventLoop
{
public: 
    EventLoop();

    inline void start() { running = true; f = std::async(&EventLoop::loop, this); }
    inline int wait() { return f.get(); }
    int loop();

    template<typename EventType>    
    void registerEventType();

    template<typename EventType>
    void connectToEvent(std::function<void(EventType*)> func);

    template<typename EventType> 
    void queueEvent(EventType *event);


private:
    std::unordered_map<std::string, std::vector<std::function<void(Event*)>>> eventMap;
    std::unordered_map<std::string, std::vector<Event *>> eventQueue;
    bool running = false;
    int eventCount = 0;

    std::condition_variable eventLoopCV;
    std::mutex eventLoopMutex;
    std::future<int> f;
};

template<typename EventType>
void EventLoop::registerEventType()
{
    auto id = typeid(EventType).name();

    if(eventMap.find(id) == eventMap.end())
    {
        std::cout << "Register a new event: " << id << std::endl;
        eventMap[id] = std::vector<std::function<void(Event*)>>();
        eventQueue[id] = std::vector<Event*>();
    }
    else
    {
        std::cout << "Event is already registered" << std::endl;
    }
}

template<typename EventType>
void EventLoop::connectToEvent(std::function<void(EventType*)> func)
{
    auto id = typeid(EventType).name();

    if(eventMap.find(id) != eventMap.end())
    {
        std::cout << "Connect the function to the event: " << id << std::endl;
        eventMap[id].push_back(
            [func](Event* e) { func(static_cast<EventType*>(e)); } // Push a lambda expression that convert an event into the EventType
            );
    }
    else
    {
        std::cout << "Error: Event is not registered" << std::endl;
    }
}

template<typename EventType>
void EventLoop::queueEvent(EventType *event)
{
    auto id = typeid(*event).name();

    if(eventMap.find(id) != eventMap.end())
    {
        eventQueue[id].push_back(event);
        eventCount++;
        eventLoopCV.notify_one();
    }
    else
    {
        std::cout << "Error: Event is not registered" << std::endl;
    }
}

#endif