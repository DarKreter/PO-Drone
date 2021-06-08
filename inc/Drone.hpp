//
// Created by darkr on 06.06.2021.
//
#ifndef DRONE_DRONE_HPP
#define DRONE_DRONE_HPP
#include <memory>
#include <MatrixRot.hpp>
#include <Cuboid.hpp>
#include <Prism.hpp>
#include <BrokenLine.hpp>


class Drone: public Figure
{
private:
    std::shared_ptr<Cuboid> body, light1, light2;
    std::array<std::shared_ptr<Prism>,4> rotors;

public:

    explicit Drone(Scene* scene, const Vector3D& localCenter, double wid, double len, double hei, const MatrixRot3x3& matRot = MatrixRot3x3());
    
    std::vector<Vector3D>& CalcLocalCoords(std::vector<Vector3D>&) override;
    
    void Translation(Vector3D wektor, double speed) override;
    void TranslationRaw(const Vector3D& wektor) override;
    
    void Rotation(double angle, MatrixRot3x3::Axis axis,  double speed);
    void RotationRaw(const MatrixRot3x3& macRot);
    
    void Draw() override;
    
    void Route(double nr, double angle);
    std::shared_ptr<BrokenLine> CreateRoute(double nr, double angle);
    
    void SetCenter();
    void ClearCenter();
};


#endif //DRONE_DRONE_HPP
