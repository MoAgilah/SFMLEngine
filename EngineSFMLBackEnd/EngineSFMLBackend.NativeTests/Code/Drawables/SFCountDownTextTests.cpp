#include "CppUnitTest.h"

#include <Fakes/Effects/FakeShaderEffect.h>
#include <Fakes/Resources/FakeShader.h>
#include <Engine/Core/Constants.h>
#include <Engine/Core/GameManager.h>
#include <Drawables/SFText.h>
#include <SFML/Graphics/Text.hpp>
#include <string>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Drawables
{
    TEST_CLASS(SFCountDownTextTests)
    {
    public:
        // ======================================================
        // Construction
        // ======================================================

        TEST_METHOD(SFCountDownText_Constructor_DisplaysInitialCount)
        {
            GameManager gm;

            TextConfig config(
                "Arial",
                24u,
                Vector2f(100.f, 200.f)
            );

            int startFrom = 3;

            SFCountDownText text(config, 1.f, startFrom, "Finito");

            auto* sfText = text.GetPrimaryDrawableAs<sf::Text>();
            Assert::IsNotNull(sfText);

            std::string str = sfText->getString();

            Assert::AreEqual(std::to_string(startFrom), str);
        }

        // ======================================================
        // Update
        // ======================================================

        TEST_METHOD(SFCountDownText_UpdateBeforeInterval_DisplaysCurrentCount)
        {
            GameManager gm;

            TextConfig config(
                "Arial",
                24u,
                Vector2f(100.f, 200.f)
            );

            int startFrom = 3;

            SFCountDownText text(config, 1.f, startFrom, "Finito");

            text.Update(0.25f);

            auto* sfText = text.GetPrimaryDrawableAs<sf::Text>();
            Assert::IsNotNull(sfText);

            std::string str = sfText->getString();

            Assert::AreEqual(std::to_string(startFrom), str);
        }

        TEST_METHOD(SFCountDownText_UpdateAfterInterval_DisplaysDecrementedCount)
        {
            GameManager gm;

            TextConfig config(
                "Arial",
                24u,
                Vector2f(100.f, 200.f)
            );

            SFCountDownText text(config, 1.f, 3, "Finito");

            text.Update(1.f);

            auto* sfText = text.GetPrimaryDrawableAs<sf::Text>();
            Assert::IsNotNull(sfText);

            std::string str = sfText->getString();

            Assert::AreEqual(std::to_string(2), str);
        }

        TEST_METHOD(SFCountDownText_UpdateWhenCountdownEnds_DisplaysCountdownMessage)
        {
            GameManager gm;

            TextConfig config(
                "Arial",
                24u,
                Vector2f(100.f, 200.f)
            );

            std::string countdownMsg = "Finito";

            SFCountDownText text(config, 1.f, 3, countdownMsg);

            text.Update(1.f);
            text.Update(1.f);
            text.Update(1.f);

            auto* sfText = text.GetPrimaryDrawableAs<sf::Text>();
            Assert::IsNotNull(sfText);

            std::string str = sfText->getString();

            Assert::AreEqual(countdownMsg, str);
        }
    };
}