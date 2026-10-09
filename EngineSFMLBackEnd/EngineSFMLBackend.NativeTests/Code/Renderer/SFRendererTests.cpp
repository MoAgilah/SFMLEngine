#include "CppUnitTest.h"

#include <Fakes/Drawables/FakeSprite.h>
#include <Fakes/Resources/FakeShader.h>
#include <Engine/Core/Constants.h>
#include <Renderer/SFRenderer.h>
#include <Renderer/SFWindow.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <string>
#include <Windows.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Renderer
{
	TEST_CLASS(SFRendererTests)
	{
	public:

		// ======================================================
		// Initialise
		// ======================================================

		TEST_METHOD(SFRenderer_Initialise_CreatesWindow)
		{
			SFRenderer renderer;

			Vector2u dimensions(
				static_cast<unsigned int>(GameConstants::ScreenDim.x),
				static_cast<unsigned int>(GameConstants::ScreenDim.y)
			);

			Assert::IsTrue(renderer.Initialise(dimensions, GameConstants::WindowTitle));

			Assert::IsNotNull(renderer.GetWindow());
		}

		TEST_METHOD(SFRenderer_Initialise_ReplacesExistingWindow)
		{
			SFRenderer renderer;

			Vector2u dimensions(
				static_cast<unsigned int>(GameConstants::ScreenDim.x),
				static_cast<unsigned int>(GameConstants::ScreenDim.y)
			);

			Assert::IsTrue(renderer.Initialise(dimensions, GameConstants::WindowTitle));

			Vector2u newDims(600u, 800u);

			Assert::IsTrue(renderer.Initialise(newDims, GameConstants::WindowTitle));

			auto* window = renderer.GetWindow();
			Assert::IsNotNull(window);

			auto* sfWindow = static_cast<sf::RenderWindow*>(window->GetNativeHandle());
			Assert::IsNotNull(sfWindow);

			Vector2u size = sfWindow->getSize();

			Assert::AreEqual(newDims.x, size.x);
			Assert::AreEqual(newDims.y, size.y);
		}

		TEST_METHOD(SFRenderer_Initialise_PreservesExistingWindowOnFailure)
		{
			SFRenderer renderer;

			Vector2u dimensions(
				static_cast<unsigned int>(GameConstants::ScreenDim.x),
				static_cast<unsigned int>(GameConstants::ScreenDim.y)
			);

			Assert::IsTrue(renderer.Initialise(dimensions, GameConstants::WindowTitle));

			auto originalWindow = renderer.GetWindow();
			Assert::IsNotNull(originalWindow);

			Vector2u newDims(600u, 0u);

			Assert::IsFalse(renderer.Initialise(newDims, GameConstants::WindowTitle));

			Assert::IsTrue(originalWindow == renderer.GetWindow());
		}

		// ======================================================
		// PollEvents
		// ======================================================

		TEST_METHOD(SFRenderer_PollWindowEvents_HandlesUninitialisedWindow)
		{
			SFRenderer renderer;

			renderer.PollWindowEvents();
		}

		TEST_METHOD(SFRenderer_PollWindowEvents_HandlesNoPendingEvents)
		{
			SFRenderer renderer;

			Vector2u dimensions(
				static_cast<unsigned int>(GameConstants::ScreenDim.x),
				static_cast<unsigned int>(GameConstants::ScreenDim.y)
			);

			Assert::IsTrue(renderer.Initialise(dimensions, GameConstants::WindowTitle));

			renderer.PollWindowEvents();

			auto window = renderer.GetWindow();
			Assert::IsNotNull(window);

			Assert::IsFalse(window->ShouldClose());
		}

		TEST_METHOD(SFRenderer_PollWindowEvents_ClosesWindowOnCloseEvent)
		{
			SFRenderer renderer;

			Vector2u dimensions(
				static_cast<unsigned int>(GameConstants::ScreenDim.x),
				static_cast<unsigned int>(GameConstants::ScreenDim.y)
			);

			Assert::IsTrue(renderer.Initialise(dimensions, GameConstants::WindowTitle));

			auto window = renderer.GetWindow();
			Assert::IsNotNull(window);

			auto* sfWindow = static_cast<sf::RenderWindow*>(window->GetNativeHandle());
			Assert::IsNotNull(sfWindow);

			HWND hwnd = sfWindow->getNativeHandle();

			auto res = PostMessage(hwnd, WM_CLOSE, 0, 0);
			Assert::IsTrue(res != 0);

			renderer.PollWindowEvents();

			Assert::IsTrue(window->ShouldClose());
		}

		// ======================================================
		// Clear
		// ======================================================

		TEST_METHOD(SFRenderer_Clear_HandlesUninitialisedRenderer)
		{
			SFRenderer renderer;

			renderer.Clear();
		}

		// ======================================================
		// Present
		// ======================================================

		TEST_METHOD(SFRenderer_Present_HandlesUninitialisedRenderer)
		{
			SFRenderer renderer;

			renderer.Present();
		}

		// ======================================================
		// Draw
		// ======================================================

		TEST_METHOD(SFRenderer_Draw_HandlesNullRenderable)
		{
			SFRenderer renderer;

			renderer.Draw(nullptr);
		}

		TEST_METHOD(SFRenderer_Draw_HandlesUninitialisedRenderer)
		{
			SFRenderer renderer;

			FakeSprite draw("spr");

			renderer.Draw(&draw);
		}

		TEST_METHOD(SFRenderer_DrawWithShader_HandlesNullRenderable)
		{
			SFRenderer renderer;

			FakeShader shader;

			renderer.Draw(nullptr, &shader);
		}

		TEST_METHOD(SFRenderer_DrawWithShader_HandlesNullShader)
		{
			SFRenderer renderer;

			FakeSprite draw("spr");

			renderer.Draw(&draw, nullptr);
		}

		TEST_METHOD(SFRenderer_DrawWithShader_HandlesUninitialisedRenderer)
		{
			SFRenderer renderer;

			FakeSprite draw("spr");

			FakeShader shader;

			renderer.Draw(&draw, &shader);
		}
	};
}
