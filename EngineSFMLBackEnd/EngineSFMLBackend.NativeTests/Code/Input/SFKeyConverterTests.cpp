#include "CppUnitTest.h"

#include <Input/SFKeyConverter.h>
#include <SFML/Window/Keyboard.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Input
{
	TEST_CLASS(SFKeyConverterTests)
	{
	public:
		TEST_METHOD(SFKeyConverter_AlphabetKey_ReturnsCorrectKeyCode)
		{
			const int platformKey = static_cast<int>(sf::Keyboard::Key::A);

			SFKeyConverter conv;

			const KeyCode result = conv.ConvertFromPlatform(platformKey);

			Assert::IsTrue(result == KeyCode::A);
		}

		TEST_METHOD(SFKeyConverter_NumberKey_ReturnsCorrectKeyCode)
		{
			const int platformKey = static_cast<int>(sf::Keyboard::Key::Num5);

			SFKeyConverter conv;

			const KeyCode result = conv.ConvertFromPlatform(platformKey);

			Assert::IsTrue(result == KeyCode::Num5);
		}

		TEST_METHOD(SFKeyConverter_LeftModifier_ReturnsCorrectKeyCode)
		{
			const int platformKey = static_cast<int>(sf::Keyboard::Key::LShift);

			SFKeyConverter conv;

			const KeyCode result = conv.ConvertFromPlatform(platformKey);

			Assert::IsTrue(result == KeyCode::LShift);
		}

		TEST_METHOD(SFKeyConverter_RightModifier_ReturnsCorrectKeyCode)
		{
			const int platformKey = static_cast<int>(sf::Keyboard::Key::RControl);

			SFKeyConverter conv;

			const KeyCode result = conv.ConvertFromPlatform(platformKey);

			Assert::IsTrue(result == KeyCode::RControl);
		}

		TEST_METHOD(SFKeyConverter_PunctuationKey_ReturnsCorrectKeyCode)
		{
			const int platformKey = static_cast<int>(sf::Keyboard::Key::Semicolon);

			SFKeyConverter conv;

			const KeyCode result = conv.ConvertFromPlatform(platformKey);

			Assert::IsTrue(result == KeyCode::Semicolon);
		}

		TEST_METHOD(SFKeyConverter_ControlKey_ReturnsCorrectKeyCode)
		{
			const int platformKey = static_cast<int>(sf::Keyboard::Key::Enter);

			SFKeyConverter conv;

			const KeyCode result = conv.ConvertFromPlatform(platformKey);

			Assert::IsTrue(result == KeyCode::Enter);
		}

		TEST_METHOD(SFKeyConverter_NavigationKey_ReturnsCorrectKeyCode)
		{
			const int platformKey = static_cast<int>(sf::Keyboard::Key::Home);

			SFKeyConverter conv;

			const KeyCode result = conv.ConvertFromPlatform(platformKey);

			Assert::IsTrue(result == KeyCode::Home);
		}

		TEST_METHOD(SFKeyConverter_ArrowKey_ReturnsCorrectKeyCode)
		{
			const int platformKey = static_cast<int>(sf::Keyboard::Key::Left);

			SFKeyConverter conv;

			const KeyCode result = conv.ConvertFromPlatform(platformKey);

			Assert::IsTrue(result == KeyCode::Left);
		}

		TEST_METHOD(SFKeyConverter_NumpadKey_ReturnsCorrectKeyCode)
		{
			const int platformKey = static_cast<int>(sf::Keyboard::Key::Numpad3);

			SFKeyConverter conv;

			const KeyCode result = conv.ConvertFromPlatform(platformKey);

			Assert::IsTrue(result == KeyCode::Numpad3);
		}

		TEST_METHOD(SFKeyConverter_NumpadOperator_ReturnsCorrectKeyCode)
		{
			const int platformKey = static_cast<int>(sf::Keyboard::Key::Add);

			SFKeyConverter conv;

			const KeyCode result = conv.ConvertFromPlatform(platformKey);

			Assert::IsTrue(result == KeyCode::Add);
		}

		TEST_METHOD(SFKeyConverter_FunctionKey_ReturnsCorrectKeyCode)
		{
			const int platformKey = static_cast<int>(sf::Keyboard::Key::F2);

			SFKeyConverter conv;

			const KeyCode result = conv.ConvertFromPlatform(platformKey);

			Assert::IsTrue(result == KeyCode::F2);
		}

		TEST_METHOD(SFKeyConverter_HighestFunctionKey_ReturnsCorrectKeyCode)
		{
			const int platformKey = static_cast<int>(sf::Keyboard::Key::F15);

			SFKeyConverter conv;

			const KeyCode result = conv.ConvertFromPlatform(platformKey);

			Assert::IsTrue(result == KeyCode::F15);
		}

		TEST_METHOD(SFKeyConverter_SpecialKey_ReturnsCorrectKeyCode)
		{
			const int platformKey = static_cast<int>(sf::Keyboard::Key::Pause);

			SFKeyConverter conv;

			const KeyCode result = conv.ConvertFromPlatform(platformKey);

			Assert::IsTrue(result == KeyCode::Pause);
		}

		TEST_METHOD(SFKeyConverter_InvalidKey_ReturnsUnknown)
		{
			const int platformKey = static_cast<int>(sf::Keyboard::Key::Unknown);

			SFKeyConverter conv;

			const KeyCode result = conv.ConvertFromPlatform(platformKey);

			Assert::IsTrue(result == KeyCode::Unknown);
		}
	};
}