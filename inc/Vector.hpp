#ifndef WEKTOR_H
#define WEKTOR_H

/**
 * @file
 * @brief Definicja klasy szablonowej Vector
 */

#include <iostream>
#include <array>
#include <iomanip>
#include <string>

/**
 * @brief Modeluje pojęcie Wektora/Punktu w przestrzeni n-wymiarowej
 *
 * Przechuje wszystkie współrzędne wierzchołka w tablicy
 * oraz pozwala wykonywać na nich podstawowe operacje
 *
 * @tparam SIZE - Określa w ilo wymiarowej przestrzeni przechowujemy nasz wektor
 */
template<std::size_t SIZE>
class Vector
{
    /**
     * @brief Tablica przechowująca wszystkie współrzędne wektora
     */
	std::array<double, SIZE> tab;
	static int hmvn;
	static int hmvt;
public:
	static int HowManyVectorsNow();
	static int HowManyVectorsTotal();
	
    /**
     * @brief Inicjalizuje wektor
     *
     * Ustawia wszystkie współrzędne na zera
     */
	Vector(): tab{}										    {hmvn++; hmvt++;}
	
	/**
	 * @brief Inicjalizuje wektor na podstawie wspołrzędnych w tablicy
	 * @param pkt - tablica współrzędnych które zostaną skopiowane do tablicy wektora
	 */
	explicit Vector(std::array<double, SIZE> pkt) : tab{ pkt }		{hmvn++;hmvt++;}
	
	/**
	 * @brief Konstruktor kopiujący
	 *
	 * Tworzy wektor na podstawie innego obiektu klasy wektor o tym samym rozmiarze
	 *
	 * @param temp - niemodyfikowalna referencja do obiektu z którego będziemy kopiować
	 */
	Vector(const Vector<SIZE>& temp) : tab{ temp.tab }		{hmvn++;hmvt++;}
	
	Vector(Vector<SIZE>&& temp)  noexcept : tab{ temp.tab }		{hmvn++;hmvt++;}
    
    /**
    * \brief Operator dostępowy do współrzędnych wektora.
    */
	const double& operator[](unsigned int n) const;
    
    /**
    * \brief Operator dostępowy do współrzędnych wektora.
    */
	double& operator[](unsigned int n);

	/**
	 * @brief Modeluje operacje dodania dwóch wektorów do siebie
	 */
	Vector<SIZE> operator+(const Vector<SIZE>&) const;
    
    /**
     * @brief Modeluje operacje odejmowania dwóch wektorów od siebie
     */
	Vector<SIZE> operator-(const Vector<SIZE>&) const;
	
	/**
	 * @brief Modeluje pojęcie mnożenia wektora przez stałą
	 */
	Vector<SIZE> operator*(double) const;
 
	/**
	 * @brief Modeluje pojęcie kopiującego operatora przypisania
	 */
    Vector<SIZE>& operator=(const Vector<SIZE>& drugi);
	
	/**
     * @brief Modeluje pojęcie kopiującego operatora przypisania
     */
	Vector<SIZE>& operator=(Vector<SIZE>&& drugi) noexcept;
	
    /**
     * @brief Liczy długość wektora
     */
	double Length() const;
	
	operator double()
	{
		return Length();
	}

	virtual ~Vector()	{hmvn--;}
};

/**
 * @brief Oznaczenie Wektora3D jako instancji klasy szablonowej Vector dla parametru szablonu równego 3
 */
typedef Vector<3> Vector3D;

/**
 * \brief  Wczytuje wektor ze strumienia.
 */
template <size_t SIZE>
std::istream& operator >> (std::istream&, Vector<SIZE>&);

/**
 * \brief  Wpisuje wektor do strumienia.
 */
template <size_t SIZE>
std::ostream& operator << (std::ostream&, const Vector<SIZE>&);


#include "Vector.tpp"

#endif
