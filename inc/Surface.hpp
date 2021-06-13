//
// Created by darkr on 06.06.2021.
//

#ifndef DRONE_SURFACE_HPP
#define DRONE_SURFACE_HPP
#include <iostream>
#include <MatrixRot.hpp>
#include <Vector.hpp>
#include "MatrixRot.hpp"
#include "Figure.hpp"

/**
 * @file
 * @brief Definicja klasy płaszczyzna
 */

/**
 * @brief Modeluje pojęcie płaszczyzny
 */
class Surface: public Figure
{
    /**
     * @brief Zmienne informujące o zasięgu na jakim ma być płaszczyzna oraz jej wysokości
     */
    double range, level;

public:

    /**
     * @brief Tworzy płaszczyzne na podstawie przysłanych danych
     */
    explicit Surface(Scene *scene, double r);
    
    /**
     * @brief Przelicza wierzchołki na podstawie swoich wartości i środka
     */
    std::vector<Vector3D>& CalcLocalCoords(std::vector<Vector3D>& a) override {return a;}
    
    /**
     * @brief Zapisuje bezpośrednio do pliku wartości punktow plaszczyzny
     */
    void Draw() override;

};


#endif //DRONE_SURFACE_HPP

