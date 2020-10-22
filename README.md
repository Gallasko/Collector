# Event Loop
 A C++11 Event Loop class
 It is fully self contained and doesn't require any external librairy

## Table of contents
* [Include in your project](#How-to-Include-in-your-project)
* [Usage](#Usage)
* [Build](#Build)

## How to Include in your project
 If you want to use this event loop class you just need to add [eventloop.cpp](src/Event/eventloop.cpp) and [eventloop.h](src/Event/eventloop.h) to your project.

## Usage
 Use `start` to run the EventLoop
 Use `stop` to stop the EventLoop
 Use `wait` to let the EventLoop run

 To register an event you need to call:     
 `registerEventType< "Your Event" >()`

 and an event only need to inherit from the class `Event` nothing more
 
 To listen to an event you need to call:
 `connectToEvent(std::function<void( "Event to listen" *)> func)`

 To queue an event you just need to queue it in the event loop
 `queueEvent("Your event")`
 Once an event is queued it, the event loop will automatically send the event to all the listener

 A full fledge exemple can be found in [application.cpp](src/application.cpp)

## Build
 To build the exemple just run cmake in the root folder and your are done.

