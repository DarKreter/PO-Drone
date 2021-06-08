//
// Created by darkr on 06.06.2021.
//

#include "Drone.hpp"
#include <vector>
#include <memory>
#include <Scene.hpp>
#include <BrokenLine.hpp>

using namespace std;

std::vector<Vector3D>& Drone::CalcLocalCoords(std::vector<Vector3D>& vertices)
{
    std::cout << "lol";
    return vertices;
}


Drone::Drone(Scene* scene, const Vector3D &localCenter, double wid, double len, double hei, const MatrixRot3x3 &matRot)
        : Figure(scene, "SomethingWentWrong.jpg", 4, matRot, localCenter)
        
{
    
    body = std::make_shared<Cuboid>(scene, localCenter, wid, len, hei, MatrixRot3x3());
    body->Nested();
    
    light1 = std::make_shared<Cuboid>(scene, localCenter + Vector3D({ 3.*wid/20.,wid/2. + len/20.,0}),
                                      2, 6, 13, MatrixRot3x3());
    light1->Nested();
    light2 = std::make_shared<Cuboid>(scene, localCenter + Vector3D({ -3.*wid/20.,wid/2. + len/20.,0}),
                                      len/10., wid/5., 2.*hei/3., MatrixRot3x3());
    light2->Nested();
    int counter = 0;
    for(auto& rotor: rotors)
    {
        rotor = std::make_shared<Prism>(scene, localCenter + Vector3D({ counter > 1 ? len/2: -len/2 ,counter % 2 == 0 ?wid/3.: -wid/3., 3.*hei/4.})
                , 2./5.*len,hei/2.,MatrixRot3x3()); rotor->Nested();
        counter++;
    }
    
    SetCenter();
    
    RotationRaw(matRot);
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
    
    body->RotationRawGlobal(macRot);
    light1->RotationRawGlobal(macRot);
    light2->RotationRawGlobal(macRot);
    short counter = 0;
    for(auto& rotor: rotors)
    {
        rotor->RotationRawGlobal(macRot);
        if(counter++ > 1)
            rotor->RotationRawLocal(MatrixRot3x3(36,MatrixRot3x3::Axis::OZ));
        else
            rotor->RotationRawLocal(MatrixRot3x3(36,MatrixRot3x3::Axis::OZ));
    }
    
    
    whereIAm->Draw();
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
    if(!angle)
        return;
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

void Drone::Route(double nr, double angle)
{
    constexpr int speed = 100;
    
    cout << "Rysuje zaplanowana sciezke lotu..." << endl << endl << endl << endl;
    
    std::vector<Vector3D> trajectory;
    std::shared_ptr<BrokenLine> route = CreateRoute(nr, angle);
    route->CalcGlobalCoords(route->CalcLocalCoords(trajectory));
    
    
    cout << "Realizacja przelotu..." << endl << endl << endl << endl;
 
    //Animacja ruchu
    //Wznoszenie
    Translation(trajectory[1] - trajectory[0] - Vector3D({0,0,body->Height()/2}), speed);
    //Obrót
    Rotation(angle, MatrixRot3x3::Axis::OZ, speed);
    //Poruszanie sie
    Translation(trajectory[2] - trajectory[1], speed);
    //Opadanie
    Translation(trajectory[3] - trajectory[2] - Vector3D({0,0,body->Height()/2}), speed);

    
    cout << "Dron wyladowal..." << endl << endl << endl << endl;
    
    //Remove BrokenLine
    whereIAm->RemoveObject(whereIAm->size()-1);
}

std::shared_ptr<BrokenLine> Drone::CreateRoute(double nr, double angle)
{
    std::vector<Vector3D> trajectory;
    //Zrobienie linii
    trajectory.push_back(Vector3D({0,0,-10}) +  this->LocalCoordCenter());
    trajectory.push_back(Vector3D({0,0,100}) +  this->LocalCoordCenter());
    trajectory.push_back(Vector3D({0,static_cast<double>(nr),0}) +  trajectory[1]);
    trajectory.push_back(Vector3D({0,0,-110}) +  trajectory[2]);
    
    std::shared_ptr<BrokenLine> tr = std::make_shared<BrokenLine>(whereIAm, trajectory);
    Vector3D* test = new Vector3D(this->localCoordCenter);
    tr->RotationCenter(test);
    tr->RotationRawGlobal(this->body->GlobalOrientation() * MatrixRot3x3(angle, MatrixRot3x3::Axis::OZ));
    
    whereIAm->AddObject(tr);
    
    return tr;
}
