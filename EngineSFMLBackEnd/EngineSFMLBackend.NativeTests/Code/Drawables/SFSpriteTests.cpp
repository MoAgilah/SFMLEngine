#include "CppUnitTest.h"

#include <Engine/Core/Constants.h>
#include <Engine/Core/GameManager.h>
#include <Drawables/SFSprite.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <string_view>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Drawables
{
    TEST_CLASS(SFSpriteTests)
    {
    public:
        // ======================================================
        // Constructors
        // ======================================================

        TEST_METHOD(SFSprite_Constructor_ThrowsIfGameManagerIsNull)
        {
            Assert::ExpectException<std::runtime_error>([&]
                {
                    SFSprite sprite("DefaultTexture");
                });
        }

        TEST_METHOD(SFSprite_Constructor_ThrowsIfTextureDoesNotExist)
        {
            GameManager gm;

            Assert::ExpectException<std::runtime_error>([&]
                {
                    SFSprite sprite("Texture");
                });
        }

        TEST_METHOD(SFSprite_ConstructorWithValidTexture_CreatesSprite)
        {
            GameManager gm;

            SFSprite sprite("DefaultTexture");

            auto* expected = sprite.GetPrimaryDrawableAs<sf::Sprite>();
            auto* actual = sprite.GetSprite();

            Assert::IsNotNull(expected);
            Assert::IsNotNull(actual);

            Assert::IsTrue(expected == actual);
        }

        TEST_METHOD(SFSprite_ConstructorWithValidTexture_SetsDefaults)
        {
            GameManager gm;

            std::string texId = "DefaultTexture";

            SFSprite sprite(texId);

            Assert::AreEqual(std::string_view(texId), sprite.GetTexID());

            auto scl = sprite.GetScale();

            Assert::AreEqual(GameConstants::Scale.x, scl.x);
            Assert::AreEqual(GameConstants::Scale.y, scl.y);

            auto texSize = sprite.GetTextureSize();

            auto origin = sprite.GetOrigin();

            Assert::AreEqual(static_cast<float>(texSize.x) * 0.5f, origin.x);
            Assert::AreEqual(static_cast<float>(texSize.y) * 0.5f, origin.y);
        }

        // ======================================================
        // SetTexture
        // ======================================================

        TEST_METHOD(SFSprite_SetTexture_ReturnsFalseIfGameManagerIsNull)
        {
            SFSprite sprite;

            Assert::IsFalse(sprite.SetTexture("DefaultTexture"));
        }

        TEST_METHOD(SFSprite_SetTexture_ReturnsFalseTextureDoesNotExist)
        {
            GameManager gm;

            SFSprite sprite;

            Assert::IsFalse(sprite.SetTexture("Texture"));
        }

        TEST_METHOD(SFSprite_SetTextureWithValidTexture_CreatesSprite)
        {
            GameManager gm;

            SFSprite sprite;

            sprite.SetTexture("DefaultTexture");

            auto* expected = sprite.GetPrimaryDrawableAs<sf::Sprite>();
            auto* actual = sprite.GetSprite();

            Assert::IsNotNull(expected);
            Assert::IsNotNull(actual);

            Assert::IsTrue(expected == actual);
        }

        TEST_METHOD(SFSprite_SetTextureWithValidTexture_SetsDefaults)
        {
            GameManager gm;

            SFSprite sprite;

            std::string texId = "DefaultTexture";

            sprite.SetTexture(texId);

            Assert::AreEqual(std::string_view(texId), sprite.GetTexID());

            auto scl = sprite.GetScale();

            Assert::AreEqual(GameConstants::Scale.x, scl.x);
            Assert::AreEqual(GameConstants::Scale.y, scl.y);

            auto texSize = sprite.GetTextureSize();

            auto origin = sprite.GetOrigin();

            Assert::AreEqual(static_cast<float>(texSize.x) * 0.5f, origin.x);
            Assert::AreEqual(static_cast<float>(texSize.y) * 0.5f, origin.y);
        }

        // ======================================================
        // SetDirection
        // ======================================================

        TEST_METHOD(SFSprite_SetDirection_DoesNothingIfSFSpriteIsNull)
        {
            SFSprite sprite;

            sprite.SetDirection(false);
        }

        TEST_METHOD(SFSprite_SetDirection_SetsXScale)
        {
            GameManager gm;

            SFSprite sprite("DefaultTexture");

            sprite.SetDirection(false);

            auto sfSprite = sprite.GetSprite();
            Assert::IsNotNull(sfSprite);

            auto scl = sfSprite->getScale();

            Assert::AreEqual(-GameConstants::Scale.x, scl.x);
            Assert::AreEqual(GameConstants::Scale.y, scl.y);

            sprite.SetDirection(true);

            scl = sfSprite->getScale();

            Assert::AreEqual(GameConstants::Scale.x, scl.x);
            Assert::AreEqual(GameConstants::Scale.y, scl.y);
        }

        // ======================================================
        // Update
        // ======================================================

        TEST_METHOD(SFSprite_Update_DoesNothing)
        {
            GameManager gm;

            SFSprite sprite("DefaultTexture");

            sprite.Update(0.16f);
        }

        // ======================================================
        // GetSprite
        // ======================================================

        TEST_METHOD(SFSprite_GetSprite_ReturnsNullIfNotSFSprite)
        {
            SFSprite sprite;

            Assert::IsNull(sprite.GetSprite());
        }

        TEST_METHOD(SFSprite_GetSprite_GetsSFSprite)
        {
            GameManager gm;

            SFSprite sprite("DefaultTexture");

            auto* expected = sprite.GetPrimaryDrawableAs<sf::Sprite>();
            auto* actual = sprite.GetSprite();

            Assert::IsNotNull(expected);
            Assert::IsNotNull(actual);

            Assert::IsTrue(expected == actual);
        }

        // ======================================================
        // GetTextureSize
        // ======================================================

        TEST_METHOD(SFSprite_GetTextureSize_ReturnsDefaultVector2fIfNotSFSprite)
        {
            SFSprite sprite;

            auto texSize = sprite.GetTextureSize();

            Assert::AreEqual(0u, texSize.x);
            Assert::AreEqual(0u, texSize.y);
        }

        TEST_METHOD(SFSprite_GetTextureSize_GetsTextureSize)
        {
            GameManager gm;

            SFSprite sprite("DefaultTexture");

            auto texSize = sprite.GetTextureSize();

            Assert::AreEqual(500u, texSize.x);
            Assert::AreEqual(400u, texSize.y);
        }

        // ======================================================
        // SetTextureRect
        // ======================================================

        TEST_METHOD(SFSprite_SetTextureRect_DoesNothingIfNotSFSprite)
        {
            SFSprite sprite;

            IntRect rect(250, 0, 125, 100);

            sprite.SetTextureRect(rect);
        }

        TEST_METHOD(SFSprite_SetTextureRect_SetsTextureRect)
        {
            GameManager gm;

            SFSprite sprite("DefaultTexture");

            IntRect rect(250, 0, 125, 100);

            sprite.SetTextureRect(rect);

            auto sfSprite = sprite.GetSprite();
            Assert::IsNotNull(sfSprite);

            auto retRect = sfSprite->getTextureRect();

            Assert::AreEqual(rect.m_left, retRect.position.x);
            Assert::AreEqual(rect.m_top, retRect.position.y);
            Assert::AreEqual(rect.m_width, retRect.size.x);
            Assert::AreEqual(rect.m_height, retRect.size.y);
        }
    };
}