//
// Created by darkr on 08.06.2021.
//

#ifndef DRONE_PLATEAU_HPP
#define DRONE_PLATEAU_HPP
#include <iostream>
#include <MatrixRot.hpp>
#include <Vector.hpp>
#include "MatrixRot.hpp"
#include "Figure.hpp"
/**
 * @file
 * @brief Definicja klasy Plateau
 */

/**
 * @brief Modeluje pojecie plaskowyzu
 */
class Plateau: public Figure
{
    /**
     * @brief dlugosc, szerokosc oraz wysokosc plaskowyzu
     */
    double width, length, height;

public:
    /**
     * @brief konstruuje plaskowyz zadanymi wartosciami
     */
    explicit Plateau(Scene *scene, const Vector3D &localCenter, double w, double l, double h,
    const MatrixRot3x3 &matRot, Vector3D* rotCen = nullptr);
    
    /**
     * @brief Przelicza wszystkie wierzcholki na podstawie srodka i dlugosci bokow
     */
    std::vector<Vector3D>& CalcLocalCoords(std::vector<Vector3D>&) override;
    
    /**
     * @brief Funkcja dostepowa do wysokosci
     * @return Zwraca wysokosc
     */
    double Height() {return height;}
    
};

#endif