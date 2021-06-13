//
// Created by darkr on 06.06.2021.
//
#ifndef FIGURE_TPP
#define FIGURE_TPP
#include<Figure.hpp>

/**
 * @file
 * @brief Definicja szablonów klasy Figure
 */

/**
 * Funkcja animująca poszczególne ruchy drona
 *
 * @tparam T - Typ argumentu przekazywanego do funkcji - musi być rzutowalny na typ double
 * @param function - Funkcja która wykonuje poszczególne ruchy - jest wywoływana wielokrotnie w pętli
 * @param arg - argument na którego podstawie określamy co jest do przebycia
 * @param speed - prędkość animacji
 * @param frequency - ilość klatek na sekunde
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