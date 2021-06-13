//
// Created by darkr on 08.06.2021.
//

#include "RidgeMountain.hpp"
#include <fstream>
#include <vector>

/**
* @file
* @brief Definicje funkcji składowych klasy RidgeMountain
*/

/**
 * Wytworzenie obiektu klasy RidgeMountain na podstawie przysłanych danych
 *
 * @param scene - scena w której znajduję się aktualnie bryła
 * @param localCenter - lokalny środek bryły
 * @param w - szerokość
 * @param l - długość
 * @param h - wysokość
 * @param matRot - orietancja bryły wokół własnej osi
 * @param rotCen - srodek wokół którego globalnie będziemy obracać bryłe
 */
RidgeMountain::RidgeMountain(Scene *scene, const Vector3D &localCenter, double w, double l, double h, const MatrixRot3x3 &matRot, Vector3D* rotCen)
        : Figure(scene, "SomethingWentWrong.jpg", 4, Type::RidgeMountain, matRot, localCenter, rotCen), width{w}, length{l}, height{h}
{}


/**
 * Przeliczenie wierzchołków na podstawie środka
 *
 * @param vertices - wektor wierzchołków w którym przechowamy wszytkie wierzchołki
 * @return - zwraca przeliczone wierzchołki
 */
std::vector<Vector3D>& RidgeMountain::CalcLocalCoords(std::vector<Vector3D>& vertices)
{
    
    double halfWidth = width/2., halfHeight = height/2., halfLength = length/2.;
    

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

                if(i == 3)
                    vertex[0] = -halfLength;
                else
                    vertex[0] = halfLength;
            }

            vertices.push_back(vertex);
        }
    
    return vertices;
}



