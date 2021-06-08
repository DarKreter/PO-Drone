//
// Created by darkr on 05.06.2021.
//
#include <fstream>
#include <utility>
#include "Figure.hpp"
#include "Scene.hpp"

std::uint16_t Figure::count = 0;

Figure::Figure(Scene *scene, std::string fn, uint8_t fnl, Type tt, const MatrixRot3x3 &matRot, Vector3D localCenter,
               Vector3D *rotationCentr)
        : fileName{std::move(fn)}, fileNewLine{fnl},
          localOrientation(matRot), globalOrientation(MatrixRot3x3()), localCoordCenter(std::move(localCenter)), whereIAm{scene}, whoIAm{tt}
{
    scene->AddNewFile(FileName("temp/object" + std::to_string(++Figure::count)));
    if(rotationCentr)
        rotationCenter = rotationCentr;
    else
        rotationCenter = &localCoordCenter;
}

void Figure::CalcGlobalCoords(std::vector<Vector3D>& vertices)
{
    for(auto& vertex: vertices)
        vertex = globalOrientation * (localOrientation * vertex + (localCoordCenter - *rotationCenter)) + localCoordCenter + (*rotationCenter - localCoordCenter);
    
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
    str.close();;
}

void Figure::TranslationRaw(const Vector3D &wektor)
{
    localCoordCenter = localCoordCenter + wektor;
    if(!nested)
        whereIAm->Draw();
}

void Figure::RotationRawLocal(const MatrixRot3x3& macRot)
{
    localOrientation = macRot * localOrientation;
    
    if(!nested)
        whereIAm->Draw();
}

void Figure::RotationRawGlobal(const MatrixRot3x3& macRot)
{
    globalOrientation = macRot * globalOrientation;
        
    if(!nested)
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

void Figure::RotationLocal(double angle, MatrixRot3x3::Axis axis,  double speed)
{
    Animate(
            [this, angle, axis](double divider)
            {
                this->RotationRawLocal(MatrixRot3x3(angle * divider, axis));
            },
            angle, speed, whereIAm->Frequency());
}


void Figure::RotationGlobal(double angle, MatrixRot3x3::Axis axis,  double speed)
{
    Animate(
            [this, angle, axis](double divider)
            {
                this->RotationRawGlobal(MatrixRot3x3(angle * divider, axis));
            },
            angle, speed, whereIAm->Frequency());
}

std::string Figure::WhoIAmText()
{
    switch(whoIAm)
    {
    case Type::Figure:
        return "Somehow pure figure";
    case Type::Cuboid:
        return "Cuboid";
    case Type::Prism:
        return "Prism";
    case Type::BrokenLine:
        return "BrokenLine";
    case Type::Plateau:
//        return "Plateau";
        return "Plaskowyz";
    case Type::RidgeMountain:
//        return "RidgeMountain";
        return "Gora z dluga grania";
    case Type::Drone:
        return "Drone";
    case Type::Pyramid:
//        return "Pyramid";
        return "Gora z ostrym szczytem";
    case Type::Surface:
        return "Surface";
    default:
        return "Ty debilu dodales nowa klase i zapomniales dodac ja do switcha!";
    }
}

Figure::~Figure()
{
    whereIAm->RemoveLastFile(fileName);
}

