#include "CppUnitTest.h"

#include <Resources/SFTexture.h>
#include <Engine/Core/Constants.h>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <type_traits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Resources
{
	TEST_CLASS(SFTextureTests)
	{
	public:
		TEST_METHOD(SFTexture_Constructor_ConstructsValidTexture)
		{
			SFTexture texture;

			sf::Texture& nativeTexture = texture.GetNativeTexture();

			Assert::IsNotNull(&nativeTexture);
		}

		TEST_METHOD(SFTexture_LoadFromFile_FailsWhenInvalidPath)
		{
			SFTexture texture;

			Assert::IsFalse(texture.LoadFromFile(""));
		}

		TEST_METHOD(SFTexture_LoadFromFile_Succeeds)
		{
			SFTexture texture;

			std::string path = GameConstants::TextureFilePaths + "DefaultTexture.png";

			Assert::IsTrue(texture.LoadFromFile(path));
		}

		TEST_METHOD(SFTexture_GetNativeTexture_ReturnsReference)
		{
			SFTexture texture;

			auto& nativeTexture = texture.GetNativeTexture();

			static_assert(
				std::is_same_v<decltype(nativeTexture), sf::Texture&>
				);
		}

		TEST_METHOD(SFTexture_GetNativeTexture_ReturnsConstReference)
		{
			const SFTexture texture;

			const auto& nativeTexture = texture.GetNativeTexture();

			static_assert(
				std::is_same_v<decltype(nativeTexture), const sf::Texture&>
				);
		}

	};
}