#include "CppUnitTest.h"

#include <Engine/Core/Constants.h>
#include <Engine/Core/GameManager.h>
#include <Drawables/SFText.h>
#include <SFML/Graphics/Text.hpp>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Drawables
{
    TEST_CLASS(SFTextTests)
    {
    public:
        // ======================================================
        // Constructors
        // ======================================================

        TEST_METHOD(SFText_Constructor_ThrowsIfTextAnimIsNotStatic)
        {
            TextConfig config(
                "Arial",
                24u,
                Vector2f(100.f, 200.f),
                TextAnimType::Flashing
            );

            Assert::ExpectException<std::runtime_error>([&]
                {
                    SFText text(config);
                });
        }

        TEST_METHOD(SFText_Constructor_ThrowsIfGameManagerIsNull)
        {
            TextConfig config("Arial");

            Assert::ExpectException<std::runtime_error>([&]
                {
                    SFText text(config);
                });
        }

        TEST_METHOD(SFText_Constructor_ThrowsIfFontDoesNotExist)
        {
            GameManager gm;

            TextConfig config("DefaultFont");

            Assert::ExpectException<std::runtime_error>([&]
                {
                    SFText text(config);
                });
        }

        TEST_METHOD(SFText_ConstructorWithValidFont_CreatesSFText)
        {
            GameManager gm;

            TextConfig config("Arial");

            SFText text(config);

            auto* sfText = text.GetPrimaryDrawableAs<sf::Text>();
            Assert::IsNotNull(sfText);
        }

        TEST_METHOD(SFText_ConstructorWithDefaultConfig_AppliesTextConfiguration)
        {
            GameManager gm;

            TextConfig config(
                "Arial",
                24u,
                Vector2f(100.f, 200.f),
                TextAnimType::Static
            );

            SFText text(config);

            Assert::AreEqual(24u, text.GetCharSize());
            Assert::AreEqual(24.f / 10.f, text.GetOutlineThickness());

            auto def = Colour::Black;

            auto col = text.GetOutlineColour();

            Assert::AreEqual(def.r, col.r);
            Assert::AreEqual(def.g, col.g);
            Assert::AreEqual(def.b, col.b);
            Assert::AreEqual(def.a, col.a);

            auto pos = text.GetPosition();

            Assert::AreEqual(100.f, pos.x);
            Assert::AreEqual(200.f, pos.y);
        }

        // ======================================================
        // SetCharSize
        // ======================================================

        TEST_METHOD(SFText_SetCharSize_SetsCharSize)
        {
            GameManager gm;

            TextConfig config(
                "Arial",
                24u,
                Vector2f(100.f, 200.f),
                TextAnimType::Static
            );

            SFText text(config);

            text.SetCharSize(30u);

            Assert::AreEqual(30u, text.GetCharSize());
        }

        // ======================================================
        // ResetOutlineColour
        // ======================================================

        TEST_METHOD(SFText_ResetOutlineColour_RestoresConfiguredColour)
        {
            GameManager gm;

            TextConfig config(
                "Arial",
                24u,
                Vector2f(100.f, 200.f),
                TextAnimType::Static
            );

            SFText text(config);

            auto chg = Colour::White;

            text.SetOutlineColour(chg);

            auto col = text.GetOutlineColour();

            Assert::AreEqual(chg.r, col.r);
            Assert::AreEqual(chg.g, col.g);
            Assert::AreEqual(chg.b, col.b);
            Assert::AreEqual(chg.a, col.a);

            chg = Colour::Black;

            text.ResetOutlineColour();

            col = text.GetOutlineColour();

            Assert::AreEqual(chg.r, col.r);
            Assert::AreEqual(chg.g, col.g);
            Assert::AreEqual(chg.b, col.b);
            Assert::AreEqual(chg.a, col.a);
        }

        // ======================================================
        // SetText
        // ======================================================

        TEST_METHOD(SFText_SetText_SetsText)
        {

            GameManager gm;

            TextConfig config(
                "Arial",
                24u,
                Vector2f(100.f, 200.f),
                TextAnimType::Static
            );

            SFText text(config);

            std::string txt = "Hello World!";

            text.SetText(txt);

            auto* sfText = text.GetPrimaryDrawableAs<sf::Text>();
            Assert::IsNotNull(sfText);

            std::string str = sfText->getString();

            Assert::AreEqual(txt, str);
        }

        TEST_METHOD(SFText_SetText_WithLeftAlignment_SetsOrigin)
        {
            GameManager gm;

            TextConfig config(
                "Arial",
                24u,
                Vector2f(100.f, 200.f),
                TextAnimType::Static,
                Colour::Black,
                TextAlignment::LeftHand
            );

            SFText text(config);

            text.SetText("Hello World!");

            auto* sfText = text.GetPrimaryDrawableAs<sf::Text>();
            Assert::IsNotNull(sfText);

            auto bounds = sfText->getLocalBounds();

            const sf::Vector2f expectedOri
            {
                bounds.position.x + (bounds.size.x * 0.f),
                bounds.position.y + (bounds.size.y * 0.5f)
            };

            auto ori = text.GetOrigin();

            Assert::AreEqual(expectedOri.x, ori.x);
            Assert::AreEqual(expectedOri.y, ori.y);
        }

        TEST_METHOD(SFText_SetText_WithCenterAlignment_SetsOrigin)
        {
            GameManager gm;

            TextConfig config(
                "Arial",
                24u,
                Vector2f(100.f, 200.f),
                TextAnimType::Static,
                Colour::Black,
                TextAlignment::Center
            );

            SFText text(config);

            text.SetText("Hello World!");

            auto* sfText = text.GetPrimaryDrawableAs<sf::Text>();
            Assert::IsNotNull(sfText);

            auto bounds = sfText->getLocalBounds();

            const sf::Vector2f expectedOri
            {
                bounds.position.x + (bounds.size.x * 0.5f),
                bounds.position.y + (bounds.size.y * 0.5f)
            };

            auto ori = text.GetOrigin();

            Assert::AreEqual(expectedOri.x, ori.x);
            Assert::AreEqual(expectedOri.y, ori.y);
        }

        TEST_METHOD(SFText_SetText_WithRightAlignment_SetsOrigin)
        {
            GameManager gm;

            TextConfig config(
                "Arial",
                24u,
                Vector2f(100.f, 200.f),
                TextAnimType::Static,
                Colour::Black,
                TextAlignment::RightHand
            );

            SFText text(config);

            text.SetText("Hello World!");

            auto* sfText = text.GetPrimaryDrawableAs<sf::Text>();
            Assert::IsNotNull(sfText);

            auto bounds = sfText->getLocalBounds();

            const sf::Vector2f expectedOri
            {
                bounds.position.x + (bounds.size.x * 1.f),
                bounds.position.y + (bounds.size.y * 0.5f)
            };

            auto ori = text.GetOrigin();

            Assert::AreEqual(expectedOri.x, ori.x);
            Assert::AreEqual(expectedOri.y, ori.y);
        }

        // ======================================================
        // GetSize
        // ======================================================

        TEST_METHOD(SFText_GetSize_ReturnsTextBoundsSize)
        {
            GameManager gm;

            TextConfig config(
                "Arial",
                24u,
                Vector2f(100.f, 200.f),
                TextAnimType::Static
            );

            SFText text(config);

            text.SetText("Hello World!");

            auto* sfText = text.GetPrimaryDrawableAs<sf::Text>();
            Assert::IsNotNull(sfText);

            Vector2f size = sfText->getLocalBounds().size;

            auto retSize = text.GetSize();

            Assert::AreEqual(size.x, retSize.x);
            Assert::AreEqual(size.y, retSize.y);
        }
    };
}