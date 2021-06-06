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
void Figure::Animate(std::function<void(double)> function, T arg, double speed)
{
    constexpr uint16_t delay = 20;//[ms]
    const double time = arg / (speed / 1000); //[ms]
    const double hmt = time / delay;//[ms]
//    auto copy = *this;
//    copy->TranslationRaw(wektor);

    for(uint32_t timeElapsed = 0; timeElapsed<=time; timeElapsed += delay)
    {
        readyToDraw = false;
        function(1 / hmt);
        readyToDraw = true;
        usleep(delay*1'000);
    }

    
//    *this = *copy;
}

#endif