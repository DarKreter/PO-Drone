//
// Created by darkr on 08.06.2021.
//

#include "Pyramid.hpp"
#include <fstream>
#include <vector>

/**
 * @file
 * @brief Definicje funkcji składowych klasy Pyramid
 */

/**
 * Wytworzenie obiektu klasy Pyramid na podstawie przysłanych danych
 *
 * @param scene - scena w której znajduję się aktualnie bryła
 * @param localCenter - lokalny środek bryły
 * @param w - szerokość
 * @param l - długość
 * @param h - wysokość
 * @param matRot - orietancja bryły wokół własnej osi
 * @param rotCen - srodek wokół którego globalnie będziemy obracać bryłe
 */
Pyramid::Pyramid(Scene *scene, const Vector3D &localCenter, double w, double l, double h, const MatrixRot3x3 &matRot, Vector3D* rotCen)
        : Figure(scene, "SomethingWentWrong.jpg", 4, Type::Pyramid, matRot, localCenter, rotCen), width{w}, length{l}, height{h}
{}

/**
 * Przeliczenie wierzchołków na podstawie środka
 *
 * @param vertices - wektor wierzchołków w którym przechowamy wszytkie wierzchołki
 * @return - zwraca przeliczone wierzchołki
 */
std::vector<Vector3D>& Pyramid::CalcLocalCoords(std::vector<Vector3D>& vertices)
{
    
    double halfWidth = width/2., halfHeight = height/2., halfLength = length/2.;
    
    vertices.push_back(Vector3D({halfWidth/2,0,halfHeight}));
    vertices.push_back(Vector3D({0,0,height}));
    vertices.push_back(Vector3D({0,0,height}));
    vertices.push_back(Vector3D({-halfWidth/2,0,halfHeight}));
    
    vertices.push_back(Vector3D({halfWidth/2,0,halfHeight}));
    vertices.push_back(Vector3D({-halfWidth,halfLength,0}));
    vertices.push_back(Vector3D({halfWidth,halfLength,0}));
    vertices.push_back(Vector3D({-halfWidth/2,0,halfHeight}));
    
    vertices.push_back(Vector3D({halfWidth/2,0,halfHeight}));
    vertices.push_back(Vector3D({-halfWidth,-halfLength,0}));
    vertices.push_back(Vector3D({halfWidth,-halfLength,0}));
    vertices.push_back(Vector3D({-halfWidth/2,0,halfHeight}));
    
    vertices.push_back(Vector3D({halfWidth/2,0,halfHeight}));
    vertices.push_back(Vector3D({0,0,height}));
    vertices.push_back(Vector3D({0,0,height}));
    vertices.push_back(Vector3D({-halfWidth/2,0,halfHeight}));
    
    return vertices;
}



