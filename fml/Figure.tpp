//
// Created by darkr on 06.06.2021.
//
#ifndef FIGURE_TPP
#define FIGURE_TPP
#include<Figure.hpp>

/*
 * Wymagania:
 * FunPtr służy do pokazywania w klasie Figure ale jest override w klasie dziedzicznej
 * T zapewnia dzielenie przez double oraz ma funkcje składową .Lenght()
 */
template<typename T>
void Figure::Animate(std::function<void(double)> function, T arg, double speed, double frequency)
{
    const uint16_t delay = 1000./frequency;//[ms]
    const double time = std::abs(arg / (speed / 1000)); //[ms]
    const double hmt = time / delay;//[ms]

    for(uint32_t timeElapsed = 0; timeElapsed<=time; timeElapsed += delay)
    {
        function(1 / hmt);
        usleep(delay*1'000);
    }
}

#endif