#ifndef PROSTOPADLOSCIAN_HH
#define PROSTOPADLOSCIAN_HH

/*!
 * \file
 * \brief Definicja klasy Cuboid
 *
 */

#include <iostream>
#include <Matrix.hpp>
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
	std::array<Vector3D, 8> vertices;

public:
    /**
     * \brief Inicjalizuje wierzchołki prostopadłościanu, na podstawie danych z pliku.
     */
    explicit Cuboid(std::string name);
    

    /**
     * \brief Operator dostępowy do wierzchołków prostopadłościanu
     */
	const Vector3D& operator[](unsigned int n) const;
    /**
    * \brief Operator dostępowy do wierzchołków prostopadłościanu
    */
    Vector3D& operator[](unsigned int n);

    /**
     * \brief  Rotacja bryły.
     */
	void Rotation(MatrixRot3x3 mRotacji);

    /**
     * \brief  Translacja bryły.
     */
	void Translation(Vector3D wektor) override;
	
	void Draw() override;

};

/**
 * \brief  Wpisuje prostopadłościan do strumienia.
 */
std::ostream& operator << (std::ostream& strm, const Cuboid& pr);

/**
 * \brief  Wczytuje prostopadłościan ze strumienia.
 */
std::istream& operator >> (std::istream& strm, Cuboid& pr);

#endif
