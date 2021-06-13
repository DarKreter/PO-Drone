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
 * przechowuje wysokosc dlugosc i szerokosc
 */
class Cuboid: public Figure
{
    /**
     * zmienne okreslajace wymiary prostopadloscianu
     *
     * Prostopadłościan jest zlokalizowany w przestrzeni 3D
     * Pojedyńczy punkt jest zmodelowany za pomocą klasy Vector3D
     */
    double width, length, height;

public:
    /**
     * \brief Inicjalizuje wierzchołki prostopadłościanu, na danych wstepnych
     */
    explicit Cuboid(Scene *scene, const Vector3D &localCenter, double w, double l, double h,
                    const MatrixRot3x3 &matRot, Vector3D* rotCen = nullptr);
    
    /**
     * @brief Przelicza wierzcholki z formy srodka na lokalna
     */
    std::vector<Vector3D>& CalcLocalCoords(std::vector<Vector3D>&) override;
    
    /**
     * @brief Funkcja dostepowa do wysokosci
     * @return zwraca wysokosc
     */
    double Height() {return height;}
    
};


#endif
