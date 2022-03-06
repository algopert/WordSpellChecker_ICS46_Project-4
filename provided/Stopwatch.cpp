// Stopwatch.cpp
//
// ICS 46 Winter 2022
// Project #4: Set the Controls for the Heart of the Sun

#include <chrono>
#include "Stopwatch.hpp"


Stopwatch::Stopwatch()
    : running{false}, duration{0.0}
{
}


void Stopwatch::start()
{
    if (!running)
    {
        startTime = std::chrono::high_resolution_clock::now();
        running = true;
    }
    else
    {
        throw Stopwatch::RunningException{};
    }
}


void Stopwatch::stop()
{
    if (running)
    {
        stopTime = std::chrono::high_resolution_clock::now();

        duration = 
            std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime)
            .count();

        running = false;
    }
    else
    {
        throw Stopwatch::NotRunningException{};
    }
}


double Stopwatch::lastDuration() const
{
    return duration;
}

