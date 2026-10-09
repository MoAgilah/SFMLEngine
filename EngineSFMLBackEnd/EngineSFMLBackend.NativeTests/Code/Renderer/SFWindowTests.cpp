#include "CppUnitTest.h"

#include <Engine/Core/Constants.h>
#include <Renderer/SFWindow.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <string>
#include <Windows.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Renderer
{
	TEST_CLASS(SFWindowTests)
	{
	public:

		// ======================================================
		// Create
		// ======================================================

		TEST_METHOD(SFWindow_Create_ReturnsFalseIfWidthIsZero)
		{
			SFWindow window;

			Vector2u dimensions(0u, 600u);

			Assert::IsFalse(window.Create(dimensions, GameConstants::WindowTitle));
		}

		TEST_METHOD(SFWindow_Create_ReturnsFalseIfHeightIsZero)
		{
			SFWindow window;

			Vector2u dimensions(600u, 0u);

			Assert::IsFalse(window.Create(dimensions, GameConstants::WindowTitle));
		}

		TEST_METHOD(SFWindow_Create_CreatesWindow)
		{
			SFWindow window;

			Vector2u dimensions(
				static_cast<unsigned int>(GameConstants::ScreenDim.x),
				static_cast<unsigned int>(GameConstants::ScreenDim.y)
			);

			Assert::IsTrue(window.Create(dimensions, GameConstants::WindowTitle));

			auto sfWindow = static_cast<sf::RenderWindow*>(window.GetNativeHandle());
			Assert::IsNotNull(sfWindow);

			Vector2u size = sfWindow->getSize();

			Assert::AreEqual(dimensions.x, size.x);
			Assert::AreEqual(dimensions.y, size.y);
		}

		TEST_METHOD(SFWindow_Create_PreservesExistingWindowIfDimensionsInvalid)
		{
			SFWindow window;

			Vector2u dimensions(
				static_cast<unsigned int>(GameConstants::ScreenDim.x),
				static_cast<unsigned int>(GameConstants::ScreenDim.y)
			);

			Assert::IsTrue(window.Create(dimensions, GameConstants::WindowTitle));

			Vector2u newDims(600u, 0u);

			Assert::IsFalse(window.Create(newDims, GameConstants::WindowTitle));

			Assert::IsFalse(window.ShouldClose());

			auto sfWindow = static_cast<sf::RenderWindow*>(window.GetNativeHandle());
			Assert::IsNotNull(sfWindow);

			Vector2u size = sfWindow->getSize();

			Assert::AreEqual(dimensions.x, size.x);
			Assert::AreEqual(dimensions.y, size.y);
		}

		TEST_METHOD(SFWindow_Create_ReplacesExistingWindow)
		{
			SFWindow window;

			Vector2u dimensions(
				static_cast<unsigned int>(GameConstants::ScreenDim.x),
				static_cast<unsigned int>(GameConstants::ScreenDim.y)
			);

			Assert::IsTrue(window.Create(dimensions, GameConstants::WindowTitle));

			Vector2u newDims(600u, 800u);

			Assert::IsTrue(window.Create(newDims, GameConstants::WindowTitle));

			auto sfWindow = static_cast<sf::RenderWindow*>(window.GetNativeHandle());
			Assert::IsNotNull(sfWindow);

			Vector2u size = sfWindow->getSize();

			Assert::AreEqual(newDims.x, size.x);
			Assert::AreEqual(newDims.y, size.y);
		}

		TEST_METHOD(SFWindow_Create_ResetsShouldCloseAfterRecreation)
		{
			SFWindow window;

			Vector2u dimensions(
				static_cast<unsigned int>(GameConstants::ScreenDim.x),
				static_cast<unsigned int>(GameConstants::ScreenDim.y)
			);

			Assert::IsTrue(window.Create(dimensions, GameConstants::WindowTitle));

			Assert::IsFalse(window.ShouldClose());

			window.Close();

			Assert::IsTrue(window.ShouldClose());

			Assert::IsTrue(window.Create(dimensions, GameConstants::WindowTitle));

			Assert::IsFalse(window.ShouldClose());
		}

		// ======================================================
		// PollEvents
		// ======================================================

		TEST_METHOD(SFWindow_PollEvents_HandlesNoPendingEvents)
		{
			SFWindow window;

			Vector2u dimensions(
				static_cast<unsigned int>(GameConstants::ScreenDim.x),
				static_cast<unsigned int>(GameConstants::ScreenDim.y)
			);

			Assert::IsTrue(window.Create(dimensions, GameConstants::WindowTitle));

			window.PollEvents();

			Assert::IsFalse(window.ShouldClose());
		}

		TEST_METHOD(SFWindow_PollEvents_ClosesWindowOnCloseEvent)
		{
			SFWindow window;

			Vector2u dimensions(
				static_cast<unsigned int>(GameConstants::ScreenDim.x),
				static_cast<unsigned int>(GameConstants::ScreenDim.y)
			);

			Assert::IsTrue(window.Create(dimensions, GameConstants::WindowTitle));

			auto* sfWindow = static_cast<sf::RenderWindow*>(window.GetNativeHandle());
			Assert::IsNotNull(sfWindow);

			HWND hwnd = sfWindow->getNativeHandle();

			auto res = PostMessage(hwnd, WM_CLOSE, 0, 0);
			Assert::IsTrue(res != 0);

			window.PollEvents();

			Assert::IsTrue(window.ShouldClose());
		}

		// ======================================================
		// ShouldClose
		// ======================================================

		TEST_METHOD(SFWindow_ShouldClose_ReturnsFalseBeforeCreation)
		{
			SFWindow window;

			Assert::IsFalse(window.ShouldClose());
		}

		// ======================================================
		// Close
		// ======================================================

		TEST_METHOD(SFWindow_Close_HandlesUninitialisedWindow)
		{
			SFWindow window;

			window.Close();
		}

		// ======================================================
		// GetNativeHandle
		// ======================================================

		TEST_METHOD(SFWindow_GetNativeHandle_ReturnsNullBeforeCreation)
		{
			SFWindow window;

			Assert::IsNull(window.GetNativeHandle());
		}
	};
}