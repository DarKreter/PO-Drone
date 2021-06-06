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

class Surface: public Figure
{
    double range, level;

public:

    explicit Surface(Scene *scene, double r);
    
    std::vector<Vector3D>& CalcLocalCoords(std::vector<Vector3D>& a) override {return a;}
    
    void Draw() override;

};


#endif //DRONE_SURFACE_HPP

