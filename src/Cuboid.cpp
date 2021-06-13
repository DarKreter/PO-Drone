#include <Cuboid.hpp>
#include <fstream>
#include <vector>


/**
 * @file
 * @brief Definicje funkcji składowych klasy Cuboid
 */


/**
 *  Stworzenie prostopadłościanu na podstawie przyslanych danych
 *
 * @param scene - scena gdzie jest Cuboid
 * @param localCenter - srodek bryły
 * @param w - szerokosc
 * @param l - dlugosc
 * @param h - wysokosc
 * @param matRot - macierz rotacji wokół której obracamy lokalnie bryły
 * @param rotCen - środek rotacji
 */
Cuboid::Cuboid(Scene *scene, const Vector3D &localCenter, double w, double l, double h, const MatrixRot3x3 &matRot, Vector3D* rotCen)
    : Figure(scene, "SomethingWentWrong.jpg", 4, Type::Cuboid, matRot, localCenter, rotCen), width{w}, length{l}, height{h}
{}


/**
 * Przeliczanie wierzchołków z środka i boków
 *
 * @param vertices - wierzchołki gdzie zapiszemy wszystkie wyliczone wierzchołki
 * @return - wyliczone wierzchołki
 */
std::vector<Vector3D>& Cuboid::CalcLocalCoords(std::vector<Vector3D>& vertices)
{
    
    double halfWidth = width/2., halfHeight = height/2., halfLength = length/2.;
    
    MatrixRot3x3 obrot(90,MatrixRot3x3::Axis::OY);
    
    
    Vector3D vertex;
    for(int i = 0;i < 5; i++)
        for(int j = 0; j<4;++j)
        {
            if(j < 2)
                vertex[1] = -halfWidth;
            else
                vertex[1] = halfWidth;
            
            if(j % 3 == 0)
            {
                vertex[2] = 0;
                vertex[0] = 0;
            }
            else
            {
                if(i < 2 || i ==4)
                    vertex[2] = halfHeight;
                else
                    vertex[2] = -halfHeight;
               
                if(i == 1 || i == 2)
                    vertex[0] = halfLength;
                else
                    vertex[0] = -halfLength;
            }
            
            vertices.push_back(vertex);
        }
    
    return vertices;
}



