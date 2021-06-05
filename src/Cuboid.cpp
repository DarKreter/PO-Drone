#include "Cuboid.hpp"
#include <fstream>
#include <iomanip>

/**
 * @file
 * @brief Definicje funkcji składowych klasy Cuboid
 */

/**
 * Wszystkie wierzchołki zostają wczytane bezpośrednio z pliku.
 *
 * @param name - nazwa pliku który zostanie otworzony i zostaną z niego
 * wczytane wszystkie wierzchołki
 */
Cuboid::Cuboid(std::string name): Figure(name)
{
    std::ifstream str(name);
    str >> (*this);
    str.close();
}



/**
 * Możemy za jego pomocą dostać się do poszczególnych wierzchołków prostopadłościanu.
 * Umożliwa on dostęp do wierzchołków, bez możliwości modyfikacji.
 * Gdy indeks jest spoza zakresu [0;7] zostanie rzucony wyjątek std::out_of_range
 *
 * @param n - indeks wierzchołka do którego chcemy uzyskać dostęp
 * @return zwraca odpowiedni niemodyfikowalny wierzchołek prostopadłościanu
 */
const Vector3D& Cuboid::operator[](unsigned int n) const
{
	if (n < 0 || n > 7)
		throw std::out_of_range{ "Cuboid out of range!" };

	return vertices[n];
}

/**
 * Możemy za jego pomocą dostać się do poszczególnych wierzchołków prostopadłościanu.
 * Umożliwa on modifikację wierzchołków.
 * Gdy indeks jest spoza zakresu [0;7] zostanie rzucony wyjątek std::out_of_range
 *
 * @param n - indeks wierzchołka do którego chcemy uzyskać dostęp
 * @return zwraca referencję do wierzchołka prostopadłościanu który chcemy zmodyfikować
 */
Vector3D& Cuboid::operator[](unsigned int n)
{
	if (n < 0 || n > 7)
		throw std::out_of_range{ "Cuboid out of range!" };

	return vertices[n];
}

/**
 * Rotacja jest wykonywana na podstawie macierzy rotacji.
 * Na kolejnych wierzchołkach jest wykonywana operacja mnożenia przez macierz rotacji.
 *
 * @param mRotacji - wyspecjalizowana macierz rotacji zainicjalizowana już odpowiednimi wartości.
 */
void Cuboid::Rotation(MatrixRot3x3 mRotacji)
{
	for (int i = 0; i < 8; ++i)
        vertices[i] = mRotacji * vertices[i];

}

/**
 * Realizuje translację prostopadłościanu o zadany wektor
 * Do kolejnych wierzchołków jest dodawany wektor translacyjny.
 *
 * @param wektor -  wyspecjalizowany wektor translacji, z zainicjowanymi wartościami.
 */
void Cuboid::Translation(Vector3D wektor)
{
	for (int i = 0; i < 8; ++i)
        vertices[i] = vertices[i] + wektor;
}

void Cuboid::Draw()
{
    std::ofstream str(fileName);
    str << (*this) << std::endl << vertices[0] << std::endl << vertices[1];
    str.close();
}

/**
 * Wypisanie Figury na odpowiedni strumień
 *
 * @param strm - strumien na który ma zostać wypisany prostopadłościan
 * @param pr - prostopadłościan który ma zostać wypisany
 * @return zwracamy referencję do przysłanego strumienia
 */
std::ostream& operator<<(std::ostream& strm, const Cuboid& pr)
{
    for (int i = 0; i < 8; ++i)
        strm << pr[i] << (i==7?"":"\n") << (i%2==1?"\n":"");

    return strm;
}

/**
 * Wczytanie Figury z odpowiedniego strumienia
 *
 * @param strm - strumien z którego ma zostać wczytany prostopadłościan
 * @param pr - prostopadłościan który ma zostać wczytany
 * @return zwracamy referencję do przysłanego strumienia
 */
std::istream& operator>>(std::istream& strm, Cuboid& pr)
{
    for (int i = 0; i < 8; ++i)
        strm >> pr[i];

    return strm;
}

