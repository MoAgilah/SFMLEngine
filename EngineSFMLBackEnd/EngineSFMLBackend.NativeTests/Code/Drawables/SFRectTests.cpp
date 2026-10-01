#include "CppUnitTest.h"

#include <Engine/Core/Constants.h>
#include <Drawables/SFShape.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Drawables
{
    TEST_CLASS(SFRectTests)
    {
    public:
        // ======================================================
        // Constructors
        // ======================================================

        TEST_METHOD(SFRect_DefaultConstructor_SetsDefaults)
        {
            SFRect rect;

            auto scl = rect.GetScale();

            Assert::AreEqual(GameConstants::Scale.x, scl.x);
            Assert::AreEqual(GameConstants::Scale.y, scl.y);

            auto defFillCol = Colour::Transparent;

            auto fillCol = rect.GetFillColour();

            Assert::AreEqual(defFillCol.r, fillCol.r);
            Assert::AreEqual(defFillCol.g, fillCol.g);
            Assert::AreEqual(defFillCol.b, fillCol.b);
            Assert::AreEqual(defFillCol.a, fillCol.a);

            auto defOutCol = Colour::Red;

            auto outCol = rect.GetOutlineColour();

            Assert::AreEqual(defOutCol.r, outCol.r);
            Assert::AreEqual(defOutCol.g, outCol.g);
            Assert::AreEqual(defOutCol.b, outCol.b);
            Assert::AreEqual(defOutCol.a, outCol.a);

            float defThk = 1.0f;

            auto outThk = rect.GetOutlineThickness();

            Assert::AreEqual(defThk, outThk);
        }

        TEST_METHOD(SFRect_ConstructorWithSizeAndPos_SetsSizeOriginAndPosition)
        {
            Vector2f size(160.0f, 90.0f);
            Vector2f pos(240.0f, 135.0f);

            SFRect rect(size, pos);

            auto retPos = rect.GetPosition();

            Assert::AreEqual(pos.x, retPos.x);
            Assert::AreEqual(pos.y, retPos.y);

            auto cen = rect.GetCenter();

            Assert::AreEqual(retPos.x, cen.x);
            Assert::AreEqual(retPos.y, cen.y);

            auto retSize = rect.GetSize();

            Assert::AreEqual(size.x, retSize.x, 0.001f);
            Assert::AreEqual(size.y, retSize.y, 0.001f);

            auto ori = rect.GetOrigin();

            Assert::AreEqual(size.x * 0.5f, ori.x);
            Assert::AreEqual(size.y * 0.5f, ori.y);
        }

        // ======================================================
        // Update
        // ======================================================

        TEST_METHOD(SFRect_Update_SetsPositionAndCenter)
        {
            SFRect rect;

            Vector2f pos(240.0f, 135.0f);

            rect.Update(pos);

            auto retPos = rect.GetPosition();

            Assert::AreEqual(pos.x, retPos.x);
            Assert::AreEqual(pos.y, retPos.y);

            auto cen = rect.GetCenter();

            Assert::AreEqual(retPos.x, cen.x);
            Assert::AreEqual(retPos.y, cen.y);
        }

        // ======================================================
        // Reset
        // ======================================================

        TEST_METHOD(SFRect_Reset_SetsSizeAndOrigin)
        {
            SFRect rect;

            Vector2f size(160.0f, 90.0f);

            rect.Reset(size);

            auto retSize = rect.GetSize();

            Assert::AreEqual(size.x, retSize.x);
            Assert::AreEqual(size.y, retSize.y);

            auto ori = rect.GetOrigin();

            Assert::AreEqual(size.x * 0.5f, ori.x);
            Assert::AreEqual(size.y * 0.5f, ori.y);
        }

        // ======================================================
        // GetRect
        // ======================================================

        TEST_METHOD(SFRect_GetRect_ReturnsRectangleShape)
        {
            SFRect rect;

            auto* expected = rect.GetPrimaryDrawableAs<sf::RectangleShape>();
            auto* actual = rect.GetRect();

            Assert::IsNotNull(expected);
            Assert::IsNotNull(actual);

            Assert::IsTrue(expected == actual);
        }

        // ======================================================
        // GetSize
        // ======================================================

        TEST_METHOD(SFRect_GetSize_ReturnsDefaultSize)
        {
            SFRect rect;

            auto size = rect.GetSize();

            Assert::AreEqual(0.0f, size.x);
            Assert::AreEqual(0.0f, size.y);
        }

        // ======================================================
        // SetSize
        // ======================================================

        TEST_METHOD(SFRect_SetSize_SetsSize)
        {
            SFRect rect;

            Vector2f size(160.0f, 90.0f);

            rect.SetSize(size);

            auto retSize = rect.GetSize();

            Assert::AreEqual(size.x, retSize.x);
            Assert::AreEqual(size.y, retSize.y);
        }

        TEST_METHOD(SFRect_SizeMethods_ReturnLogicalLocalAndGlobalSizes)
        {
            SFRect rect;

            Vector2f size(160.0f, 90.0f);

            rect.SetSize(size);

            Vector2f scale(2.f, 2.f);

            rect.SetScale(scale);

            auto outlineContribution = rect.GetOutlineThickness() * 2;

            Vector2f expLocSize = size + Vector2f(outlineContribution, outlineContribution);

            auto locSize = rect.GetLocalSize();

            Assert::AreEqual(expLocSize.x, locSize.x);
            Assert::AreEqual(expLocSize.y, locSize.y);

            Vector2f expGloSize = expLocSize * scale;

            auto gloSize = rect.GetGlobalSize();

            Assert::AreEqual(expGloSize.x, gloSize.x);
            Assert::AreEqual(expGloSize.y, gloSize.y);
        }
    };
}