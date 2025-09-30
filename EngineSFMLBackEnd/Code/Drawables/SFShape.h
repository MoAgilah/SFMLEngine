#pragma once

#include "SFDrawables.h"
#include <Engine/Interface/Drawables/IShape.h>
#include <Utilities/Line.h>
#include <Utilities/Traits.h>
#include <Utilities/Vector.h>

namespace sf
{
    class Transformable;
    class Shape;
    class ConvexShape;
    class RectangleShape;
    class CircleShape;
}

template<typename TShape>
class SFShape : public SFDrawables<TShape>, public IShape
{
public:

    // IShape (colour/outline)
    Colour GetFillColour() override;
    void SetFillColour(const Colour& col) override;

    Colour GetOutlineColour() override;
    void SetOutlineColour(const Colour& col) override;

    float GetOutlineThickness() override;
    void SetOutlineThickness(float scale) override;

    // Rotation in degrees (we’ll convert to sf::Angle in the .cpp)
    void SetRotation(float rotationDegrees) override;
};

class SFTriangle : public SFShape<sf::ConvexShape>, public ITriangleShape
{
public:
    SFTriangle();
    SFTriangle(const std::array<Vector2f, 3>& points, const Vector2f& pos);

    void Update(const Vector2f& pos) override;
    void Render(IRenderer* renderer) override;

    void Reset(const std::array<Vector2f, 3>& points);

    sf::ConvexShape* GetTriangle();

    Vector2f GetPoint(int idx) override;
    Linef GetLine(int start, int end) override;

    // Returns the three points of the triangle
    std::array<Vector2f, 3> GetPoints() const override;

    // Sets the three points of the triangle
    void SetPoints(const std::array<Vector2f, 3>& points) override;
};

// --- Rectangle Shape ---
class SFRect : public SFShape<sf::RectangleShape>, public IBoxShape
{
public:
    SFRect();
    SFRect(const Vector2f& size, const Vector2f& pos);

    void Update(const Vector2f& pos) override;
    void Render(IRenderer* renderer) override;

    void Reset(const Vector2f& size);

    sf::RectangleShape* GetRect();

    Vector2f GetSize() override;
    void SetSize(const Vector2f& size) override;
};

// --- Circle Shape ---
class SFCircle : public SFShape<sf::CircleShape>, public ICircleShape
{
public:
    SFCircle();
    SFCircle(float radius, const Vector2f& pos);

    void Update(const Vector2f& pos) override;
    void Render(IRenderer* renderer) override;

    void Reset(float radius);

    sf::CircleShape* GetCircle();

    float GetRadius() override;
    void SetRadius(float radius) override;
};

class SFCapsule : public SFShape<sf::Shape>, public ICapsuleShape
{
public:
    SFCapsule();
    SFCapsule(float radius, float length, float angle, const Vector2f& pos);

    void Update(const Vector2f& pos) override;
    void Render(IRenderer* renderer) override;

    void Reset(float radius, float length, float angle);

    // Getters for native drawables
    sf::RectangleShape* GetBody();
    sf::CircleShape* GetEndCap1();
    sf::CircleShape* GetEndCap2();

    void SetSize(const Vector2f& size) override;
};

template <>
struct CapsuleTraits<SFCapsule>
{
    using CircleType = SFCircle;
    using BoxType = SFRect;
};