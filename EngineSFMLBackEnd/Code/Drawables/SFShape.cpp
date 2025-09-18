#include "SFShape.h"

#include <Engine/Core/Constants.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <numbers>

SFTriangle::SFTriangle()
{
    SetDrawable(std::make_shared<sf::ConvexShape>(3));
    SetScale(GameConstants::Scale);
    SetFillColour(Colour::Transparent);
    SetOutlineColour(Colour::Red);
    SetOutlineThickness(2);
}

SFTriangle::SFTriangle(const std::array<Vector2f, 3>& points, const Vector2f& pos)
    : SFTriangle()
{
    Reset(points);
    Update(pos);
}

void SFTriangle::Update(const Vector2f& pos)
{
    // unsure as of yet
}

void SFTriangle::Render(IRenderer* renderer)
{
    SFDrawables<sf::ConvexShape>::Render(renderer);
}

void SFTriangle::Reset(const std::array<Vector2f, 3>& points)
{
    SetPoints(points);
}

Vector2f SFTriangle::GetPoint(int idx)
{
    return Vector2f(GetTriangle()->getPoint(idx));
}

Linef SFTriangle::GetLine(int start, int end)
{
    return Linef(GetPoint(start), GetPoint(end));
}

std::array<Vector2f, 3> SFTriangle::GetPoints() const
{
    return std::array<Vector2f, 3>{GetPrimaryDrawable()->getPoint(0),
        GetPrimaryDrawable()->getPoint(1),
        GetPrimaryDrawable()->getPoint(2)};
}

void SFTriangle::SetPoints(const std::array<Vector2f, 3>& points)
{
    auto drawable = GetPrimaryDrawable();
    if (drawable)
    {
        for (int i = 0; i < 3; i++)
            drawable->setPoint(i, points[i]);
    }
}

SFRect::SFRect()
{
	SetDrawable(std::make_shared<sf::RectangleShape>());
	SetScale(GameConstants::Scale);
	SetFillColour(Colour::Transparent);
	SetOutlineColour(Colour::Red);
	SetOutlineThickness(2);
}

SFRect::SFRect(const Vector2f& size, const Vector2f& pos)
    : SFRect()
{
    Reset(size);
    Update(pos);
}

void SFRect::Update(const Vector2f& pos)
{
	SetPosition(pos);
	this->SetCenter(GetPosition());
}

void SFRect::Render(IRenderer* renderer)
{
    SFDrawables<sf::RectangleShape>::Render(renderer);
}

void SFRect::Reset(const Vector2f& size)
{
	SetSize(size);
	SetOrigin(size * 0.5f);
}

SFCircle::SFCircle()
{
	SetDrawable(std::make_shared<sf::CircleShape>());
	SetScale(GameConstants::Scale);
	SetFillColour(Colour::Transparent);
	SetOutlineColour(Colour::Red);
	SetOutlineThickness(2);
}

SFCircle::SFCircle(float radius, const Vector2f& pos)
    : SFCircle()
{
    Reset(radius);
    Update(pos);
}

void SFCircle::Update(const Vector2f& pos)
{
	SetPosition(pos);
	this->SetCenter(GetPosition());
}

void SFCircle::Render(IRenderer* renderer)
{
    SFDrawables<sf::CircleShape>::Render(renderer);
}

void SFCircle::Reset(float radius)
{
	SetRadius(radius);
	SetOrigin(Vector2f(radius, radius));
}

namespace
{
    void CalculateRotatedRectangleCorners(Vector2f corners[4], const Vector2f& centre, const Vector2f& size, float angle)
    {
        float radians = angle * std::numbers::pi_v<float> / 180.0f;
        float cosTheta = cos(radians);
        float sinTheta = sin(radians);
        float halfWidth = size.x / 2.0f;
        float halfHeight = size.y / 2.0f;
        Vector2f relativeCorners[4] =
        {
            { -halfWidth, -halfHeight }, // Bottom-left
            {  halfWidth, -halfHeight }, // Bottom-right
            {  halfWidth,  halfHeight }, // Top-right
            { -halfWidth,  halfHeight }  // Top-left
        };
        for (int i = 0; i < 4; ++i)
        {
            corners[i].x = centre.x + relativeCorners[i].x * cosTheta - relativeCorners[i].y * sinTheta;
            corners[i].y = centre.y + relativeCorners[i].x * sinTheta + relativeCorners[i].y * cosTheta;
        }
    }
}

SFCapsule::SFCapsule()
{
    // Set up primary and secondary drawables
    auto rect = std::make_shared<sf::RectangleShape>();
    SetDrawable(std::static_pointer_cast<sf::Shape>(rect));
    SetFillColour(Colour::Transparent);
    SetOutlineColour(Colour::Red);
    SetOutlineThickness(2);
    SetScale(GameConstants::Scale);

    auto cap1 = std::make_shared<sf::CircleShape>();
    cap1->setFillColor(Colour::Transparent);
    cap1->setOutlineColor(Colour::Red);
    cap1->setOutlineThickness(2);
    cap1->setScale(GameConstants::Scale);
    AddDrawable(std::static_pointer_cast<sf::Shape>(cap1));

    auto cap2 = std::make_shared<sf::CircleShape>();
    cap2->setFillColor(Colour::Transparent);
    cap2->setOutlineColor(Colour::Red);
    cap2->setOutlineThickness(2);
    cap2->setScale(GameConstants::Scale);
    AddDrawable(std::static_pointer_cast<sf::Shape>(cap2));
}

SFCapsule::SFCapsule(float radius, float length, float angle, const Vector2f& pos)
    : SFCapsule()
{
    Reset(radius, length, angle);
    Update(pos);
}

void SFCapsule::Update(const Vector2f& pos)
{
    SetPosition(pos);
    this->SetCenter(pos);

   Vector2f corners[4];
   auto size = GetSize();
   auto scale = GetScale();
   size.x *= scale.x;
   size.y *= scale.y;
   CalculateRotatedRectangleCorners(corners, pos, size, m_angle);

   // Compute endpoints for circles
   Vector2f end1 = Line(corners[3], corners[2]).GetMidPoint(); // top
   Vector2f end2 = Line(corners[1], corners[0]).GetMidPoint(); // bottom

   auto* cap1 = GetEndCap1();
   if (cap1)
       cap1->setPosition(end1);

   auto* cap2 = GetEndCap2();
   if (cap2)
       cap2->setPosition(end2);

   m_segment.start = end1;
   m_segment.end = end2;
}

void SFCapsule::Render(IRenderer* renderer)
{
    SFDrawables<sf::Shape>::Render(renderer);

    if (auto* windowHandle = renderer->GetWindow())
    {
        auto* sfWindow = static_cast<sf::RenderWindow*>(windowHandle->GetNativeHandle());
        if (sfWindow)
        {
            auto endCap1 = GetEndCap1();
            if (endCap1)
            {
                sfWindow->draw(*endCap1);
            }

            auto endCap2 = GetEndCap2();
            if (endCap2)
            {
                sfWindow->draw(*endCap2);
            }
        }
    }
}

void SFCapsule::Reset(float radius, float length, float angle)
{
    m_angle = angle;
    m_radius = radius;
    m_length = length;

    SetSize(Vector2f(radius * 2.f, length));
    SetOrigin({ radius, length / 2.f });
    SetRotation(angle);

    auto* cap1 = GetEndCap1();
    if (cap1)
    {
        cap1->setRadius(radius);
        cap1->setOrigin({ radius, radius });
    }

    auto* cap2 = GetEndCap2();
    if (cap2)
    {
        cap2->setRadius(radius);
        cap2->setOrigin({ radius, radius });
    }
}

sf::RectangleShape* SFCapsule::GetBody()
{
    return this->GetPrimaryDrawableAs<sf::RectangleShape>();
}

sf::CircleShape* SFCapsule::GetEndCap1()
{
    if (this->GetDrawables().size() > 1)
        return dynamic_cast<sf::CircleShape*>(this->GetDrawables()[1].get());
    return nullptr;
}

sf::CircleShape* SFCapsule::GetEndCap2()
{
    if (this->GetDrawables().size() > 2)
        return dynamic_cast<sf::CircleShape*>(this->GetDrawables()[2].get());
    return nullptr;
}

void SFCapsule::Move(float x, float y)
{
    GetBody()->move(Vector2f(x, y));
    GetEndCap1()->move(Vector2f(x, y));
    GetEndCap2()->move(Vector2f(x, y));
}