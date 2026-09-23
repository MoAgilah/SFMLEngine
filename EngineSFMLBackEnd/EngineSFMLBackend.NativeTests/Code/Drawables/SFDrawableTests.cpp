#include "CppUnitTest.h"

#include <Fakes/Renderer/FakeRenderer.h>
#include <Fakes/Resources/FakeShader.h>
#include <Testables/Drawables/TestableSFDrawable.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Drawables
{
    TEST_CLASS(SFDrawableTests)
    {
    public:
        // ======================================================
        // Constructors
        // ======================================================

        TEST_METHOD(TestableSFDrawable_DefaultConstructor_CreatesRectangleShape)
        {
            TestableSFDrawable drawable;

            Assert::IsNotNull(drawable.GetPrimaryDrawable());
            Assert::IsNotNull(drawable.GetPrimaryDrawableAs<sf::RectangleShape>());
        }

        TEST_METHOD(TestableSFDrawable_Constructor_CreatesRectangleShapeWithDefaultSize)
        {
            auto size = Vector2f(16.f, 16.f);

            TestableSFDrawable drawable(size);

            Assert::IsNotNull(drawable.GetPrimaryDrawable());

            auto sfRect = drawable.GetPrimaryDrawableAs<sf::RectangleShape>();
            Assert::IsNotNull(sfRect);

            Vector2f retSize = sfRect->getSize();

            Assert::AreEqual(size.x, retSize.x);
            Assert::AreEqual(size.y, retSize.y);
        }

        // ======================================================
        // Render - Safe early return behaviour
        // ======================================================

        TEST_METHOD(SFDrawable_Render_DoesNothingIfRendererIsNull)
        {
            TestableSFDrawable drawable;

            drawable.Render(nullptr);
        }

        TEST_METHOD(SFDrawable_Render_DoesNothingIfPrimaryIsNull)
        {
            TestableSFDrawable drawable;

            FakeRenderer renderer;

            drawable.ForTestingMakeDrawableNull();

            drawable.Render(&renderer);
        }

        TEST_METHOD(SFDrawable_RenderWithShader_DoesNothingIfRendererIsNull)
        {
            TestableSFDrawable drawable;

            drawable.Render(nullptr, nullptr);
        }

        TEST_METHOD(SFDrawable_RenderWithShader_DoesNothingIfShaderIsNull)
        {
            TestableSFDrawable drawable;

            FakeRenderer renderer;

            drawable.ForTestingMakeDrawableNull();

            drawable.Render(&renderer, nullptr);
        }

        TEST_METHOD(SFDrawable_RenderWithShader_DoesNothingIfShaderIsInvalidType)
        {
            TestableSFDrawable drawable;

            FakeRenderer renderer;

            FakeShader shader;

            drawable.Render(&renderer, &shader);
        }

        // ======================================================
        // Position
        // ======================================================

        TEST_METHOD(SFDrawable_GetPosition_ReturnsDefaultVector2fIfPrimaryIsNull)
        {
            TestableSFDrawable drawable;

            drawable.ForTestingMakeDrawableNull();

            Vector2f def;

            auto pos = drawable.GetPosition();

            Assert::AreEqual(def.x, pos.x);
            Assert::AreEqual(def.y, pos.y);
        }

        TEST_METHOD(SFDrawable_SetPosition_DoesNothingIfPrimaryIsNull)
        {
            TestableSFDrawable drawable;

            drawable.ForTestingMakeDrawableNull();

            drawable.SetPosition(Vector2f(16.f, 16.f));

            Vector2f def;

            auto pos = drawable.GetPosition();

            Assert::AreEqual(def.x, pos.x);
            Assert::AreEqual(def.y, pos.y);
        }

        TEST_METHOD(SFDrawable_SetPosition_UpdatesPosition)
        {
            TestableSFDrawable drawable;

            auto newPos = Vector2f(16.f, 16.f);

            drawable.SetPosition(newPos);

            auto pos = drawable.GetPosition();

            Assert::AreEqual(newPos.x, pos.x);
            Assert::AreEqual(newPos.y, pos.y);
        }

        TEST_METHOD(SFDrawable_GetPosition_ReturnsDefaultVector2fIfNotSet)
        {
            TestableSFDrawable drawable;

            Vector2f def;

            auto pos = drawable.GetPosition();

            Assert::AreEqual(def.x, pos.x);
            Assert::AreEqual(def.y, pos.y);
        }

        TEST_METHOD(SFDrawable_OffsetPosition_DoesNothingIfPrimaryIsNull)
        {
            TestableSFDrawable drawable;

            drawable.ForTestingMakeDrawableNull();

            drawable.OffsetPosition(Vector2f(1.f, 2.f));

            Vector2f def;

            auto pos = drawable.GetPosition();

            Assert::AreEqual(def.x, pos.x);
            Assert::AreEqual(def.y, pos.y);
        }

        TEST_METHOD(SFDrawable_OffsetPosition_MovesPosition)
        {
            TestableSFDrawable drawable;

            drawable.OffsetPosition(Vector2f(1.f, 2.f));

            auto pos = drawable.GetPosition();

            Assert::AreEqual(1.f, pos.x);
            Assert::AreEqual(2.f, pos.y);
        }

        // ======================================================
        // Scale
        // ======================================================

        TEST_METHOD(SFDrawable_SetScale_UpdatesScaleOnlyIfPrimaryIsNull)
        {
            TestableSFDrawable drawable;

            drawable.ForTestingMakeDrawableNull();

            drawable.SetScale(GameConstants::Scale);

            auto scl = drawable.GetScale();

            Assert::AreEqual(GameConstants::Scale.x, scl.x);
            Assert::AreEqual(GameConstants::Scale.y, scl.y);

            Assert::IsNull(drawable.GetPrimaryDrawable());
        }

        TEST_METHOD(SFDrawable_SetScale_UpdatesScaleAndPrimaryScale)
        {
            TestableSFDrawable drawable;

            drawable.SetScale(GameConstants::Scale);

            auto scl = drawable.GetScale();

            Assert::AreEqual(GameConstants::Scale.x, scl.x);
            Assert::AreEqual(GameConstants::Scale.y, scl.y);

            Assert::IsNotNull(drawable.GetPrimaryDrawable());

            auto sfRect = drawable.GetPrimaryDrawableAs<sf::RectangleShape>();
            Assert::IsNotNull(sfRect);

            Vector2f priScl = sfRect->getScale();

            Assert::AreEqual(scl.x, priScl.x);
            Assert::AreEqual(scl.y, priScl.y);
        }

        TEST_METHOD(SFDrawable_GetScale_ReturnsDefaultVector2fIfNotSet)
        {
            TestableSFDrawable drawable;

            Vector2f def;

            auto scl = drawable.GetScale();

            Assert::AreEqual(def.x, scl.x);
            Assert::AreEqual(def.y, scl.y);
        }

        // ======================================================
        // Origin
        // ======================================================

        TEST_METHOD(SFDrawable_GetOrigin_ReturnsDefaultVector2fIfPrimaryIsNull)
        {
            TestableSFDrawable drawable;

            drawable.ForTestingMakeDrawableNull();

            Vector2f def;

            auto ori = drawable.GetOrigin();

            Assert::AreEqual(def.x, ori.x);
            Assert::AreEqual(def.y, ori.y);
        }

        TEST_METHOD(SFDrawable_SetOrigin_DoesNothingIfPrimaryIsNull)
        {
            TestableSFDrawable drawable;

            drawable.ForTestingMakeDrawableNull();

            drawable.SetOrigin(Vector2f(8.f, 8.f));

            Vector2f def;

            auto ori = drawable.GetOrigin();

            Assert::AreEqual(def.x, ori.x);
            Assert::AreEqual(def.y, ori.y);
        }

        TEST_METHOD(SFDrawable_SetOrigin_UpdatesOrigin)
        {
            TestableSFDrawable drawable;

            auto newOri = Vector2f(8.f, 8.f);

            drawable.SetOrigin(newOri);

            auto ori = drawable.GetOrigin();

            Assert::AreEqual(newOri.x, ori.x);
            Assert::AreEqual(newOri.y, ori.y);
        }

        TEST_METHOD(SFDrawable_GetOrigin_ReturnsDefaultVector2fIfNotSet)
        {
            TestableSFDrawable drawable;

            Vector2f def;

            auto ori = drawable.GetOrigin();

            Assert::AreEqual(def.x, ori.x);
            Assert::AreEqual(def.y, ori.y);
        }

        // ======================================================
        // Size
        // ======================================================


        TEST_METHOD(SFDrawable_GetLocalSize_ReturnsDefaultVector2fIfPrimaryIsNull)
        {
            TestableSFDrawable drawable;

            drawable.ForTestingMakeDrawableNull();

            Vector2f def;

            auto size = drawable.GetLocalSize();

            Assert::AreEqual(def.x, size.x);
            Assert::AreEqual(def.y, size.y);
        }

        TEST_METHOD(SFDrawable_GetLocalSize_ReturnsDefaultVector2fIfNotSet)
        {
            TestableSFDrawable drawable;

            Vector2f def;

            auto size = drawable.GetLocalSize();

            Assert::AreEqual(def.x, size.x);
            Assert::AreEqual(def.y, size.y);
        }

        TEST_METHOD(SFDrawable_GetLocalSize_ReturnsLocalSize)
        {
            auto size = Vector2f(16.f, 16.f);

            TestableSFDrawable drawable(size);

            auto retSize = drawable.GetLocalSize();

            Assert::AreEqual(size.x, retSize.x);
            Assert::AreEqual(size.y, retSize.y);
        }

        TEST_METHOD(SFDrawable_GetSize_ReturnsDefaultVector2fIfPrimaryIsNull)
        {
            TestableSFDrawable drawable;

            drawable.ForTestingMakeDrawableNull();

            Vector2f def;

            auto size = drawable.GetSize();

            Assert::AreEqual(def.x, size.x);
            Assert::AreEqual(def.y, size.y);
        }

        TEST_METHOD(SFDrawable_GetSize_ReturnsDefaultVector2fIfNotSet)
        {
            TestableSFDrawable drawable;

            Vector2f def;

            auto size = drawable.GetSize();

            Assert::AreEqual(def.x, size.x);
            Assert::AreEqual(def.y, size.y);
        }

        TEST_METHOD(SFDrawable_GetSize_ReturnsLocalSize)
        {
            auto size = Vector2f(16.f, 16.f);

            TestableSFDrawable drawable(size);

            auto locSize = drawable.GetLocalSize();

            Assert::AreEqual(size.x, locSize.x);
            Assert::AreEqual(size.y, locSize.y);

            auto retSize = drawable.GetSize();

            Assert::AreEqual(locSize.x, retSize.x);
            Assert::AreEqual(locSize.y, retSize.y);
        }

        TEST_METHOD(SFDrawable_SetSize_DoesNothing)
        {
            auto size = Vector2f(16.f, 16.f);

            TestableSFDrawable drawable(size);

            drawable.SetSize(Vector2f(32.f, 32.f));

            auto retSize = drawable.GetSize();

            Assert::AreEqual(size.x, retSize.x);
            Assert::AreEqual(size.y, retSize.y);
        }

        TEST_METHOD(SFDrawable_GetGlobalSize_ReturnsDefaultVector2fIfPrimaryIsNull)
        {
            TestableSFDrawable drawable;

            drawable.ForTestingMakeDrawableNull();

            Vector2f def;

            auto size = drawable.GetGlobalSize();

            Assert::AreEqual(def.x, size.x);
            Assert::AreEqual(def.y, size.y);
        }

        TEST_METHOD(SFDrawable_GetGlobalSize_ReturnsDefaultVector2fIfNotSet)
        {
            TestableSFDrawable drawable;

            Vector2f def;

            auto size = drawable.GetGlobalSize();

            Assert::AreEqual(def.x, size.x);
            Assert::AreEqual(def.y, size.y);
        }

        TEST_METHOD(SFDrawable_GetGlobalSize_ReturnsGlobalSize)
        {
            TestableSFDrawable drawable(Vector2f(16.f, 16.f));

            drawable.SetScale(Vector2f(2.f, 2.f));

            auto size = drawable.GetGlobalSize();

            Assert::AreEqual(32.f, size.x);
            Assert::AreEqual(32.f, size.y);
        }
    };
}