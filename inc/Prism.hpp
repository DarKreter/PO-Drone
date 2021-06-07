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



class Prism: public Figure
{
    double radius, height;
    
public:
    /**
     * \brief Inicjalizuje wierzchołki prostopadłościanu, na podstawie danych z pliku.
     */
    explicit Prism(Scene *scene, const Vector3D &localCenter, double r, double h, const MatrixRot3x3 &matRot = MatrixRot3x3());
    
    std::vector<Vector3D>& CalcLocalCoords(std::vector<Vector3D>&) override;
};



#endif //DRONE_PRISM_HPP

