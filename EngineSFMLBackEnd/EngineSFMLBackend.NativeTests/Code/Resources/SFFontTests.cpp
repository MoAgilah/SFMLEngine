#include "CppUnitTest.h"

#include <Resources/SFFont.h>
#include <Engine/Core/Constants.h>
#include <SFML/Graphics/Font.hpp>
#include <string>
#include <type_traits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Resources
{
	TEST_CLASS(SFFontTests)
	{
	public:
		TEST_METHOD(SFFont_Constructor_ConstructsValidTexture)
		{
			SFFont font;

			sf::Font& nativeFont = font.GetNativeFont();

			Assert::IsNotNull(&nativeFont);
		}

		TEST_METHOD(SFFont_LoadFromFile_FailsWhenInvalidPath)
		{
			SFFont font;

			Assert::IsFalse(font.LoadFromFile(""));
		}

		TEST_METHOD(SFFont_LoadFromFile_Succeeds)
		{
			SFFont font;

			std::string path = GameConstants::FontFilePaths + "Arial.ttf";

			Assert::IsTrue(font.LoadFromFile(path));
		}

		TEST_METHOD(SFFont_GetNativeTexture_ReturnsReference)
		{
			SFFont font;

			auto& nativeFont = font.GetNativeFont();

			static_assert(
				std::is_same_v<decltype(nativeFont), sf::Font&>
				);
		}

		TEST_METHOD(SFFont_GetNativeTexture_ReturnsConstReference)
		{
			const SFFont font;

			const auto& nativeFont = font.GetNativeFont();

			static_assert(
				std::is_same_v<decltype(nativeFont), const sf::Font&>
				);
		}
	};
}