//
// Created by darkr on 06.06.2021.
//

#include "BrokenLine.hpp"
#include <fstream>


BrokenLine::BrokenLine(std::vector<Vector3D> p)
        : Figure("SomethingWentWrong.jpg", 0, MatrixRot3x3(), Vector3D()), points{p}
{}

void BrokenLine::Draw()
{
    std::ofstream str(fileName);
    for(auto& point: points)
        str << point << std::endl;
    
    str.close();
}


