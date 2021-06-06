#include "Vector.hpp"
#include <cassert>
#include <cmath>
#include <limits>

template<std::size_t SIZE>
int Vector<SIZE>::hmvn = 0;

template<std::size_t SIZE>
int Vector<SIZE>::hmvt = 0;
/**
 * @file
 * @brief Definicje szablonów klasy Vector
 */

/**
 * Możemy za jego pomocą dostać się do poszczególnych współrzędnych wektora.
 * Umożliwa on dostęp do współrzędnych, bez możliwości modyfikacji.
 * Gdy indeks jest spoza zakresu [0;SIZE] zostanie rzucony wyjątek std::out_of_range
 *
 * @tparam SIZE - Określa wymiarowość w jakiej znajduje się wektor
 * @param n - indeks współrzędnej do której chcemy uzyskać dostęp
 * @return Niemodyfikowalna wartość określonej indeksem współrzędnej
 */
template<size_t SIZE>
const double& Vector<SIZE>::operator[](unsigned int n) const
{
	if (n < 0 || n >= SIZE)
		throw std::out_of_range{"Vector<" + std::to_string(SIZE) + "> out of range!"};
	return tab[n];
}

/**
 * Możemy za jego pomocą dostać się do poszczególnych współrzędnych wektora.
 * Umożliwa on dostęp do współrzędnych, z możliwością modyfikacji.
 * Gdy indeks jest spoza zakresu [0;SIZE] zostanie rzucony wyjątek std::out_of_range
 *
 * @tparam SIZE - Określa wymiarowość w jakiej znajduje się wektor
 * @param n - indeks współrzędnej do której chcemy uzyskać dostęp
 * @return Modyfikowalna referencjado  określonej indeksem współrzędnej
 */
template<size_t SIZE>
double& Vector<SIZE>::operator[](unsigned int n)
{
	if (n < 0 || n >= SIZE)
		throw std::out_of_range{ "Vector<" + std::to_string(SIZE) + "> out of range!" };
	return tab[n];
}

/**
 * Dodaje odpowiednie składowe dwóch wektorów i zwraca wynik.
 *
 * @tparam SIZE - Określa wymiar wektora
 * @param second - Vector który dodajemy
 * @return Zwraca wynik dodawania dwóch wektorów
 */
template<size_t SIZE>
Vector<SIZE> Vector<SIZE>::operator+(const Vector<SIZE>& second) const
{
	Vector<SIZE> temp(*this);
	for (uint16_t i = 0; i < SIZE; ++i)
		temp[i] += second[i];

	return temp;
}

/**
 * Odejmuje odpowiednie składowe dwóch wektorów i zwraca wynik.
 *
 * @tparam SIZE - Określa wymiar wektora
 * @param second - Vector który odejmujemy
 * @return Zwraca wynik odejmowania dwóch wektorów
 */
template<size_t SIZE>
Vector<SIZE> Vector<SIZE>::operator-(const Vector<SIZE>& second) const
{
	Vector<SIZE> temp(*this);
	for (uint16_t i = 0; i < SIZE; ++i)
		temp[i] -= second[i];

	return temp;
}

/**
 * Mnoży wszystkie składowe wektora przez przysłaną stałą.
 *
 * @tparam SIZE - Określa wymiar wektora
 * @param st - stała przez którą mnożymy
 * @return Zwraca wynik przemnożenia wektora przez stałą.
 */
template<size_t SIZE>
Vector<SIZE> Vector<SIZE>::operator*(double st) const
{
	Vector<SIZE> temp(*this);
	for (uint16_t i = 0; i < SIZE; ++i)
		temp[i] *= st;

	return temp;
}

/**
 *
 * @tparam SIZE - Określa wymiar wektora
 * @return Zwraca długość wektora
 */
template<size_t SIZE>
double Vector<SIZE>::Length() const
{
	double sum = 0;
	for (uint16_t i = 0; i < SIZE; ++i)
		sum += pow(tab[i], 2);

	return sqrt(sum);
}

/**
 * Funkcja kopiująca wartości współrzędnych wektora do innego obiektu tej samej klasy
 * Jeśli spróbujemy wpisać obiekt do samego siebie, funkcja jedynie zwróci referencję do samego siebie.
 *
 * @tparam SIZE - Określa wymiar wektora
 * @param drugi - Obiekt z którego kopiujemy wartości współrzędnych
 * @return Zwraca referencję do obiektu do którego wpisywalismy dane
 */
template<std::size_t SIZE>
Vector<SIZE> &Vector<SIZE>::operator=(const Vector<SIZE> &drugi)
{
    if(&drugi == this)
        return (*this);
    
    for(uint16_t i = 0;i<SIZE;++i)
        tab[i] = drugi[i];
    
    return (*this);
}

/**
 * Funkcja kopiująca wartości współrzędnych wektora do innego obiektu tej samej klasy
 * Jeśli spróbujemy wpisać obiekt do samego siebie, funkcja jedynie zwróci referencję do samego siebie.
 *
 * @tparam SIZE - Określa wymiar wektora
 * @param drugi - Obiekt z którego kopiujemy wartości współrzędnych
 * @return Zwraca referencję do obiektu do którego wpisywalismy dane
 */
template<std::size_t SIZE>
Vector<SIZE>& Vector<SIZE>::operator=(Vector<SIZE>&& drugi) noexcept
 {
    if(&drugi == this)
        return (*this);
    
    for(uint16_t i = 0;i<SIZE;++i)
        tab[i] = drugi[i];
    
    return (*this);
}

/**
 * Wczytanie wektora z odpowiedniego strumienia
 *
 * @param strm - strumien z którego ma zostać wczytany wektor
 * @param wek - wektor który ma zostać wczytany
 * @return zwracamy referencję do przysłanego strumienia
 */
template<size_t SIZE>
std::istream& operator >> (std::istream& strm, Vector<SIZE>& wek)
{
	double x;
    Vector<SIZE> temp;
	for (uint16_t i = 0; i < SIZE; ++i)
	{
		strm >> x;
		if (!strm.good())
		{
			strm.clear();
			strm.ignore(std::numeric_limits<int>::max(), '\n');
			throw std::runtime_error("Nie udalo sie wczytac Wektora<" + std::to_string(SIZE) + ">!");
		}
		temp[i] = x;
	}
    wek = temp;
	return strm;
}

/**
 * Wypisanie wektora na odpowiedni strumień
 *
 * @param strm - strumien na który ma zostać wypisany wektor
 * @param wek - wektor który ma zostać wypisany
 * @return zwracamy referencję do przysłanego strumienia
 */
template <size_t SIZE>
std::ostream& operator << (std::ostream& strm, const Vector<SIZE>& wek)
{
	for (uint16_t i = 0; i < SIZE; ++i)
		strm << std::setw(16) << std::fixed << std::setprecision(8) << wek[i] << (i == SIZE - 1 ? " " : "");

	return strm;
}
