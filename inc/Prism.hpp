//
// Created by darkr on 06.06.2021.
//

#ifndef DRONE_PRISM_HPP
#define DRONE_PRISM_HPP
#include <iostream>
#include <MatrixRot.hpp>
#include <Vector.hpp>
#include "MatrixRot.hpp"
#include "Figure.hpp"

/**
 * @file
 * @brief Definicja klasy Prism
 */

/**
 * @brief Modeluje pojecie graniastoslupa
 */
class Prism: public Figure
{
    /**
     * @brief Przechowuja dlugosc promienia i wysokosc granistoslupa
     */
    double radius, height;
    
public:
    /**
     * \brief Inicjalizuje wielkosci granistoslupa na podstawie przyslanych
     */
    explicit Prism(Scene *scene, const Vector3D &localCenter, double r, double h, const MatrixRot3x3 &matRot = MatrixRot3x3());
    
    /**
     * @brief Przelicza wierzcholki z pliku na podstawie srodka promienia i wysokosci
     */
    std::vector<Vector3D>& CalcLocalCoords(std::vector<Vector3D>&) override;
};



#endif //DRONE_PRISM_HPP

