//
// Created by darkr on 05.06.2021.
//
#ifndef DRONE_MATRIXROT_HPP
#define DRONE_MATRIXROT_HPP

#include <Matrix.hpp>

template<std::size_t SIZE>
class MatrixRot: public Matrix<SIZE>
{
public:
    /**
     * @brief Inicjalizuje macierz rotacji na podstawie kąta obotu i osi wokół której ma być wykonany obrót
     */
    MatrixRot(double alpha, typename Matrix<SIZE>::Axis o);
};

/**
 * @brief Oznaczenie Macierz3x3 jako instancji klasy szablonowej Macierz dla parametru szablonu równego 3
 */
typedef Matrix<3>  MatrixRot3x3;

#endif //DRONE_MATRIXROT_HPP
