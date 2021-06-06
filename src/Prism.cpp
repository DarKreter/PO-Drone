//
// Created by darkr on 06.06.2021.
//

#include "Prism.hpp"
#include <vector>



Prism::Prism(const Vector3D& localCenter, double r, double h, const MatrixRot3x3& matRot)
        : Figure("SomethingWentWrong.jpg", 4, matRot, localCenter), radius{r}, height{h}
{}

std::vector<Vector3D>& Prism::CalcLocalCoords(std::vector<Vector3D>& vertices)
{
    double halfHeight = height/2;
    MatrixRot3x3 obrot(60,MatrixRot3x3::Axis::OZ);
    vertices.push_back(Vector3D({0,0,-halfHeight}));
    vertices.push_back(Vector3D({radius,0,-halfHeight}));
    vertices.push_back(Vector3D({radius,0,halfHeight}));
    vertices.push_back(Vector3D({0,0,halfHeight}));

    for(int i = 0;i < 6; i++)
        for(int j = 0;j<4;j++)
            vertices.push_back( obrot * vertices[i*4 + j] );
        
    return vertices;
}



