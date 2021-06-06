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
class Scene;

class Figure
{
protected:
    std::string fileName;
    uint8_t fileNewLine;
    
    MatrixRot3x3 orientation;
    Vector3D localCoordCenter;
    
    Scene* whereIAm;
    
    
    explicit Figure(std::string fn, uint8_t fnl, const MatrixRot3x3 &matRot, const Vector3D &localCenter);
    
    template<typename T>
    void Animate(std::function<void(double)>function, T arg, double speed, double frequency);
    
    //Wyliczyć wszystkie punkty bryły
    virtual std::vector<Vector3D>& CalcLocalCoords(std::vector<Vector3D>&) = 0;
    
    //Przeliczyć je na układ globalny (mnożenie przez macierz plus translacja o środek)
    void CalcGlobalCoords(std::vector<Vector3D>& vertices);
    
    
public:
    
    virtual void Draw();
    
    void Translation(Vector3D wektor, double speed);
    void TranslationRaw(const Vector3D& wektor);
    
    void Rotation(double angle, MatrixRot3x3::Axis axis,  double speed);
    void RotationRaw(const MatrixRot3x3& macRot);
    

    std::string FileName(std::string sf) {return fileName = sf;}
    void SetScene(Scene*s) {whereIAm = s;}
};

#include<Figure.tpp>

#endif //DRONE_FIGURE_HPP
