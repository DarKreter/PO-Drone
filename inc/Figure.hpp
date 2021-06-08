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
#include <memory>

class Scene;

class Figure
{
protected:
    std::string fileName;
    uint8_t fileNewLine;
    
    MatrixRot3x3 localOrientation, globalOrientation;
    Vector3D localCoordCenter;
    const Vector3D* rotationCenter;
    
    Scene* whereIAm;
    
    static std::uint16_t count;
    
    explicit Figure(Scene* scene, std::string fn, uint8_t fnl, const MatrixRot3x3 &matRot,
                    Vector3D localCenter, Vector3D* rotationCentr = nullptr);
    
    template<typename T>
    void Animate(std::function<void(double)>function, T arg, double speed, double frequency);
    
    //Wyliczyć wszystkie punkty bryły
    virtual std::vector<Vector3D>& CalcLocalCoords(std::vector<Vector3D>&) = 0;
    
    bool nested = false;
    
public:
    //Przeliczyć je na układ globalny (mnożenie przez macierz plus translacja o środek)
    void CalcGlobalCoords(std::vector<Vector3D>& vertices);
    
    virtual void Draw();
    
    virtual void Translation(Vector3D wektor, double speed);
    virtual void TranslationRaw(const Vector3D& wektor);
    
    virtual void RotationGlobal(double angle, MatrixRot3x3::Axis axis,  double speed);
    virtual void RotationLocal(double angle, MatrixRot3x3::Axis axis,  double speed);
    virtual void RotationRawLocal(const MatrixRot3x3& macRot);
    virtual void RotationRawGlobal(const MatrixRot3x3& macRot);
    

    std::string FileName(std::string sf) {return fileName = sf;}
    void SetScene(Scene*s) {whereIAm = s;}
    void Nested() { nested = true; }
    Vector3D LocalCoordCenter() { return localCoordCenter; }
    MatrixRot3x3 GlobalOrientation() { return globalOrientation; }
    void RotationCenter(Vector3D* w) {rotationCenter = w;}
    void ClearRotationCenter() {rotationCenter = &localCoordCenter;}

    ~Figure();
};

#include<Figure.tpp>

#endif //DRONE_FIGURE_HPP
