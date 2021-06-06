#ifndef PROSTOPADLOSCIAN_HH
#define PROSTOPADLOSCIAN_HH

/*!
 * \file
 * \brief Definicja klasy Cuboid
 *
 */

#include <iostream>
#include <MatrixRot.hpp>
#include <Vector.hpp>
#include "MatrixRot.hpp"
#include "Figure.hpp"

/**
 * \brief Modeluje pojęcie Prostopadłościanu
 *
 * Przechowuje 8 wierzchołków prostopadłościanu w tablicy.
 * Dostarcza narzędzia do przesuwania go w przestrzeni o wektor
 * oraz obrót o zadany kąt względem danej osi układu współrzędnych.
 * Pozwala także na wygodne wypisanie i wczytanie go ze strumienia standardowego.
 */
class Cuboid: public Figure
{
    /**
     * \brief Tablica przechowująca 8 wierzchołków prostopadłościanu
     *
     * Prostopadłościan jest zlokalizowany w przestrzeni 3D
     * Pojedyńczy punkt jest zmodelowany za pomocą klasy Vector3D
     */
    double width, length, height;

public:
    /**
     * \brief Inicjalizuje wierzchołki prostopadłościanu, na podstawie danych z pliku.
     */
    explicit Cuboid(const Vector3D& localCenter, double w, double l, double h, const MatrixRot3x3& matRot = MatrixRot3x3());
    
    std::vector<Vector3D>& CalcLocalCoords(std::vector<Vector3D>&) override;
    
};


#endif
