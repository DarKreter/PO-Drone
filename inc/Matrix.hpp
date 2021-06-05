#ifndef MACIERZ_H
#define MACIERZ_H

/**
 * @file
 * @brief Definicja klasy Matrix
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
class Matrix
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
    Matrix();
    
    Matrix(std::array<Vector<SIZE>, SIZE>);

    
    /**
     * @brief Konstruktor kopiujący
     */
    Matrix(const Matrix<SIZE>& druga);
    
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
    Matrix<SIZE> operator*(const Matrix<SIZE>&) const;
    
    /**
     * @brief Kopiujący operator przypisania
     */
    Matrix<SIZE>& operator=(const Matrix<SIZE>& drugi);
    
};

/**
 * @brief  Wpisuje macierz rotacji do strumienia.
 */
template<size_t SIZE>
std::ostream& operator<<(std::ostream& strm, const Matrix<SIZE>& mac);

#include "Matrix.tpp"

#endif
