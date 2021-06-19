//
// Created by darkr on 19.06.2021.
//

#include "Rectangle.hpp"

/**
 * @file
 * @brief Definicje funkcji składowych klasy Rectangle
 */

/**
 * Pozwala na dostęp do wierzchołków prostokąta
 *
 * @param n - indeks wierzchołka do którego chcemy się dostać
 * @return - zwraca Vector3D jako odpowiedni wierzchołek
 */
Vector3D Rectangle::operator[](std::size_t n) const
{
    if(n > 3)
        throw std::out_of_range("Rectangle out of range");
    
    return vertices[n];
}

/**
 * Pozwala na dostęp do wierzchołków prostokąta
 *
 * @param n - indeks wierzchołka do którego chcemy się dostać
 * @return - zwraca Vector3D jako odpowiedni wierzchołek
 */
Vector3D& Rectangle::operator[](std::size_t n)
{
    if(n > 3)
        throw std::out_of_range("Rectangle out of range");
    
    return vertices[n];
}

/**
 * Operator sprawdza czy dwa prostokąty kolidują ze sobą na płaszczyźnie
 *
 * @param r - Drugi prostokąt do porównania
 * @return - zwraca true jesli ze sobą kolidują lub false jeśli nie
 */
bool Rectangle::operator|(const Rectangle &r)
{
    for(const auto& vertex: r.vertices)
        if(vertex[0] >= vertices[0][0] && vertex[0] <= vertices[3][0]
            && vertex[1] >=vertices[0][1] && vertex[1] <= vertices[1][1])
            return true;
    
    for(const auto& vertex: vertices)
        if(vertex[0] >= r.vertices[0][0] && vertex[0] <= r.vertices[3][0]
           && vertex[1] >=r.vertices[0][1] && vertex[1] <= r.vertices[1][1])
            return true;
    
    return false;
}

/**
 * Tworzy obiekt na podstawie zakresu wartości na osiach X i Y
 *
 * @param x1 - minimalna wartość na osi OX
 * @param x2 - maksymalna wartość na osi OX
 * @param y1 - minimalna wartość na osi OY
 * @param y2 - maksymalna wartość na osi OY
 */
Rectangle::Rectangle(double x1, double x2, double y1, double y2):
vertices({Vector3D({x1,y1,0}),
          Vector3D({x1,y2,0}),
          Vector3D({x2,y2,0}),
          Vector3D({x2,y1,0})})
{}
