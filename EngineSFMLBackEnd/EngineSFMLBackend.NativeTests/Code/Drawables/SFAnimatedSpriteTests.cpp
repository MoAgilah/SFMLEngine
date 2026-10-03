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
    TEST_CLASS(SFAnimatedSpriteTests)
    {
    public:
        // ======================================================
        // Constructors
        // ======================================================

        TEST_METHOD(SFAnimatedSprite_Constructor_ThrowsIfRowsAreNegative)
        {
            GameManager gm;

            Assert::ExpectException<std::runtime_error>([&]
                {
                    SFAnimatedSprite sprite(
                        "DefaultTexture",
                        -1,
                        4,
                        GameConstants::AnimationFrameDurationMS,
                        1.0f
                    );
                });
        }

        TEST_METHOD(SFAnimatedSprite_Constructor_ThrowsIfRowsAreZero)
        {
            GameManager gm;

            Assert::ExpectException<std::runtime_error>([&]
                {
                    SFAnimatedSprite sprite(
                        "DefaultTexture",
                        0,
                        4,
                        GameConstants::AnimationFrameDurationMS,
                        1.0f
                    );
                });
        }

        TEST_METHOD(SFAnimatedSprite_Constructor_ThrowsIfColumnsAreNegative)
        {
            GameManager gm;

            Assert::ExpectException<std::runtime_error>([&]
                {
                    SFAnimatedSprite sprite(
                        "DefaultTexture",
                        4,
                        -1,
                        GameConstants::AnimationFrameDurationMS,
                        1.0f
                    );
                });
        }

        TEST_METHOD(SFAnimatedSprite_Constructor_ThrowsIfColumnsAreZero)
        {
            GameManager gm;

            Assert::ExpectException<std::runtime_error>([&]
                {
                    SFAnimatedSprite sprite(
                        "DefaultTexture",
                        4,
                        0,
                        GameConstants::AnimationFrameDurationMS,
                        1.0f
                    );
                });
        }

        TEST_METHOD(SFAnimatedSprite_ConstructorWithValidParameters_SetsFrameSizeAndOrigin)
        {
            GameManager gm;

            SFAnimatedSprite sprite(
                "DefaultTexture",
                4,
                4,
                GameConstants::AnimationFrameDurationMS,
                1.0f
            );

            auto frameSize = sprite.GetFrameSize();

            Assert::AreEqual(125u, frameSize.x);
            Assert::AreEqual(100u, frameSize.y);

            auto origin = sprite.GetOrigin();

            Assert::AreEqual(static_cast<float>(frameSize.x) * 0.5f, origin.x);
            Assert::AreEqual(static_cast<float>(frameSize.y) * 0.5f, origin.y);
        }

        // ======================================================
        // GetSize
        // ======================================================

        TEST_METHOD(SFAnimatedSprite_GetSize_ReturnsLogicalDrawableSize)
        {
            GameManager gm;

            SFAnimatedSprite sprite(
                "DefaultTexture",
                4,
                4,
                GameConstants::AnimationFrameDurationMS,
                1.0f
            );

            auto frameSize = sprite.GetFrameSize();

            Assert::AreEqual(125u, frameSize.x);
            Assert::AreEqual(100u, frameSize.y);

            auto size = sprite.GetSize();

            Assert::AreEqual(static_cast<float>(frameSize.x), size.x);
            Assert::AreEqual(static_cast<float>(frameSize.y), size.y);
        }

        // ======================================================
        // GetTextureSize
        // ======================================================

        TEST_METHOD(SFAnimatedSprite_GetTextureSize_ReturnsFullTextureSize)
        {
            GameManager gm;

            SFAnimatedSprite sprite(
                "DefaultTexture",
                4,
                4,
                GameConstants::AnimationFrameDurationMS,
                1.0f
            );

            auto texSize = sprite.GetTextureSize();

            Assert::AreEqual(500u, texSize.x);
            Assert::AreEqual(400u, texSize.y);
        }

        // ======================================================
        // SetFrameSize
        // ======================================================

        TEST_METHOD(SFAnimatedSprite_SetFrameSize_ThrowsIfWidthIsZero)
        {
            GameManager gm;

            SFAnimatedSprite sprite(
                "DefaultTexture",
                4,
                4,
                GameConstants::AnimationFrameDurationMS,
                1.0f
            );

            Assert::ExpectException<std::runtime_error>([&]
                {
                    sprite.SetFrameSize(Vector2u(0, 5));
                });
        }

        TEST_METHOD(SFAnimatedSprite_SetFrameSize_ThrowsIfHeightIsZero)
        {
            GameManager gm;

            SFAnimatedSprite sprite(
                "DefaultTexture",
                4,
                4,
                GameConstants::AnimationFrameDurationMS,
                1.0f
            );

            Assert::ExpectException<std::runtime_error>([&]
                {
                    sprite.SetFrameSize(Vector2u(2, 0));
                });
        }

        TEST_METHOD(SFAnimatedSprite_SetFrameSize_SetsFrameSizeAndOrigin)
        {
            GameManager gm;

            SFAnimatedSprite sprite(
                "DefaultTexture",
                4,
                4,
                GameConstants::AnimationFrameDurationMS,
                1.0f
            );

            auto texSize = sprite.GetTextureSize();
            sprite.SetFrameSize({ texSize.x / static_cast<unsigned>(5), texSize.y / static_cast<unsigned>(2) });

            auto frameSize = sprite.GetFrameSize();

            Assert::AreEqual(100u, frameSize.x);
            Assert::AreEqual(200u, frameSize.y);

            auto origin = sprite.GetOrigin();

            Assert::AreEqual(static_cast<float>(frameSize.x) * 0.5f, origin.x);
            Assert::AreEqual(static_cast<float>(frameSize.y) * 0.5f, origin.y);
        }

        // ======================================================
        // Set Frame Data
        // ======================================================

        TEST_METHOD(SFAnimatedSprite_SetFrameData_ThrowsIfRowsAreZero)
        {
            GameManager gm;

            SFAnimatedSprite sprite(
                "DefaultTexture",
                4,
                4,
                GameConstants::AnimationFrameDurationMS,
                1.0f
            );

            std::vector<int> numFrames = { 5, 5 };

            Assert::ExpectException<std::runtime_error>([&]
                {
                    sprite.SetFrameData(0, 5, numFrames);
                });
        }

        TEST_METHOD(SFAnimatedSprite_SetFrameData_ThrowsIfRowsAreNegative)
        {
            GameManager gm;

            SFAnimatedSprite sprite(
                "DefaultTexture",
                4,
                4,
                GameConstants::AnimationFrameDurationMS,
                1.0f
            );

            std::vector<int> numFrames = { 5, 5 };

            Assert::ExpectException<std::runtime_error>([&]
                {
                    sprite.SetFrameData(-2, 5, numFrames);
                });
        }

        TEST_METHOD(SFAnimatedSprite_SetFrameData_ThrowsIfColumnsAreZero)
        {
            GameManager gm;

            SFAnimatedSprite sprite(
                "DefaultTexture",
                4,
                4,
                GameConstants::AnimationFrameDurationMS,
                1.0f
            );

            std::vector<int> numFrames = { 5, 5 };

            Assert::ExpectException<std::runtime_error>([&]
                {
                    sprite.SetFrameData(2, 0, numFrames);
                });
        }

        TEST_METHOD(SFAnimatedSprite_SetFrameData_ThrowsIfColumnsAreNegative)
        {
            GameManager gm;

            SFAnimatedSprite sprite(
                "DefaultTexture",
                4,
                4,
                GameConstants::AnimationFrameDurationMS,
                1.0f
            );

            std::vector<int> numFrames = { 5, 5 };

            Assert::ExpectException<std::runtime_error>([&]
                {
                    sprite.SetFrameData(2, -5, numFrames);
                });
        }

        TEST_METHOD(SFAnimatedSprite_SetFrameData_SetsFrameSizeFromTextureDimensions)
        {
            GameManager gm;

            SFAnimatedSprite sprite(
                "DefaultTexture",
                4,
                4,
                GameConstants::AnimationFrameDurationMS,
                1.0f
            );

            std::vector<int> numFrames = { 5, 5 };

            sprite.SetFrameData(2, 5, numFrames);

            auto frameSize = sprite.GetFrameSize();

            Assert::AreEqual(100u, frameSize.x);
            Assert::AreEqual(200u, frameSize.y);
        }

        // ======================================================
        // Update
        // ======================================================

        TEST_METHOD(SFAnimatedSprite_Update_SetsTextureRectFromCurrentFrame)
        {
            GameManager gm;

            SFAnimatedSprite sprite(
                "DefaultTexture",
                4,
                4,
                GameConstants::AnimationFrameDurationMS,
                1.0f
            );

            std::vector<int> numFrames = { 4, 2, 3, 1 };

            sprite.SetFrames(numFrames);

            auto spr = sprite.GetSprite();
            Assert::IsNotNull(spr);

            auto before = spr->getTextureRect();

            sprite.Update(0.06f);

            auto after = spr->getTextureRect();

            Assert::AreEqual(0, before.position.x);
            Assert::AreEqual(125, after.position.x);

            Assert::AreEqual(before.position.y, after.position.y);
            Assert::AreEqual(before.size.x, after.size.x);
            Assert::AreEqual(before.size.y, after.size.y);
        }

        TEST_METHOD(SFAnimatedSprite_UpdateAfterChangeAnim_SetsTextureRectFromCurrentAnimation)
        {
            GameManager gm;

            SFAnimatedSprite sprite(
                "DefaultTexture",
                4,
                4,
                GameConstants::AnimationFrameDurationMS,
                1.0f
            );

            std::vector<int> numFrames = { 4, 2, 3, 1 };

            sprite.SetFrames(numFrames);

            sprite.ChangeAnim(1);

            auto spr = sprite.GetSprite();
            Assert::IsNotNull(spr);

            auto before = spr->getTextureRect();

            sprite.Update(0.03f);

            auto after = spr->getTextureRect();

            Assert::AreEqual(before.position.x, after.position.x);
            Assert::AreEqual(0, before.position.y);
            Assert::AreEqual(100, after.position.y);

            Assert::AreEqual(before.size.x, after.size.x);
            Assert::AreEqual(before.size.y, after.size.y);
        }
    };
}