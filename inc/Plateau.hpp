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


class Plateau: public Figure
{
    /**
     * \brief Tablica przechowująca 8 wierzchołków prostopadłościanu
     *
     * Prostopadłościan jest zlokalizowany w przestrzeni 3D
     * Pojedyńczy punkt jest zmodelowany za pomocą klasy Vector3D
     */
    double width, length, height;

public:
    /**
     * \brief Inicjalizuje wierzchołki prostopadłościanu, na podstawie danych z pliku.
     */
    explicit Plateau(Scene *scene, const Vector3D &localCenter, double w, double l, double h,
    const MatrixRot3x3 &matRot, Vector3D* rotCen = nullptr);
    
    std::vector<Vector3D>& CalcLocalCoords(std::vector<Vector3D>&) override;
    
    double Height() {return height;}
    
};

#endif