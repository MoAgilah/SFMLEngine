#include "CppUnitTest.h"

#include <Engine/Core/Constants.h>
#include <Drawables/SFShape.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Drawables
{
    TEST_CLASS(SFCircleTests)
    {
    public:
        // ======================================================
        // Constructors
        // ======================================================

        TEST_METHOD(SFCircle_DefaultConstructor_SetsDefaults)
        {
            SFCircle circle;

            auto scl = circle.GetScale();

            Assert::AreEqual(GameConstants::Scale.x, scl.x);
            Assert::AreEqual(GameConstants::Scale.y, scl.y);

            auto defFillCol = Colour::Transparent;

            auto fillCol = circle.GetFillColour();

            Assert::AreEqual(defFillCol.r, fillCol.r);
            Assert::AreEqual(defFillCol.g, fillCol.g);
            Assert::AreEqual(defFillCol.b, fillCol.b);
            Assert::AreEqual(defFillCol.a, fillCol.a);

            auto defOutCol = Colour::Red;

            auto outCol = circle.GetOutlineColour();

            Assert::AreEqual(defOutCol.r, outCol.r);
            Assert::AreEqual(defOutCol.g, outCol.g);
            Assert::AreEqual(defOutCol.b, outCol.b);
            Assert::AreEqual(defOutCol.a, outCol.a);

            float defThk = 1.0f;

            auto outThk = circle.GetOutlineThickness();

            Assert::AreEqual(defThk, outThk);
        }

        TEST_METHOD(SFCircle_ConstructorWithRadiusAndPos_SetsRadiusOriginAndPosition)
        {
            float radius = 45.f;
            Vector2f pos(175.0f, 225.0f);

            SFCircle circle(radius, pos);

            auto retPos = circle.GetPosition();

            Assert::AreEqual(pos.x, retPos.x);
            Assert::AreEqual(pos.y, retPos.y);

            auto cen = circle.GetCenter();

            Assert::AreEqual(retPos.x, cen.x);
            Assert::AreEqual(retPos.y, cen.y);

            auto retRad = circle.GetRadius();

            Assert::AreEqual(radius, retRad, 0.001f);

            auto ori = circle.GetOrigin();

            Assert::AreEqual(radius, ori.x);
            Assert::AreEqual(radius, ori.y);
        }

        // ======================================================
        // Update
        // ======================================================

        TEST_METHOD(SFCircle_Update_SetsPositionAndCenter)
        {
            SFCircle circle;

            Vector2f pos(175.0f, 225.0f);

            circle.Update(pos);

            auto retPos = circle.GetPosition();

            Assert::AreEqual(pos.x, retPos.x);
            Assert::AreEqual(pos.y, retPos.y);

            auto cen = circle.GetCenter();

            Assert::AreEqual(retPos.x, cen.x);
            Assert::AreEqual(retPos.y, cen.y);
        }

        // ======================================================
        // Reset
        // ======================================================

        TEST_METHOD(SFCircle_Reset_SetsRadiusAndOrigin)
        {
            SFCircle circle;

            float radius = 45.f;

            circle.Reset(radius);

            auto retRad = circle.GetRadius();

            Assert::AreEqual(radius, retRad);

            auto ori = circle.GetOrigin();

            Assert::AreEqual(radius, ori.x);
            Assert::AreEqual(radius, ori.y);
        }

        // ======================================================
        // GetCircle
        // ======================================================

        TEST_METHOD(SFCircle_GetCircle_ReturnsCircleShape)
        {
            SFCircle circle;

            auto* expected = circle.GetPrimaryDrawableAs<sf::CircleShape>();
            auto* actual = circle.GetCircle();

            Assert::IsNotNull(expected);
            Assert::IsNotNull(actual);

            Assert::IsTrue(expected == actual);
        }

        // ======================================================
        // Radius
        // ======================================================

        TEST_METHOD(SFCircle_GetRadius_ReturnsDefaultIfUnset)
        {
            SFCircle circle;

            auto radius = circle.GetRadius();

            Assert::AreEqual(0.f, radius);
        }

        TEST_METHOD(SFCircle_SetRadius_SetsRadius)
        {
            SFCircle circle;

            float radius = 45.f;

            circle.SetRadius(radius);

            auto retRad = circle.GetRadius();

            Assert::AreEqual(radius, retRad);
        }
    };
}