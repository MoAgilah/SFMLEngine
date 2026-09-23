#include "CppUnitTest.h"

#include <Testables/Drawables/TestableSFShape.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Drawables
{
    TEST_CLASS(SFShapeTests)
    {
    public:
        // ======================================================
        // Constructors
        // ======================================================
        TEST_METHOD(TestableSFShape_DefaultConstructor_CreatesRectangleShape)
        {
            TestableSFShape shape;

            Assert::IsNotNull(shape.GetPrimaryDrawable());
            Assert::IsNotNull(shape.GetPrimaryDrawableAs<sf::RectangleShape>());
        }

        // ======================================================
        // Fill Colour
        // ======================================================

        TEST_METHOD(SFShape_GetFillColour_ReturnsDefaultColourIfPrimaryIsNull)
        {
            TestableSFShape shape;

            shape.ForTestingMakeShapeNull();

            Colour def = sf::Color::Black;

            auto col = shape.GetFillColour();

            Assert::AreEqual(def.r, col.r);
            Assert::AreEqual(def.g, col.g);
            Assert::AreEqual(def.b, col.b);
            Assert::AreEqual(def.a, col.a);
        }

        TEST_METHOD(SFShape_SetFillColour_DoesNothingIfPrimaryIsNull)
        {
            TestableSFShape shape;

            shape.ForTestingMakeShapeNull();

            Colour newCol = sf::Color::White;

            shape.SetFillColour(newCol);

            Colour def = sf::Color::Black;

            auto col = shape.GetFillColour();

            Assert::AreEqual(def.r, col.r);
            Assert::AreEqual(def.g, col.g);
            Assert::AreEqual(def.b, col.b);
            Assert::AreEqual(def.a, col.a);
        }

        TEST_METHOD(SFShape_SetFillColour_UpdatesFillColour)
        {
            TestableSFShape shape;

            Colour newCol = sf::Color::White;

            shape.SetFillColour(newCol);

            auto col = shape.GetFillColour();

            Assert::AreEqual(newCol.r, col.r);
            Assert::AreEqual(newCol.g, col.g);
            Assert::AreEqual(newCol.b, col.b);
            Assert::AreEqual(newCol.a, col.a);
        }

        TEST_METHOD(SFShape_GetFillColour_ReturnsDefaultColourIfNotSet)
        {
            TestableSFShape shape;

            Colour def = sf::Color::White;

            auto col = shape.GetFillColour();

            Assert::AreEqual(def.r, col.r);
            Assert::AreEqual(def.g, col.g);
            Assert::AreEqual(def.b, col.b);
            Assert::AreEqual(def.a, col.a);
        }

        // ======================================================
        // Outline Colour
        // ======================================================

        TEST_METHOD(SFShape_GetOutlineColour_ReturnsDefaultColourIfPrimaryIsNull)
        {
            TestableSFShape shape;

            shape.ForTestingMakeShapeNull();

            Colour def = sf::Color::Black;

            auto col = shape.GetOutlineColour();

            Assert::AreEqual(def.r, col.r);
            Assert::AreEqual(def.g, col.g);
            Assert::AreEqual(def.b, col.b);
            Assert::AreEqual(def.a, col.a);
        }

        TEST_METHOD(SFShape_SetOutlineColour_DoesNothingIfPrimaryIsNull)
        {
            TestableSFShape shape;

            shape.ForTestingMakeShapeNull();

            Colour newCol = sf::Color::White;

            shape.SetOutlineColour(newCol);

            Colour def = sf::Color::Black;

            auto col = shape.GetOutlineColour();

            Assert::AreEqual(def.r, col.r);
            Assert::AreEqual(def.g, col.g);
            Assert::AreEqual(def.b, col.b);
            Assert::AreEqual(def.a, col.a);
        }

        TEST_METHOD(SFShape_SetOutlineColour_UpdatesOutlineColour)
        {
            TestableSFShape shape;

            Colour newCol = sf::Color::Black;

            shape.SetOutlineColour(newCol);

            auto col = shape.GetOutlineColour();

            Assert::AreEqual(newCol.r, col.r);
            Assert::AreEqual(newCol.g, col.g);
            Assert::AreEqual(newCol.b, col.b);
            Assert::AreEqual(newCol.a, col.a);
        }

        TEST_METHOD(SFShape_GetOutlineColour_ReturnsDefaultColourIfNotSet)
        {
            TestableSFShape shape;

            Colour def = sf::Color::White;

            auto col = shape.GetOutlineColour();

            Assert::AreEqual(def.r, col.r);
            Assert::AreEqual(def.g, col.g);
            Assert::AreEqual(def.b, col.b);
            Assert::AreEqual(def.a, col.a);
        }

        // ======================================================
        // Outline Colour
        // ======================================================

        TEST_METHOD(SFShape_GetOutlineThickness_ReturnsDefaultThicknessIfPrimaryIsNull)
        {
            TestableSFShape shape;

            shape.ForTestingMakeShapeNull();

            float def = 0.f;

            auto thk = shape.GetOutlineThickness();

            Assert::AreEqual(def, thk);
        }

        TEST_METHOD(SFShape_SetOutlineThickness_DoesNothingIfPrimaryIsNull)
        {
            TestableSFShape shape;

            shape.ForTestingMakeShapeNull();

            float newThk = 1.f;

            shape.SetOutlineThickness(newThk);

            float def = 0.f;

            auto thk = shape.GetOutlineThickness();

            Assert::AreEqual(def, thk);
        }

        TEST_METHOD(SFShape_SetOutlineThickness_UpdatesOutlineThickness)
        {
            TestableSFShape shape;

            float newThk = 1.f;

            shape.SetOutlineThickness(newThk);

            auto thk = shape.GetOutlineThickness();

            Assert::AreEqual(newThk, thk);
        }

        TEST_METHOD(SFShape_GetOutlineThickness_ReturnsDefaultThicknessIfNotSet)
        {
            TestableSFShape shape;

            float def = 0.f;

            auto thk = shape.GetOutlineThickness();

            Assert::AreEqual(def, thk);
        }

        // ======================================================
        // Rotation
        // ======================================================

        TEST_METHOD(SFShape_SetRotation_DoesNothingIfPrimaryIsNull)
        {
            TestableSFShape shape;

            shape.ForTestingMakeShapeNull();

            float newRot = 1.f;

            shape.SetRotation(newRot);

            Assert::IsNull(shape.GetPrimaryDrawable());
        }

        TEST_METHOD(SFShape_SetRotation_UpdatesRotation)
        {
            TestableSFShape shape;

            float newRot = 1.f;

            shape.SetRotation(newRot);

            Assert::IsNotNull(shape.GetPrimaryDrawable());

            auto sfRect = shape.GetPrimaryDrawableAs<sf::RectangleShape>();
            Assert::IsNotNull(sfRect);

            float rot = sfRect->getRotation().asDegrees();

            Assert::AreEqual(newRot, rot, 0.001f);
        }
    };
}