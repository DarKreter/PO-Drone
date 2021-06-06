//
// Created by darkr on 06.06.2021.
//

#include "Drone.hpp"
#include <vector>
#include <memory>
#include <Scene.hpp>


std::vector<Vector3D>& Drone::CalcLocalCoords(std::vector<Vector3D>& vertices)
{
    std::cout << "lol";
    return vertices;
}


Drone::Drone(Scene* scene, const Vector3D &localCenter, double wid, double len, double hei, const MatrixRot3x3 &matRot)
        : Figure(scene, "SomethingWentWrong.jpg", 4, matRot, localCenter)
        
{
    
    body = std::make_shared<Cuboid>(scene, localCenter, wid, len, hei, matRot);
    body->Nested();
    light1 = std::make_shared<Cuboid>(scene, localCenter + Vector3D({ 3.*wid/20.,wid/2. + len/20.,0}),
                                      len/10., wid/5., 2.*hei/3., matRot);
    light1->Nested();
    light2 = std::make_shared<Cuboid>(scene, localCenter + Vector3D({ -3.*wid/20.,wid/2. + len/20.,0}),
                                      len/10., wid/5., 2.*hei/3., matRot);
    light2->Nested();
    int counter = 0;
    for(auto& rotor: rotors)
    {
        rotor = std::make_shared<Prism>(scene, localCenter + Vector3D({ counter > 1 ? len/2: -len/2 ,counter % 2 == 0 ?wid/3.: -wid/3., 3.*hei/4.})
                , 2./5.*len,hei/2.,matRot); rotor->Nested();
        counter++;
    }
}

void Drone::TranslationRaw(const Vector3D &wektor)
{
    localCoordCenter = localCoordCenter + wektor;
    body->TranslationRaw(wektor);
    light1->TranslationRaw(wektor);
    light2->TranslationRaw(wektor);
    short counter = 0;
    for(auto& rotor: rotors)
    {
        rotor->TranslationRaw(wektor);
        if(counter++ > 1)
            rotor->RotationRawLocal(MatrixRot3x3(wektor.Length()*36,MatrixRot3x3::Axis::OZ));
        else
            rotor->RotationRawLocal(MatrixRot3x3(-wektor.Length()*36,MatrixRot3x3::Axis::OZ));
        
    }
    
    whereIAm->Draw();
    
}

void Drone::RotationRaw(const MatrixRot3x3& macRot)
{
    localOrientation = macRot * localOrientation;
    
    SetCenter();
    
    body->RotationRawGlobal(macRot);
    light1->RotationRawGlobal(macRot);
    light2->RotationRawGlobal(macRot);

    for(auto& rotor: rotors)
        rotor->RotationRawGlobal(macRot);
    
    
    whereIAm->Draw();
    
//    ClearCenter();
}


void Drone::SetCenter()
{
    body->RotationCenter(&localCoordCenter);
    light1->RotationCenter(&localCoordCenter);
    light2->RotationCenter(&localCoordCenter);
    for(auto& rotor: rotors)
        rotor->RotationCenter(&localCoordCenter);

}

void Drone::ClearCenter()
{
    body->ClearRotationCenter();
    light1->ClearRotationCenter();
    light2->ClearRotationCenter();
    for(auto& rotor: rotors)
        rotor->ClearRotationCenter();
}


void Drone::Translation(Vector3D wektor, double speed)
{
    Animate(
            [this, wektor](double divider)
            {
                this->TranslationRaw(wektor*divider);
            },
            wektor, speed, whereIAm->Frequency());
}

void Drone::Rotation(double angle, MatrixRot3x3::Axis axis,  double speed)
{
    Animate(
            [this, angle, axis](double divider)
            {
                this->RotationRaw(MatrixRot3x3(angle * divider, axis));
            },
            angle, speed, whereIAm->Frequency());
}

void Drone::Draw()
{
    body->Draw();
    light1->Draw();
    light2->Draw();

    for(auto& rotor: rotors)
        rotor->Draw();
    
}
