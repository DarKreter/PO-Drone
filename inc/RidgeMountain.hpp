//
// Created by darkr on 08.06.2021.
//

#ifndef DRONE_RIDGEMOUNTAIN_HPP
#define DRONE_RIDGEMOUNTAIN_HPP
#include <iostream>
#include <MatrixRot.hpp>
#include <Vector.hpp>
#include "MatrixRot.hpp"
#include "Figure.hpp"

/**
 * @file
 * @brief Definicja klasy RidgeMountain
 */

/**
 * @brief Modeluje pojecie gory z długą granią
 */
class RidgeMountain: public Figure
{
    /**
     * @brief Zmienne opisuja poszczegolne boki bryły
     */
    double width, length, height;

public:
    /**
     * \brief Inicjalizuje poszczegolne boki bryły na podstawie danych przysłanych
     */
    explicit RidgeMountain(Scene *scene, const Vector3D &localCenter, double w, double l, double h,
    const MatrixRot3x3 &matRot, Vector3D* rotCen = nullptr);
    
    /**
     * @brief Przelicza wierzchołki na podstawie dlugości boków oraz środka bryły
     */
    std::vector<Vector3D>& CalcLocalCoords(std::vector<Vector3D>&) override;
    
};


#endif //DRONE_RIDGEMOUNTAIN_HPP
