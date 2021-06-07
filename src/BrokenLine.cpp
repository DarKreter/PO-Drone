//
// Created by darkr on 06.06.2021.
//

#include "BrokenLine.hpp"
#include <fstream>
#include <utility>


BrokenLine::BrokenLine(Scene *scene, std::vector<Vector3D> p)
        : Figure(scene, "SomethingWentWrong.jpg", 128, MatrixRot3x3(), Vector3D()), points{std::move(p)}
{}


std::vector<Vector3D>& BrokenLine::CalcLocalCoords(std::vector<Vector3D>& vertices)
{
    for(auto& point: points)
        vertices.push_back(point);
    
    return vertices;
}



