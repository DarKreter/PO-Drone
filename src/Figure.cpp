//
// Created by darkr on 05.06.2021.
//
#include <fstream>
#include "Figure.hpp"

Figure::Figure(std::string fn, const MatrixRot3x3& matRot, const Vector3D& localCenter) : fileName{std::move(fn)}, readyToDraw{true},
                                                                            orientation(matRot), localCoordCenter(localCenter)
{}

void Figure::CalcGlobalCoords(std::vector<Vector3D>& vertices)
{
    for(auto& vertex: vertices)
        vertex = orientation * vertex + localCoordCenter;
    
}

void Figure::Draw()
{
    std::vector<Vector3D> vertices;
    vertices.reserve(32);
    
    CalcGlobalCoords(CalcLocalCoords(vertices));

    
    std::ofstream str(fileName);
    str << vertices;
    str.close();
}

void Figure::TranslationRaw(const Vector3D &wektor)
{
    localCoordCenter = localCoordCenter + wektor;
}

void Figure::RotationRaw(const MatrixRot3x3& macRot)
{
    orientation = macRot * orientation;
    Draw();
}


std::ostream& operator<<(std::ostream& strm,const std::vector<Vector3D>& vertices)
{
    int i =0;
    for(const auto& vertex: vertices)
    {
        strm << vertex << std::endl << (i%2==1?"\n":"");
        i++;
    }
    
    return strm;
}

void Figure::Translation(Vector3D wektor, double speed)
{
    Animate(
            [this, wektor](double divider)
            {
                this->TranslationRaw(wektor*divider);
            },
            wektor, speed);
}

void Figure::Rotation(double angle, MatrixRot3x3::Axis axis,  double speed)
{
    Animate(
            [this, angle, axis](double divider)
            {
                this->RotationRaw(MatrixRot3x3(angle * divider, axis));
            },
            angle, speed);
}

