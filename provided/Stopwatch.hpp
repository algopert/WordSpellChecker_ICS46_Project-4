// Stopwatch.hpp
//
// ICS 46 Winter 2022
// Project #4: Set the Controls for the Heart of the Sun
//
// The Stopwatch class is used to measure CPU time consumption between
// the time that its start() and stop() member functions are called.

#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include <chrono>



class Stopwatch
{
public:
    Stopwatch();

    void start();
    void stop();

    double lastDuration() const;


    class NotRunningException { };
    class RunningException { };

private:
    bool running;
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point stopTime;
    double duration;
};



#endif

