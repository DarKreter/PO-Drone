//
// Created by darkr on 19.06.2021.
//

#ifndef DRONE_RECTANGLE_HPP
#define DRONE_RECTANGLE_HPP
#include <Vector.hpp>
#include <utility>

/**
 * @file
 * @brief Definicja klasy Rectangle
 */

/**
 * @brief Klasa modeluje pojęcie prostokąta
 */
class Rectangle
{
    /**
     * @brief Tablica 4 wierzchołków prostokąta
     */
    std::array<Vector3D, 4> vertices;
    
public:
    /**
     * @brief Konstruktor tworzący prostokąt na podstawie 4 wierzchołków
     * @param a - tablica 4 wierzchołków
     */
    explicit Rectangle(std::array<Vector3D, 4> a): vertices(std::move(a)) {}
    /**
     * @brief Tworzy prostokąt na podstawie jego zakresu na osiach X i Y
     */
    explicit Rectangle(double x1, double x2, double y1, double y2);
    
    /**
     * @brief Operator dostępowy do wierzchołków prostokąta
     */
    Vector3D operator[](std::size_t n) const;
    
    /**
     * @brief Operator dostępowy do wierzchołków prostokąta
     */
    Vector3D& operator[] (std::size_t n);
    
    /**
     * @brief Operator kolizji
     */
    bool operator|(const Rectangle& r);
};


#endif //DRONE_RECTANGLE_HPP
