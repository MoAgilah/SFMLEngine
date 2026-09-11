#include "CppUnitTest.h"


#include <Resources/SFFont.h>
#include <Resources/SFMusic.h>
#include <Resources/SFShader.h>
#include <Resources/SFSound.h>
#include <Resources/SFTexture.h>
#include <Engine/Core/Constants.h>
#include <Utilities/ResourceLoader.h>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utilities
{
	TEST_CLASS(SFResourceLoaderTests)
	{
	public:

		TEST_METHOD(SFResourceLoader_CanLoadTexture)
		{
			ResourceLoader<ITexture> loader(GameConstants::TextureFilePaths);

			Assert::AreEqual(size_t(1), loader.GetResourceCount());

			Assert::IsNotNull(loader.GetResource("DefaultTexture"));
		}

		TEST_METHOD(SFResourceLoader_CanLoadShader)
		{
			ResourceLoader<IShader> loader(GameConstants::ShaderFilePaths);

			Assert::AreEqual(size_t(1), loader.GetResourceCount());

			Assert::IsNotNull(loader.GetResource("FadeInOutShader"));
		}

		TEST_METHOD(SFResourceLoader_CanLoadFont)
		{
			ResourceLoader<IFont> loader(GameConstants::FontFilePaths);

			Assert::AreEqual(size_t(1), loader.GetResourceCount());

			Assert::IsNotNull(loader.GetResource("Arial"));
		}

		TEST_METHOD(SFResourceLoader_CanLoadSound)
		{
			ResourceLoader<ISound> loader(GameConstants::SoundFilePaths);

			Assert::AreEqual(size_t(1), loader.GetResourceCount());

			Assert::IsNotNull(loader.GetResource("DefaultSound"));
		}

		TEST_METHOD(SFResourceLoader_CanLoadMusic)
		{
			ResourceLoader<IMusic> loader(GameConstants::MusicFilePaths);

			Assert::AreEqual(size_t(1), loader.GetResourceCount());

			Assert::IsNotNull(loader.GetResource("DefaultMusic"));
		}
	};
}