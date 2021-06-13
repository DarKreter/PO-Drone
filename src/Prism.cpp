//
// Created by darkr on 06.06.2021.
//

#include "Prism.hpp"
#include <vector>
/**
 * @file
 * @brief Definicje funkcji składowych klasy Prism
 */

/**
 * Konstruuje obiekt na podstawie przyslanych danych
 *
 * @param scene - wskaznik na scene w ktorej znajduje sie obiekt
 * @param localCenter - lokalny srodek bryły
 * @param r - promień graniastosłupa
 * @param h - wysokość
 * @param matRot - orientacja bryły w postaci macierzy rotacji
 */


Prism::Prism(Scene *scene, const Vector3D &localCenter, double r, double h, const MatrixRot3x3 &matRot)
        : Figure(scene, "SomethingWentWrong.jpg", 4, Type::Prism, matRot, localCenter), radius{r}, height{h}
{}

/**
 * Obliczenie lokalnych wierzchołków
 *
 * @param vertices - Wektor gdzie zapisujemy wszystkie wierzchołki
 * @return - zwracamy przeliczone wierzchołki
 */
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



