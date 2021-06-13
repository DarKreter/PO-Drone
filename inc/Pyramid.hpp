//
// Created by darkr on 08.06.2021.
//

#ifndef DRONE_PYRAMID_HPP
#define DRONE_PYRAMID_HPP
#include <iostream>
#include <MatrixRot.hpp>
#include <Vector.hpp>
#include "MatrixRot.hpp"
#include "Figure.hpp"

/**
 * @file
 * @brief Definicja klasy Pyramid
 */

/**
 * @brief Modeluje pojecie ostroslupa
 */
class Pyramid: public Figure
{
    /**
     * @brief Dlugosc i szerokosc podstawy oraz wysokosc bryly
     */
    double width, length, height;

public:
    /**
     * \brief Inicjalizuje wartosci ostrosłupa na podstawie przysłanych danych
     */
    explicit Pyramid(Scene *scene, const Vector3D &localCenter, double w, double l, double h,
    const MatrixRot3x3 &matRot, Vector3D* rotCen = nullptr);
    
    /**
     * @brief Przelicza wierzchołki na podstawie długości podstawy, wysokości oraz środka
     */
    std::vector<Vector3D>& CalcLocalCoords(std::vector<Vector3D>&) override;
    
};



#endif //DRONE_PYRAMID_HPP

