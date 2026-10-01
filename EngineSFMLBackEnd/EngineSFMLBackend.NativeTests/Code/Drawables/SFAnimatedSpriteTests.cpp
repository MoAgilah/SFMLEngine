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

        TEST_METHOD(SFAnimatedSprite_Constructor_ThrowsIfRowsAreNotGreaterThanZero)
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

        TEST_METHOD(SFAnimatedSprite_Constructor_ThrowsIfColumnsAreNotGreaterThanZero)
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

        TEST_METHOD(SFAnimatedSprite_Constructor_ThrowsIfFrameDurationIsNotGreaterThanZero)
        {
            GameManager gm;

            Assert::ExpectException<std::runtime_error>([&]
                {
                    SFAnimatedSprite sprite(
                        "DefaultTexture",
                        4,
                        4,
                        -1,
                        1.0f
                    );
                });

            Assert::ExpectException<std::runtime_error>([&]
                {
                    SFAnimatedSprite sprite(
                        "DefaultTexture",
                        4,
                        4,
                        0,
                        1.0f
                    );
                });
        }

        TEST_METHOD(SFAnimatedSprite_Constructor_ThrowsIfAnimationSpeedIsNegative)
        {
            GameManager gm;

            Assert::ExpectException<std::runtime_error>([&]
                {
                    SFAnimatedSprite sprite(
                        "DefaultTexture",
                        4,
                        4,
                        GameConstants::AnimationFrameDurationMS,
                        -1.0f
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

        TEST_METHOD(SFAnimatedSprite_ConstructorWithValidParameters_SetsAnimationSpeed)
        {
            GameManager gm;

            SFAnimatedSprite sprite(
                "DefaultTexture",
                4,
                4,
                GameConstants::AnimationFrameDurationMS,
                1.0f
            );

            Assert::AreEqual(1.f, sprite.GetCurrAnimSpeed());
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

        TEST_METHOD(SFAnimatedSprite_SetFrameSize_ThrowsIfWidthIsNotGreaterThanZero)
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

        TEST_METHOD(SFAnimatedSprite_SetFrameSize_ThrowsIfHeightIsNotGreaterThanZero)
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
        // SetFrames
        // ======================================================

        TEST_METHOD(SFAnimatedSprite_SetFrames_ThrowsIfFrameDataIsEmpty)
        {
            GameManager gm;

            SFAnimatedSprite sprite(
                "DefaultTexture",
                4,
                4,
                GameConstants::AnimationFrameDurationMS,
                1.0f
            );

            std::vector<int> numFrames;

            Assert::ExpectException<std::runtime_error>([&]
                {
                    sprite.SetFrames(numFrames);
                });
        }

        TEST_METHOD(SFAnimatedSprite_SetFrames_ThrowsIfFrameCountIsNotGreaterThanZero)
        {
            GameManager gm;

            SFAnimatedSprite sprite(
                "DefaultTexture",
                4,
                4,
                GameConstants::AnimationFrameDurationMS,
                1.0f
            );

            std::vector<int> numFrames = { 1, 2, -1, 3 };

            Assert::ExpectException<std::runtime_error>([&]
                {
                    sprite.SetFrames(numFrames);
                });

            numFrames[2] = 0;

            Assert::ExpectException<std::runtime_error>([&]
                {
                    sprite.SetFrames(numFrames);
                });
        }

        TEST_METHOD(SFAnimatedSprite_SetFrames_SetsFrames)
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

            Assert::AreEqual(0, sprite.GetCurrentAnim());
        }

        // ======================================================
        // ChangeAnim
        // ======================================================

        TEST_METHOD(SFAnimatedSprite_ChangeAnim_ThrowsIfOutOfAnimBounds)
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

            Assert::ExpectException<std::runtime_error>([&]
                {
                    sprite.ChangeAnim(-1);
                });

            Assert::ExpectException<std::runtime_error>([&]
                {
                    sprite.ChangeAnim(4);
                });
        }

        TEST_METHOD(SFAnimatedSprite_ChangeAnim_ChangesAnimation)
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

            int newAnim = 2;

            sprite.ChangeAnim(newAnim);

            Assert::AreEqual(newAnim, sprite.GetCurrentAnim());
        }

        // ======================================================
        // UpdateAnimSpeed
        // ======================================================

        TEST_METHOD(SFAnimatedSprite_UpdateAnimSpeed_ThrowsIfAnimationSpeedIsNegative)
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
                    sprite.UpdateAnimSpeed(-1);
                });
        }

        TEST_METHOD(SFAnimatedSprite_UpdateAnimSpeed_ChangesAnimationSpeed)
        {
            GameManager gm;

            SFAnimatedSprite sprite(
                "DefaultTexture",
                4,
                4,
                GameConstants::AnimationFrameDurationMS,
                1.0f
            );

            float newSpd = 0.5f;

            sprite.UpdateAnimSpeed(newSpd);

            Assert::AreEqual(newSpd, sprite.GetCurrAnimSpeed());
        }

        // ======================================================
        // Update
        // ======================================================

        TEST_METHOD(SFAnimatedSprite_Update_ThrowsIfFramesHaveNotBeenConfigured)
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
                    sprite.Update(0.67f);
                });
        }

        TEST_METHOD(SFAnimatedSprite_Update_DoesNotAdvanceFrameBeforeFrameDuration)
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

            sprite.Update(0.03f);

            auto after = spr->getTextureRect();

            Assert::AreEqual(before.position.x, after.position.x);
            Assert::AreEqual(before.position.y, after.position.y);
            Assert::AreEqual(before.size.x, after.size.x);
            Assert::AreEqual(before.size.y, after.size.y);
        }

        TEST_METHOD(SFAnimatedSprite_Update_AdvancesFrameWhenFrameDurationReached)
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

        TEST_METHOD(SFAnimatedSprite_Update_AdvancesMultipleFramesWhenElapsedTimeAllows)
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

            sprite.Update(0.18f);

            auto after = spr->getTextureRect();

            Assert::AreEqual(0, before.position.x);
            Assert::AreEqual(375, after.position.x);

            Assert::AreEqual(before.position.y, after.position.y);
            Assert::AreEqual(before.size.x, after.size.x);
            Assert::AreEqual(before.size.y, after.size.y);
        }

        TEST_METHOD(SFAnimatedSprite_Update_PreservesRemainingFrameTime)
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

            sprite.Update(0.09f);

            auto after = spr->getTextureRect();

            Assert::AreEqual(0, before.position.x);
            Assert::AreEqual(125, after.position.x);

            Assert::AreEqual(before.position.y, after.position.y);
            Assert::AreEqual(before.size.x, after.size.x);
            Assert::AreEqual(before.size.y, after.size.y);

            before = after;

            sprite.Update(0.03f);

            after = spr->getTextureRect();

            Assert::AreEqual(125, before.position.x);
            Assert::AreEqual(250, after.position.x);

            Assert::AreEqual(before.position.y, after.position.y);
            Assert::AreEqual(before.size.x, after.size.x);
            Assert::AreEqual(before.size.y, after.size.y);
        }

        TEST_METHOD(SFAnimatedSprite_UpdateWithLooping_WrapsToFirstFrame)
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

            Assert::AreEqual(0, before.position.x);

            sprite.Update(0.25f);

            auto after = spr->getTextureRect();

            Assert::AreEqual(0, after.position.x);
            Assert::AreEqual(before.position.y, after.position.y);
            Assert::AreEqual(before.size.x, after.size.x);
            Assert::AreEqual(before.size.y, after.size.y);
        }

        TEST_METHOD(SFAnimatedSprite_UpdateWithoutLooping_StopsOnLastFrame)
        {
            GameManager gm;

            SFAnimatedSprite sprite(
                "DefaultTexture",
                4,
                4,
                GameConstants::AnimationFrameDurationMS,
                1.0f
            );

            sprite.SetShouldLoop(false);

            std::vector<int> numFrames = { 4, 2, 3, 1 };

            sprite.SetFrames(numFrames);

            auto spr = sprite.GetSprite();
            Assert::IsNotNull(spr);

            auto before = spr->getTextureRect();

            sprite.Update(0.25f);

            auto after = spr->getTextureRect();

            Assert::AreEqual(0, before.position.x);
            Assert::AreEqual(375, after.position.x);

            Assert::AreEqual(before.position.y, after.position.y);
            Assert::AreEqual(before.size.x, after.size.x);
            Assert::AreEqual(before.size.y, after.size.y);
        }

        TEST_METHOD(SFAnimatedSprite_UpdateWithoutLooping_SetsPlayedOnceAfterCompletion)
        {
            GameManager gm;

            SFAnimatedSprite sprite(
                "DefaultTexture",
                4,
                4,
                GameConstants::AnimationFrameDurationMS,
                1.0f
            );

            sprite.SetShouldLoop(false);

            std::vector<int> numFrames = { 4, 2, 3, 1 };

            sprite.SetFrames(numFrames);

            auto spr = sprite.GetSprite();
            Assert::IsNotNull(spr);

            Assert::IsFalse(sprite.PlayedOnce());

            sprite.Update(0.25f);

            Assert::IsTrue(sprite.PlayedOnce());
        }

        TEST_METHOD(SFAnimatedSprite_UpdateAfterChangeAnim_UsesSelectedAnimation)
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