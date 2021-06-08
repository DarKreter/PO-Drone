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



class RidgeMountain: public Figure
{
    double width, length, height;

public:
    /**
     * \brief Inicjalizuje wierzchołki prostopadłościanu, na podstawie danych z pliku.
     */
    explicit RidgeMountain(Scene *scene, const Vector3D &localCenter, double w, double l, double h,
    const MatrixRot3x3 &matRot, Vector3D* rotCen = nullptr);
    
    std::vector<Vector3D>& CalcLocalCoords(std::vector<Vector3D>&) override;
    
};


#endif //DRONE_RIDGEMOUNTAIN_HPP
