//
// Created by darkr on 06.06.2021.
//

#include "Drone.hpp"
#include <vector>
#include <memory>
#include <Scene.hpp>
#include <BrokenLine.hpp>
/**
 * @file
 * @brief Definicje funkcji składowych klasy Drone
 */

using namespace std;

/**
 * Przeliczenie wierzchołków na podstawie danych
 *
 * @param vertices - wierzchołki do przeliczenia
 * @return - Wierzchołki które przeliczalismy
 */
std::vector<Vector3D>& Drone::CalcLocalCoords(std::vector<Vector3D>& vertices)
{
    return vertices;
}

/**
 * Kontruktor drona który inicjalizuje w nim wszystkie składowe figury
 *
 * @param scene - scena w której znajduje się dron
 * @param localCenter - środek drona
 * @param wid - szerokość drona
 * @param len - długość drona
 * @param hei - wysokość drona
 * @param matRot - macierz orientacji drona
 */
Drone::Drone(Scene* scene, const Vector3D &localCenter, double wid, double len, double hei, const MatrixRot3x3 &matRot)
        : Figure(scene, "SomethingWentWrong.jpg", 4, Type::Drone, matRot, localCenter)
        
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

/**
 * Przesuniecie od razu o wetkor
 *
 * @param wektor - wektor translacji
 */
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
            rotor->RotationRawLocal(MatrixRot3x3(wektor.Length()*12,MatrixRot3x3::Axis::OZ));
        else
            rotor->RotationRawLocal(MatrixRot3x3(-wektor.Length()*12,MatrixRot3x3::Axis::OZ));
        
    }
    
    whereIAm->Draw();
    
}

/**
 * Obrot od razu o zadana macierz obrotu
 *
 * @param macRot - macierz rotacji o ktora bedziemy obracac
 */
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
            rotor->RotationRawLocal(MatrixRot3x3(120,MatrixRot3x3::Axis::OZ));
        else
            rotor->RotationRawLocal(MatrixRot3x3(120,MatrixRot3x3::Axis::OZ));
    }
    
    
    whereIAm->Draw();
}


/**
 * Ustawienie srodka dla wszystkich figur skladowych drona
 */
void Drone::SetCenter()
{
    body->RotationCenter(&localCoordCenter);
    light1->RotationCenter(&localCoordCenter);
    light2->RotationCenter(&localCoordCenter);
    for(auto& rotor: rotors)
        rotor->RotationCenter(&localCoordCenter);

}

/**
 * Wyczyszczenie srodka ddla wszystkich elementow skladowych drona
 */
void Drone::ClearCenter()
{
    body->ClearRotationCenter();
    light1->ClearRotationCenter();
    light2->ClearRotationCenter();
    for(auto& rotor: rotors)
        rotor->ClearRotationCenter();
}

/**
 * Przesuniecie drona o zadany wektor z zadana predkosci(animacja)
 *
 * @param wektor - wektor translacji
 * @param speed - predkosc przesuwania
 */
void Drone::Translation(Vector3D wektor, double speed)
{
    if(!wektor)
        return;
    
    Animate(
            [this, wektor](double divider)
            {
                this->TranslationRaw(wektor*divider);
            },
            wektor, speed, whereIAm->Frequency());
}

/**
 * Obrót o zadany kąt w zanimowany sposób z prędkością
 *
 * @param angle - kat o jaki obrocimy drona
 * @param axis - os wokol ktorej obrot sie odbedzie
 * @param speed - predkosc z jaka bedziemy obracac
 */
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

/**
 * Wymuszenie rysowania każdej składowej drona
 */
void Drone::Draw()
{
    body->Draw();
    light1->Draw();
    light2->Draw();

    for(auto& rotor: rotors)
        rotor->Draw();
    
}

/**
 * Stworzenie trasy i wykonanie jej przez drona
 *
 * @param nr - dlugosc trasy
 * @param angle - kat o ktory ma sie obrocic dron po wzleceniu w powietrze
 */
void Drone::Route(double nr, double angle)
{
    constexpr int speed = 200;
    
    cout << "Rysuje zaplanowana sciezke lotu..." << endl << endl << endl << endl;
    
    std::vector<Vector3D> trajectory, siema;
    std::shared_ptr<BrokenLine> route = CreateRoute(nr, angle);
    route->CalcGlobalCoords(route->CalcLocalCoords(trajectory));
    
    cout << "Realizacja przelotu..." << endl << endl << endl << endl;
 
    //Animacja ruchu
    //Wznoszenie
    Translation(trajectory[1] - trajectory[0] - Vector3D({0,0,body->Height()/2}), speed);
    //Obrót
    Rotation(angle, MatrixRot3x3::Axis::OZ, speed);
    //Poruszanie sie
//    cout << trajectory[2] - trajectory[1] << endl;
    Translation(trajectory[2] - trajectory[1], speed);
    
    std::string what = Collision();
    while(what != "")
    {
        Vector3D temp = (trajectory[2] - trajectory[1])*0.5;//  double a = temp[1] / temp[0], length = 50;
//        Vector3D additionalRoute = Vector3D({length / pow(1 + a, 0.5),a * length / pow(1 + a, 0.5), 0});
        std::cout << "Ladowisko niedostepne!\nWykryto element powierzchni typu: " << what << "\n\n\n"
        << "Lot zostal wydluzony.\nPoszukiwanie wolnego ladowiska\n\n\n";
        
        
        //biore broken line
        auto tEmP = whereIAm->Objects().end();
        shared_ptr<BrokenLine> trasa = dynamic_pointer_cast<BrokenLine>(*(--tEmP));
        
        //zmieniam wspolrzedne
        trasa->points[2] = trasa->points[2] + Vector3D({0, (temp).Length(),0});
        trasa->points[3] = trasa->points[3] + Vector3D({0, temp.Length(),0});
        
        //rysuje
        whereIAm->Draw();
        
        
        usleep(2'000'000);
        Translation(temp, speed);
        
        what = Collision();
    }
    std::cout << "Ladowisko dostepne!\nRozpoczecie procedury ladowania.\n\n\n";
    
    //Opadanie
    Translation(trajectory[3] - trajectory[2] + Vector3D({0,0,body->Height()/2}), speed);

    
    cout << "Dron wyladowal..." << endl << endl << endl << endl;
    
    //Remove BrokenLine
    whereIAm->RemoveObject(whereIAm->size()-1);
}

/**
 * Stworzenie lini lamanej trasy przelotu
 *
 * @param nr - dlugosc trasy przelotu
 * @param angle - kat dla trasy przelotu
 * @return - zwraca linie łamaną która ilustruje przelot
 */
std::shared_ptr<BrokenLine> Drone::CreateRoute(double nr, double angle)
{
    std::vector<Vector3D> trajectory;
    //Zrobienie linii
    trajectory.push_back(Vector3D({0,0,-body->Height()/2}) +  this->LocalCoordCenter());
    trajectory.push_back(Vector3D({0,0,350}) +  this->LocalCoordCenter());
    trajectory.push_back(Vector3D({0, static_cast<double>(nr),0}) +  trajectory[1]);
    trajectory.push_back(Vector3D({0,0,-360}) +  trajectory[2]);
    
    std::shared_ptr<BrokenLine> tr = std::make_shared<BrokenLine>(whereIAm, trajectory);
    Vector3D* test = new Vector3D(this->localCoordCenter);
    tr->RotationCenter(test);
    tr->RotationRawGlobal(this->body->GlobalOrientation() * MatrixRot3x3(angle, MatrixRot3x3::Axis::OZ));
    
    whereIAm->AddObject(tr);
    
    return tr;
}

/**
 * Zwraca rzut figury w formie uproszczonej jako prostokąt który ma boki
 * równoległe do osi OX i OY
 *
 * @return - Prostokąt który jest rzutem na płaszczyzne OXY
 */
Rectangle Drone::OXYprojection()
{
    return body->OXYprojection();
}

 /**
  * @brief check if there is collision with anything from scene
  * @return true if there is collision, false if not
  */
 std::string Drone::Collision()
 {
    std::string a = "";
    for(auto& object: whereIAm->Objects())
        if(object->WhoIAm() != Figure::Type::BrokenLine && object->WhoIAm() != Figure::Type::Surface &&
                    this != object.get() && (object->OXYprojection() | OXYprojection()) )
        {
            
            a = object->WhoIAmText();
            break;
        }
    
    
    return a;
 }