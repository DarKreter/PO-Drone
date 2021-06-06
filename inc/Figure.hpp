//
// Created by darkr on 05.06.2021.
//

#ifndef DRONE_FIGURE_HPP
#define DRONE_FIGURE_HPP

#include <string>
#include <utility>
#include <unistd.h>
#include <Vector.hpp>
#include <MatrixRot.hpp>
#include <vector>
#include <functional>

class Figure
{
protected:
    std::string fileName;
    bool readyToDraw;
    
    MatrixRot3x3 orientation;
    Vector3D localCoordCenter;
    
    explicit Figure(std::string fn, const MatrixRot3x3& matRot, const Vector3D& localCenter);
    
    template<typename T>
    void Animate(std::function<void(double)>function, T arg, double speed);
    
    //Wyliczyć wszystkie punkty bryły
    virtual std::vector<Vector3D>& CalcLocalCoords(std::vector<Vector3D>&) = 0;
    
    //Przeliczyć je na układ globalny (mnożenie przez macierz plus translacja o środek)
    void CalcGlobalCoords(std::vector<Vector3D>& vertices);
    
public:
    void ReadyToDraw(bool rtd) { readyToDraw = rtd;}
    bool ReadyToDraw() { return readyToDraw;}
    
    
    
    //Zapisać je do pliku w konkretnej kolejności
    void Draw();
    
    
    void Translation(Vector3D wektor, double speed);
    //Translacja środka układu o wektor
    void TranslationRaw(const Vector3D& wektor);
    
    void Rotation(double angle, MatrixRot3x3::Axis axis,  double speed);
    //Zmiana macierzy rotacji przez przemnożenie ich przez siebie
    //NowaMacierz * StaraMacierz
    void RotationRaw(const MatrixRot3x3& macRot);
    

    std::string FileName(std::string sf) {return fileName = sf;}
};


std::ostream& operator<<(std::ostream& strm, const std::vector<Vector3D>& pr);

#include<Figure.tpp>

#endif //DRONE_FIGURE_HPP
