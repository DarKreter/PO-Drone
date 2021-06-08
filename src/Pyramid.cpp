//
// Created by darkr on 08.06.2021.
//

#include "Pyramid.hpp"
#include <fstream>
#include <vector>


Pyramid::Pyramid(Scene *scene, const Vector3D &localCenter, double w, double l, double h, const MatrixRot3x3 &matRot, Vector3D* rotCen)
        : Figure(scene, "SomethingWentWrong.jpg", 4, matRot, localCenter, rotCen), width{w}, length{l}, height{h}
{}


std::vector<Vector3D>& Pyramid::CalcLocalCoords(std::vector<Vector3D>& vertices)
{
    
    double halfWidth = width/2., halfHeight = height/2., halfLength = length/2.;
    
    vertices.push_back(Vector3D({halfWidth/2,0,halfHeight}));
    vertices.push_back(Vector3D({0,0,height}));
    vertices.push_back(Vector3D({0,0,height}));
    vertices.push_back(Vector3D({-halfWidth/2,0,halfHeight}));
    
    vertices.push_back(Vector3D({halfWidth/2,0,halfHeight}));
    vertices.push_back(Vector3D({-halfWidth,halfLength,0}));
    vertices.push_back(Vector3D({halfWidth,halfLength,0}));
    vertices.push_back(Vector3D({-halfWidth/2,0,halfHeight}));
    
    vertices.push_back(Vector3D({halfWidth/2,0,halfHeight}));
    vertices.push_back(Vector3D({-halfWidth,-halfLength,0}));
    vertices.push_back(Vector3D({halfWidth,-halfLength,0}));
    vertices.push_back(Vector3D({-halfWidth/2,0,halfHeight}));
    
    vertices.push_back(Vector3D({halfWidth/2,0,halfHeight}));
    vertices.push_back(Vector3D({0,0,height}));
    vertices.push_back(Vector3D({0,0,height}));
    vertices.push_back(Vector3D({-halfWidth/2,0,halfHeight}));
    
    return vertices;
}



