//
// Created by darkr on 08.06.2021.
//

#include "../inc/Plateau.hpp"
#include <fstream>
#include <vector>


/**
 * @file
 * @brief Definicje funkcji składowych klasy Plateau
 */

/**
 * Konstruuje płaskowyż na podstawie przysłanych danych
 *
 * @param scene - scena w której znajduje się dana bryła
 * @param localCenter - środek tej bryły
 * @param w - szerokość
 * @param l - długość
 * @param h - wysokość
 * @param matRot - Macierz rotacji lokalna wokół której orientujemy bryłe
 * @param rotCen - środek wokół którego robimy obrót globalny
 */
Plateau::Plateau(Scene *scene, const Vector3D &localCenter, double w, double l, double h, const MatrixRot3x3 &matRot, Vector3D* rotCen)
        : Figure(scene, "SomethingWentWrong.jpg", 4, Type::Plateau, matRot, localCenter, rotCen), width{w}, length{l}, height{h}
{}

/**
 * Przeliczenie wierzchołków lokalnych
 *
 * @param vertices - wektor gdzie zapiszemy wierzchołki
 * @return - przeliczone wierzchołki
 */
std::vector<Vector3D>& Plateau::CalcLocalCoords(std::vector<Vector3D>& vertices)
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
                    vertex[2] = height;
                else
                    vertex[2] = 0;
                
                if(i == 1 || i == 2)
                    vertex[0] = halfLength;
                else
                    vertex[0] = -halfLength;
            }
            
            vertices.push_back(vertex);
        }
    
    return vertices;
}



