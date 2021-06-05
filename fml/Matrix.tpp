#include "Matrix.hpp"
#include <cmath>

/**
 * @file
 * @brief Definicje szablonów klasy Matrix
 */

/**
 * Tworzy macierz rotacji na podstawie innego obiektu klasy Matrix o tym samym rozmiarze
 *
 * @tparam SIZE - Określa wymiar macierzy rotacji
 * @param druga - niemodyfikowalna referencja do obiektu z którego będziemy kopiować
 */
template<size_t SIZE>
Matrix<SIZE>::Matrix(const Matrix<SIZE> &druga)
{
    for(std::size_t i=0; i<SIZE;++i)
        tab[i] = druga[i];
}

/**
 *  Inicjalizuje macierz rotacji jako macierz jednostokowa
 *
 * @tparam SIZE - Określa wymiar macierzy rotacji
 */
template<size_t SIZE>
Matrix<SIZE>::Matrix(): tab{}
{
    for(std::size_t i=0;i<SIZE;++i)
        tab[i][i] = 1;
}

/**
 * Funkcja kopiująca wartości wiersze macierzy do innego obiektu tej samej klasy
 * Jeśli spróbujemy wpisać obiekt do samego siebie, funkcja jedynie zwróci referencję do samego siebie.
 *
 * @tparam SIZE - Określa wymiar obu macierzy rotacji
 * @param drugi - Obiekt z którego kopiujemy wartości współrzędnych
 * @return Zwraca referencję do obiektu do którego wpisywalismy dane
 */
template<std::size_t SIZE>
Matrix<SIZE> &Matrix<SIZE>::operator=(const Matrix<SIZE> &drugi)
{
    if(&drugi == this)
        return (*this);
    
    for(std::size_t i = 0;i<SIZE;++i)
        tab[i] = drugi[i];
    
    return (*this);
}

/**
 * Możemy za jego pomocą dostać się do poszczególnych wierszów macierzy rotacji.
 * Umożliwa on dostęp do wierszy, bez możliwości modyfikacji.
 * Gdy indeks jest spoza zakresu [0;SIZE] zostanie rzucony wyjątek std::out_of_range
 *
 * @tparam SIZE - Określa wymiar macierzy rotacji
 * @param n - indeks wiersza do którego chcemy uzyskać dostęp
 * @return zwraca odpowiedni niemodyfikowalny wiersz macierzy rotacji
 */
template<size_t SIZE>
const Vector<SIZE>& Matrix<SIZE>::operator[](unsigned int n) const
{
	if (n < 0 || n >= SIZE)
		throw std::out_of_range{ "Matrix<" + std::to_string(SIZE) + "> out of range!" };

	return tab[n];
}

/**
 * Możemy za jego pomocą dostać się do poszczególnych wierszów macierzy rotacji.
 * Umożliwa on modifikację wierszy.
 * Gdy indeks jest spoza zakresu [0;SIZE] zostanie rzucony wyjątek std::out_of_range
 *
 * @tparam SIZE - Określa wymiar macierzy rotacji
 * @param n - indeks wiersza do którego chcemy uzyskać dostęp
 * @return zwraca referencję do wiersza macierzy rotacji który chcemy zmodyfikować
 */
template<size_t SIZE>
Vector<SIZE>& Matrix<SIZE>::operator[](unsigned int n)
{
	if (n < 0 || n >= SIZE)
		throw std::out_of_range{ "Matrix<" + std::to_string(SIZE) + "> out of range!" };

	return tab[n];
}

/**
 * Mnoży odpowiednie składowe macierzy z odpowiednimi składowymi wektora.
 *
 * @tparam SIZE - Określa wymiar macierzy rotacji oraz rozmiar wektora
 * @param v - wektor przez który chcemy przemnożyć macierz
 * @return Zwracamy wektor który jest wynikiem mnożenia
 */
template<size_t SIZE>
Vector<SIZE> Matrix<SIZE>::operator*(const Vector<SIZE>& v) const
{
	Vector<SIZE> temp;

	for (std::size_t i = 0; i < SIZE; ++i)
		for (std::size_t j = 0; j < SIZE; ++j)
			temp[i] += v[j] * tab[i][j];

	return temp;
}

/**
 * Mnoży odpowiednie składowe macierzy z odpowiednimi składowymi drugiej macierzy.
 *
 * @tparam SIZE - Określa wymiar obu macierzy rotacji
 * @param v - macierz przez którą chcemy przemnożyć pierwszą macierz
 * @return Zwracamy macierz która jest wynikiem mnożenia
 */
template<size_t SIZE>
Matrix<SIZE> Matrix<SIZE>::operator*(const Matrix<SIZE>& m) const
{
	Matrix<SIZE> temp;
    for (std::size_t  w = 0; w < SIZE; ++w)
        temp[w][w] = 0;;
    
	for (std::size_t  i = 0; i < SIZE; ++i)
		for (std::size_t j = 0; j < SIZE; ++j)
			for (std::size_t k = 0; k < SIZE; ++k)
				temp[i][j] += tab[i][k] * m[k][j];

	return temp;
}

template<size_t SIZE>
Matrix<SIZE>::Matrix(std::array<Vector<SIZE>, SIZE> a): tab{a}
{}

/**
 * Wypisanie macierzy rotacji na odpowiedni strumień
 *
 * @param strm - strumień na który ma zostać wypisana macierz
 * @param mac - macierz rotacji która zostanie wpisana do strumienia
 * @return Zwracamy referencję do przysłanego strumienia
 */
template<size_t SIZE>
std::ostream& operator<<(std::ostream& strm, const Matrix<SIZE>& mac)
{
	for (std::size_t i = 0; i < SIZE; ++i)
		std::cout << mac[i] << (i == SIZE-1? " ": "\n");

	return strm;
}
