#ifndef MACIERZ_H
#define MACIERZ_H

/**
 * @file
 * @brief Definicja klasy MatrixRot
 */

#include <iostream>
#include <Vector.hpp>

/**
 * @brief Modeluje pojęcie macierzy rotacji
 *
 * Macierz rotacji zawsze jest intepretowana jako macierz kwadratowa SIZExSIZE
 *
 * @tparam SIZE - Określa wymiar macierzy rotacji
 */
template<size_t SIZE>
class MatrixRot
{
protected:
    /**
     * @brief Tablica przechowująca wartości wszystkich pól macierzy
     *
     * Składa się ona z wektorów
     */
    std::array<Vector<SIZE>, SIZE> tab;

public:
    /**
     * @brief Określa rodzaj osi wokół której wykonywany będzie obrót
     *
     * Obrót może być wykonany wokół jednej z 3 osi układu współrzędnych
     */
    enum class Axis
    {
        OX /** Oś OX układu współrzędnych */,
        OY /** Oś OY układu współrzędnych */,
        OZ /** Oś OZ układu współrzędnych */
    };
    
    /**
     * @brief Inicjalizacja macierzy rotacji
     */
    MatrixRot();
    
    explicit MatrixRot(std::array<Vector<SIZE>, SIZE>);

    
    /**
     * @brief Inicjalizuje macierz rotacji na podstawie kąta obotu i osi wokół której ma być wykonany obrót
     */
    MatrixRot(double alpha, typename MatrixRot<SIZE>::Axis o);
    
    
    /**
     * @brief Konstruktor kopiujący
     */
    MatrixRot(const MatrixRot<SIZE>& druga);
    
    /**
    * \brief Operator dostępowy do wierszów macierzy
    */
    const Vector<SIZE>& operator[](unsigned int n) const;
    
    /**
    * \brief Operator dostępowy do wierszów macierzy
    */
    Vector<SIZE>& operator[](unsigned int n);

    /**
     * @brief Modeluje pojęcie mnożenia macierzy przez wektor
     */
    Vector<SIZE> operator*(const Vector<SIZE>&) const;
    
    /**
     * @brief Modeluje pojęcie mnozenia macierzy przez inną macierz
     */
    MatrixRot<SIZE> operator*(const MatrixRot<SIZE>&) const;
    
    
    /**
     * @brief Kopiujący operator przypisania
     */
    MatrixRot<SIZE>& operator=(const MatrixRot<SIZE>& drugi);
    
    /**
     * @brief Przenoszący operator przypisania
     */
    MatrixRot<SIZE>& operator=(MatrixRot<SIZE>&& drugi) noexcept ;
    
};

/**
 * @brief  Wpisuje macierz rotacji do strumienia.
 */
template<size_t SIZE>
std::ostream& operator<<(std::ostream& strm, const MatrixRot<SIZE>& mac);


/**
 * @brief Oznaczenie Macierz3x3 jako instancji klasy szablonowej Macierz dla parametru szablonu równego 3
 */
typedef MatrixRot<3>  MatrixRot3x3;

#include "MatrixRot.tpp"

#endif
