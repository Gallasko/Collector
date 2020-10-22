#include "eventloop.h"

EventLoop::EventLoop()
{

}

int EventLoop::loop()
{
    do
    {
        std::cout << "Wait for an event" << std::endl;
        std::unique_lock<std::mutex> lock(eventLoopMutex);
        eventLoopCV.wait(lock);

        while(eventCount != 0)
        {
            for (auto const& dict : eventQueue)
            {
                // first : key, second : value
                std::cout << dict.first << std::endl;
                if(dict.second.size() == 0)
                {
                    std::cout << "No event" << std::endl;
                }
                else
                {
                    for(int i = dict.second.size(); i > 0; i--)
                    {
                        std::cout << "Event" << std::endl;
                        for(auto listener : eventMap[dict.first])
                        {
                            listener(dict.second[i - 1]);
                        }
                        eventQueue[dict.first].erase(eventQueue[dict.first].begin() + i - 1);
                        eventCount--;
                    }
                }
            }
        }
        
    } while (running);

    eventQueue.clear();
    eventMap.clear();

    return 0;
}