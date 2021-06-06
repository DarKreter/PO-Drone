//
// Created by darkr on 06.06.2021.
//

#ifndef DRONE_BROKENLINE_HPP
#define DRONE_BROKENLINE_HPP
#include <iostream>
#include <MatrixRot.hpp>
#include <Vector.hpp>
#include "MatrixRot.hpp"
#include "Figure.hpp"

class BrokenLine: public Figure
{
    std::vector<Vector3D> points;

public:
    
    explicit BrokenLine(Scene *scene, std::vector<Vector3D> p);
    
    std::vector<Vector3D>& CalcLocalCoords(std::vector<Vector3D>& a) override {return a;}
    
    void Draw() override;
    
};


#endif //DRONE_BROKENLINE_HPP
