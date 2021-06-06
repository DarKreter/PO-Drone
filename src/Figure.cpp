//
// Created by darkr on 05.06.2021.
//
#include <fstream>
#include "Figure.hpp"
#include "Scene.hpp"

Figure::Figure(std::string fn, uint8_t fnl, const MatrixRot3x3 &matRot, const Vector3D &localCenter)
        : fileName{std::move(fn)}, fileNewLine{fnl},
            orientation(matRot), localCoordCenter(localCenter), whereIAm{nullptr}
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
    int i =0;
    for(const auto& vertex: vertices)
    {
        str << vertex << std::endl << (i%fileNewLine==(fileNewLine-1)?"\n":"");
        i++;
    }
    str.close();
}

void Figure::TranslationRaw(const Vector3D &wektor)
{
    localCoordCenter = localCoordCenter + wektor;
    
    whereIAm->Draw();
}

void Figure::RotationRaw(const MatrixRot3x3& macRot)
{
    orientation = macRot * orientation;
    whereIAm->Draw();
}

void Figure::Translation(Vector3D wektor, double speed)
{
    Animate(
            [this, wektor](double divider)
            {
                this->TranslationRaw(wektor*divider);
            },
            wektor, speed, whereIAm->Frequency());
}

void Figure::Rotation(double angle, MatrixRot3x3::Axis axis,  double speed)
{
    Animate(
            [this, angle, axis](double divider)
            {
                this->RotationRaw(MatrixRot3x3(angle * divider, axis));
            },
            angle, speed, whereIAm->Frequency());
}

