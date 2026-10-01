#include "CppUnitTest.h"

#include <Engine/Core/Constants.h>
#include <Drawables/SFShape.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Drawables
{
    TEST_CLASS(SFCapsuleTests)
    {
    public:
        // ======================================================
        // Constructors
        // ======================================================

        TEST_METHOD(SFCapsule_DefaultConstructor_SetsShapeDefaults)
        {
            SFCapsule capsule;

            auto scl = capsule.GetScale();

            Assert::AreEqual(GameConstants::Scale.x, scl.x);
            Assert::AreEqual(GameConstants::Scale.y, scl.y);

            auto defFillCol = Colour::Transparent;

            auto fillCol = capsule.GetFillColour();

            Assert::AreEqual(defFillCol.r, fillCol.r);
            Assert::AreEqual(defFillCol.g, fillCol.g);
            Assert::AreEqual(defFillCol.b, fillCol.b);
            Assert::AreEqual(defFillCol.a, fillCol.a);

            auto defOutCol = Colour::Red;

            auto outCol = capsule.GetOutlineColour();

            Assert::AreEqual(defOutCol.r, outCol.r);
            Assert::AreEqual(defOutCol.g, outCol.g);
            Assert::AreEqual(defOutCol.b, outCol.b);
            Assert::AreEqual(defOutCol.a, outCol.a);

            float defThk = 1.0f;

            auto outThk = capsule.GetOutlineThickness();

            Assert::AreEqual(defThk, outThk);
        }

        TEST_METHOD(SFCapsule_DefaultConstructor_CreatesBody)
        {
            SFCapsule capsule;

            auto body = capsule.GetBody();
            Assert::IsNotNull(body);

            auto scl = body->getScale();

            Assert::AreEqual(GameConstants::Scale.x, scl.x);
            Assert::AreEqual(GameConstants::Scale.y, scl.y);

            auto defFillCol = Colour::Transparent;

            auto fillCol = body->getFillColor();

            Assert::AreEqual(defFillCol.r, fillCol.r);
            Assert::AreEqual(defFillCol.g, fillCol.g);
            Assert::AreEqual(defFillCol.b, fillCol.b);
            Assert::AreEqual(defFillCol.a, fillCol.a);

            auto defOutCol = Colour::Red;

            auto outCol = body->getOutlineColor();

            Assert::AreEqual(defOutCol.r, outCol.r);
            Assert::AreEqual(defOutCol.g, outCol.g);
            Assert::AreEqual(defOutCol.b, outCol.b);
            Assert::AreEqual(defOutCol.a, outCol.a);

            float defThk = 1.0f;

            auto outThk = body->getOutlineThickness();

            Assert::AreEqual(defThk, outThk);
        }

        TEST_METHOD(SFCapsule_DefaultConstructor_CreatesEndCap1)
        {
            SFCapsule capsule;

            auto endCap1 = capsule.GetEndCap1();
            Assert::IsNotNull(endCap1);

            auto scl = endCap1->getScale();

            Assert::AreEqual(GameConstants::Scale.x, scl.x);
            Assert::AreEqual(GameConstants::Scale.y, scl.y);

            auto defFillCol = Colour::Transparent;

            auto fillCol = endCap1->getFillColor();

            Assert::AreEqual(defFillCol.r, fillCol.r);
            Assert::AreEqual(defFillCol.g, fillCol.g);
            Assert::AreEqual(defFillCol.b, fillCol.b);
            Assert::AreEqual(defFillCol.a, fillCol.a);

            auto defOutCol = Colour::Red;

            auto outCol = endCap1->getOutlineColor();

            Assert::AreEqual(defOutCol.r, outCol.r);
            Assert::AreEqual(defOutCol.g, outCol.g);
            Assert::AreEqual(defOutCol.b, outCol.b);
            Assert::AreEqual(defOutCol.a, outCol.a);

            float defThk = 1.0f;

            auto outThk = endCap1->getOutlineThickness();

            Assert::AreEqual(defThk, outThk);
        }

        TEST_METHOD(SFCapsule_DefaultConstructor_CreatesEndCap2)
        {
            SFCapsule capsule;

            auto endCap2 = capsule.GetEndCap2();
            Assert::IsNotNull(endCap2);

            auto scl = endCap2->getScale();

            Assert::AreEqual(GameConstants::Scale.x, scl.x);
            Assert::AreEqual(GameConstants::Scale.y, scl.y);

            auto defFillCol = Colour::Transparent;

            auto fillCol = endCap2->getFillColor();

            Assert::AreEqual(defFillCol.r, fillCol.r);
            Assert::AreEqual(defFillCol.g, fillCol.g);
            Assert::AreEqual(defFillCol.b, fillCol.b);
            Assert::AreEqual(defFillCol.a, fillCol.a);

            auto defOutCol = Colour::Red;

            auto outCol = endCap2->getOutlineColor();

            Assert::AreEqual(defOutCol.r, outCol.r);
            Assert::AreEqual(defOutCol.g, outCol.g);
            Assert::AreEqual(defOutCol.b, outCol.b);
            Assert::AreEqual(defOutCol.a, outCol.a);

            float defThk = 1.0f;

            auto outThk = endCap2->getOutlineThickness();

            Assert::AreEqual(defThk, outThk);
        }

        TEST_METHOD(SFCapsule_ParameterizedConstructor_SetsCapsuleProperties)
        {
            float radius = 20.0f;
            float length = 120.0f;
            float angle = 45.0f;
            Vector2f pos(200.0f, 150.0f);

            SFCapsule capsule(radius, length, angle, pos);

            auto retPos = capsule.GetPosition();

            Assert::AreEqual(pos.x, retPos.x);
            Assert::AreEqual(pos.y, retPos.y);

            auto cen = capsule.GetCenter();

            Assert::AreEqual(retPos.x, cen.x);
            Assert::AreEqual(retPos.y, cen.y);

            auto retRad = capsule.GetRadius();

            Assert::AreEqual(radius, retRad, 0.001f);

            auto retLen = capsule.GetLength();

            Assert::AreEqual(length, retLen, 0.001f);

            auto ori = capsule.GetOrigin();

            Assert::AreEqual(radius, ori.x);
            Assert::AreEqual(length / 2.f, ori.y);

            auto retAng = capsule.GetAngle();

            Assert::AreEqual(angle, retAng, 0.001f);

            auto seg = capsule.GetSegment();

            Vector2f expectedStart(157.574f, 192.426);

            Assert::AreEqual(expectedStart.x, seg.start.x, 0.001f);
            Assert::AreEqual(expectedStart.y, seg.start.y, 0.001f);

            Vector2f expectedEnd(242.426f, 107.574f);

            Assert::AreEqual(expectedEnd.x, seg.end.x, 0.001f);
            Assert::AreEqual(expectedEnd.y, seg.end.y, 0.001f);
        }

        TEST_METHOD(SFCapsule_ParameterizedConstructor_ConfiguresBody)
        {
            float radius = 20.0f;
            float length = 120.0f;
            float angle = 45.0f;
            Vector2f pos(200.0f, 150.0f);

            SFCapsule capsule(radius, length, angle, pos);

            auto body = capsule.GetBody();
            Assert::IsNotNull(body);

            auto retPos = body->getPosition();

            Assert::AreEqual(pos.x, retPos.x);
            Assert::AreEqual(pos.y, retPos.y);

            auto retSize = body->getSize();

            Assert::AreEqual(radius * 2.f, retSize.x);
            Assert::AreEqual(length, retSize.y);

            auto ori = capsule.GetOrigin();

            Assert::AreEqual(radius, ori.x);
            Assert::AreEqual(length / 2.f, ori.y);

            auto retAng = body->getRotation().asDegrees();

            Assert::AreEqual(angle, retAng, 0.001f);
        }

        TEST_METHOD(SFCapsule_ParameterizedConstructor_ConfiguresEndCap1)
        {
            float radius = 20.0f;
            float length = 120.0f;
            float angle = 45.0f;
            Vector2f pos(200.0f, 150.0f);

            SFCapsule capsule(radius, length, angle, pos);

            auto endCap1 = capsule.GetEndCap1();
            Assert::IsNotNull(endCap1);

            Vector2f expectedPos(157.574f, 192.426);

            auto retPos = endCap1->getPosition();

            Assert::AreEqual(expectedPos.x, retPos.x, 0.001f);
            Assert::AreEqual(expectedPos.y, retPos.y, 0.001f);

            auto retRad = endCap1->getRadius();

            Assert::AreEqual(radius, retRad, 0.001f);

            auto ori = endCap1->getOrigin();

            Assert::AreEqual(radius, ori.x);
            Assert::AreEqual(radius, ori.y);
        }

        TEST_METHOD(SFCapsule_ParameterizedConstructor_ConfiguresEndCap2)
        {
            float radius = 20.0f;
            float length = 120.0f;
            float angle = 45.0f;
            Vector2f pos(200.0f, 150.0f);

            SFCapsule capsule(radius, length, angle, pos);

            auto endCap2 = capsule.GetEndCap2();
            Assert::IsNotNull(endCap2);

            Vector2f expectedPos(242.426f, 107.574f);

            auto retPos = endCap2->getPosition();

            Assert::AreEqual(expectedPos.x, retPos.x, 0.001f);
            Assert::AreEqual(expectedPos.y, retPos.y, 0.001f);

            auto retRad = endCap2->getRadius();

            Assert::AreEqual(radius, retRad, 0.001f);

            auto ori = endCap2->getOrigin();

            Assert::AreEqual(radius, ori.x);
            Assert::AreEqual(radius, ori.y);
        }

        // ======================================================
        // Reset
        // ======================================================

        TEST_METHOD(SFCapsule_Reset_SetsCapsuleProperties)
        {
            float radius = 20.0f;
            float length = 120.0f;
            float angle = 45.0f;

            SFCapsule capsule;

            capsule.Reset(radius, length, angle);

            auto retRad = capsule.GetRadius();

            Assert::AreEqual(radius, retRad, 0.001f);

            auto retLen = capsule.GetLength();

            Assert::AreEqual(length, retLen, 0.001f);

            auto ori = capsule.GetOrigin();

            Assert::AreEqual(radius, ori.x);
            Assert::AreEqual(length / 2.f, ori.y);

            auto retAng = capsule.GetAngle();

            Assert::AreEqual(angle, retAng, 0.001f);
        }

        TEST_METHOD(SFCapsule_Reset_ConfiguresBody)
        {
            float radius = 20.0f;
            float length = 120.0f;
            float angle = 45.0f;

            SFCapsule capsule;

            capsule.Reset(radius, length, angle);

            auto body = capsule.GetBody();
            Assert::IsNotNull(body);

            auto retSize = body->getSize();

            Assert::AreEqual(radius * 2.f, retSize.x);
            Assert::AreEqual(length, retSize.y);

            auto ori = capsule.GetOrigin();

            Assert::AreEqual(radius, ori.x);
            Assert::AreEqual(length / 2.f, ori.y);

            auto retAng = body->getRotation().asDegrees();

            Assert::AreEqual(angle, retAng, 0.001f);
        }

        TEST_METHOD(SFCapsule_Reset_ConfiguresEndCaps)
        {
            float radius = 20.0f;
            float length = 120.0f;
            float angle = 45.0f;

            SFCapsule capsule;

            capsule.Reset(radius, length, angle);

            auto endCap1 = capsule.GetEndCap1();
            Assert::IsNotNull(endCap1);

            auto retRad1 = endCap1->getRadius();

            Assert::AreEqual(radius, retRad1, 0.001f);

            auto ori1 = endCap1->getOrigin();

            Assert::AreEqual(radius, ori1.x);
            Assert::AreEqual(radius, ori1.y);

            auto endCap2 = capsule.GetEndCap2();
            Assert::IsNotNull(endCap2);

            auto retRad2 = endCap2->getRadius();

            Assert::AreEqual(retRad1, retRad2, 0.001f);

            auto ori2 = endCap2->getOrigin();

            Assert::AreEqual(ori1.x, ori2.x);
            Assert::AreEqual(ori1.y, ori2.y);
        }

        // ======================================================
        // Update
        // ======================================================

        TEST_METHOD(SFCapsule_Update_SetsPositionAndCenter)
        {
            float radius = 20.0f;
            float length = 120.0f;
            float angle = 45.0f;

            SFCapsule capsule;

            capsule.Reset(radius, length, angle);

            Vector2f pos(200.0f, 150.0f);

            capsule.Update(pos);

            auto retPos = capsule.GetPosition();

            Assert::AreEqual(pos.x, retPos.x);
            Assert::AreEqual(pos.y, retPos.y);

            auto cen = capsule.GetCenter();

            Assert::AreEqual(retPos.x, cen.x);
            Assert::AreEqual(retPos.y, cen.y);
        }

        TEST_METHOD(SFCapsule_Update_PositionsEndCap1)
        {
            float radius = 20.0f;
            float length = 120.0f;
            float angle = 45.0f;

            SFCapsule capsule;

            capsule.Reset(radius, length, angle);

            Vector2f pos(200.0f, 150.0f);

            capsule.Update(pos);

            auto endCap1 = capsule.GetEndCap1();
            Assert::IsNotNull(endCap1);

            Vector2f expectedPos(157.574f, 192.426);

            auto retPos = endCap1->getPosition();

            Assert::AreEqual(expectedPos.x, retPos.x, 0.001f);
            Assert::AreEqual(expectedPos.y, retPos.y, 0.001f);
        }

        TEST_METHOD(SFCapsule_Update_PositionsEndCap2)
        {
            float radius = 20.0f;
            float length = 120.0f;
            float angle = 45.0f;

            SFCapsule capsule;

            capsule.Reset(radius, length, angle);

            Vector2f pos(200.0f, 150.0f);

            capsule.Update(pos);

            auto endCap2 = capsule.GetEndCap2();
            Assert::IsNotNull(endCap2);

            Vector2f expectedPos(242.426f, 107.574f);

            auto retPos = endCap2->getPosition();

            Assert::AreEqual(expectedPos.x, retPos.x, 0.001f);
            Assert::AreEqual(expectedPos.y, retPos.y, 0.001f);
        }

        TEST_METHOD(SFCapsule_Update_UpdatesSegment)
        {
            float radius = 20.0f;
            float length = 120.0f;
            float angle = 45.0f;

            SFCapsule capsule;

            capsule.Reset(radius, length, angle);

            Vector2f pos(200.0f, 150.0f);

            capsule.Update(pos);

            auto seg = capsule.GetSegment();

            Vector2f expectedStart(157.574f, 192.426);

            Assert::AreEqual(expectedStart.x, seg.start.x, 0.001f);
            Assert::AreEqual(expectedStart.y, seg.start.y, 0.001f);

            Vector2f expectedEnd(242.426f, 107.574f);

            Assert::AreEqual(expectedEnd.x, seg.end.x, 0.001f);
            Assert::AreEqual(expectedEnd.y, seg.end.y, 0.001f);
        }

        // ======================================================
        // GetBody
        // ======================================================

        TEST_METHOD(SFCapsule_GetBody_ReturnsRectangleShape)
        {
            SFCapsule capsule;

            auto* expected = capsule.GetPrimaryDrawableAs<sf::RectangleShape>();
            auto* actual = capsule.GetBody();

            Assert::IsNotNull(expected);
            Assert::IsNotNull(actual);

            Assert::IsTrue(expected == actual);
        }

        // ======================================================
        // GetEndCap1
        // ======================================================

        TEST_METHOD(SFCapsule_GetEndCap1_ReturnsCircleShape)
        {
            SFCapsule capsule;

            auto drawables = capsule.GetDrawables();

            Assert::IsTrue(drawables.size() > 1);

            auto* expected = dynamic_cast<sf::CircleShape*>(drawables[1].get());
            auto* actual = capsule.GetEndCap1();

            Assert::IsNotNull(expected);
            Assert::IsNotNull(actual);

            Assert::IsTrue(expected == actual);
        }

        // ======================================================
        // GetEndCap2
        // ======================================================

        TEST_METHOD(SFCapsule_GetEndCap2_ReturnsCircleShape)
        {
            SFCapsule capsule;

            auto drawables = capsule.GetDrawables();

            Assert::IsTrue(drawables.size() > 2);

            auto* expected = dynamic_cast<sf::CircleShape*>(drawables[2].get());
            auto* actual = capsule.GetEndCap2();

            Assert::IsNotNull(expected);
            Assert::IsNotNull(actual);

            Assert::IsTrue(expected == actual);
        }

        // ======================================================
        // GetSize
        // ======================================================

        TEST_METHOD(SFCapsule_GetSize_ReturnsDefaultBodySize)
        {
            SFCapsule capsule;

            auto size = capsule.GetSize();

            Assert::AreEqual(0.0f, size.x);
            Assert::AreEqual(0.0f, size.y);

            auto body = capsule.GetBody();
            Assert::IsNotNull(body);

            auto retSize = body->getSize();

            Assert::AreEqual(size.x, retSize.x);
            Assert::AreEqual(size.y, retSize.y);
        }

        // ======================================================
        // SetSize
        // ======================================================

        TEST_METHOD(SFCapsule_SetSize_SetsBodySize)
        {
            SFCapsule capsule;

            Vector2f size(160.0f, 90.0f);

            capsule.SetSize(size);

            auto body = capsule.GetBody();
            Assert::IsNotNull(body);

            auto retSize = body->getSize();

            Assert::AreEqual(size.x, retSize.x);
            Assert::AreEqual(size.y, retSize.y);
        }

        // ======================================================
        // GetRadius
        // ======================================================

        TEST_METHOD(SFCapsule_GetRadius_ReturnsDefaultRadius)
        {
            SFCapsule capsule;

            auto radius = capsule.GetRadius();

            Assert::AreEqual(0.f, radius);
        }

        // ======================================================
        // SetRadius
        // ======================================================

        TEST_METHOD(SFCapsule_SetRadius_SetsRadius)
        {
            SFCapsule capsule;

            float radius = 20.0f;

            capsule.SetRadius(radius);

            auto retRad = capsule.GetRadius();

            Assert::AreEqual(radius, retRad);
        }

        // ======================================================
        // GetLength
        // ======================================================

        TEST_METHOD(SFCapsule_GetLength_ReturnsDefaultLength)
        {
            SFCapsule capsule;

            auto length = capsule.GetLength();

            Assert::AreEqual(0.f, length);
        }

        // ======================================================
        // SetLength
        // ======================================================

        TEST_METHOD(SFCapsule_SetLength_SetsLength)
        {
            SFCapsule capsule;

            float length = 120.0f;

            capsule.SetLength(length);

            auto retLen = capsule.GetLength();

            Assert::AreEqual(length, retLen);
        }

        // ======================================================
        // GetAngle
        // ======================================================

        TEST_METHOD(SFCapsule_GetAngle_ReturnsDefaultAngle)
        {
            SFCapsule capsule;

            auto angle = capsule.GetAngle();

            Assert::AreEqual(0.f, angle);
        }

        // ======================================================
        // SetAngle
        // ======================================================

        TEST_METHOD(SFCapsule_SetAngle_SetsAngle)
        {
            SFCapsule capsule;

            float angle = 45.f;

            capsule.SetAngle(angle);

            auto retAng = capsule.GetAngle();

            Assert::AreEqual(angle, retAng);
        }

        // ======================================================
        // GetSegment
        // ======================================================

        TEST_METHOD(SFCapsule_GetSegment_ReturnsDefaultSegment)
        {
            SFCapsule capsule;

            auto seg = capsule.GetSegment();

            Assert::AreEqual(0.f, seg.start.x);
            Assert::AreEqual(0.f, seg.start.y);
            Assert::AreEqual(0.f, seg.end.x);
            Assert::AreEqual(0.f, seg.end.y);
        }

        // ======================================================
        // SetSegment
        // ======================================================

        TEST_METHOD(SFCapsule_SetSegment_SetsSegment)
        {
            SFCapsule capsule;

            Line2f segment(
                Vector2f(100.0f, 150.0f),
                Vector2f(300.0f, 150.0f)
            );

            capsule.SetSegment(segment);

            auto retSeg = capsule.GetSegment();

            Assert::AreEqual(segment.start.x, retSeg.start.x);
            Assert::AreEqual(segment.start.y, retSeg.start.y);
            Assert::AreEqual(segment.end.x, retSeg.end.x);
            Assert::AreEqual(segment.end.y, retSeg.end.y);
        }
    };
}