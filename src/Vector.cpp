//
// Created by darkr on 08.06.2021.
//
#include<Vector.hpp>

template <>
std::ostream& operator << (std::ostream& strm, const Vector<2>& wek)
{
    strm << "(";
    for (uint16_t i = 0; i < 2; ++i)
        strm << std::setw(6) << wek[i] << (i == 2 - 1 ? ")" : ";");

    return strm;
}

/**
 * Wypisanie wektora na odpowiedni strumień
 *
 * @param strm - strumien na który ma zostać wypisany wektor
 * @param wek - wektor który ma zostać wypisany
 * @return zwracamy referencję do przysłanego strumienia
 */
template <>
std::ostream& operator << (std::ostream& strm, const Vector<3>& wek)
{
    for (uint16_t i = 0; i < 3; ++i)
        strm << std::setw(16) << std::fixed << std::setprecision(8) << wek[i] << (i == 3 - 1 ? " " : "");
    
    return strm;
}