#include "CppUnitTest.h"

#include <Resources/SFMusic.h>
#include <Engine/Core/Constants.h>
#include <SFML/Audio/Music.hpp>
#include <chrono>
#include <string>
#include <thread>
#include <type_traits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Resources
{
	TEST_CLASS(SFMusicTests)
	{
	public:
		TEST_METHOD(SFMusic_Constructor_ConstructsValidTexture)
		{
			SFMusic music;

			sf::Music& nativeMusic = music.GetNativeMusic();

			Assert::IsNotNull(&nativeMusic);
		}

		TEST_METHOD(SFMusic_LoadFromFile_FailsWhenInvalidPath)
		{
			SFMusic music;

			Assert::IsFalse(music.LoadFromFile(""));
		}

		TEST_METHOD(SFMusic_LoadFromFile_Succeeds)
		{
			SFMusic music;

			std::string path = GameConstants::MusicFilePaths + "DefaultMusic.wav";

			Assert::IsTrue(music.LoadFromFile(path));
		}

		TEST_METHOD(SFMusic_GetNativeTexture_ReturnsReference)
		{
			SFMusic music;

			auto& nativeMusic = music.GetNativeMusic();

			static_assert(
				std::is_same_v<decltype(nativeMusic), sf::Music&>
				);
		}

		TEST_METHOD(SFMusic_GetNativeTexture_ReturnsConstReference)
		{
			const SFMusic music;

			const auto& nativeMusic = music.GetNativeMusic();

			static_assert(
				std::is_same_v<decltype(nativeMusic), const sf::Music&>
				);
		}

		TEST_METHOD(SFMusic_Play_WithoutLoadedMusic_RemainsStopped)
		{
			SFMusic music;

			auto& nativeMusic = music.GetNativeMusic();

			Assert::AreEqual(
				static_cast<int>(sf::Music::Status::Stopped),
				static_cast<int>(nativeMusic.getStatus())
			);

			music.Play();

			Assert::AreEqual(
				static_cast<int>(sf::Music::Status::Stopped),
				static_cast<int>(nativeMusic.getStatus())
			);
		}

		TEST_METHOD(SFMusic_Play_SetsStatusToPlaying)
		{
			SFMusic music;

			std::string path = GameConstants::MusicFilePaths + "DefaultMusic.wav";

			Assert::IsTrue(music.LoadFromFile(path));

			auto& nativeMusic = music.GetNativeMusic();

			Assert::AreEqual(
				static_cast<int>(sf::Music::Status::Stopped),
				static_cast<int>(nativeMusic.getStatus())
			);

			music.Play();

			Assert::AreEqual(
				static_cast<int>(sf::Music::Status::Playing),
				static_cast<int>(nativeMusic.getStatus())
			);
		}

		TEST_METHOD(SFMusic_Pause_WithoutLoadedMusic_RemainsStopped)
		{
			SFMusic music;

			auto& nativeMusic = music.GetNativeMusic();

			Assert::AreEqual(
				static_cast<int>(sf::Music::Status::Stopped),
				static_cast<int>(nativeMusic.getStatus())
			);

			music.Pause();

			Assert::AreEqual(
				static_cast<int>(sf::Music::Status::Stopped),
				static_cast<int>(nativeMusic.getStatus())
			);
		}

		TEST_METHOD(SFMusic_Pause_SetsStatusToPaused)
		{
			SFMusic music;

			std::string path = GameConstants::MusicFilePaths + "DefaultMusic.wav";

			Assert::IsTrue(music.LoadFromFile(path));

			auto& nativeMusic = music.GetNativeMusic();

			music.Play();

			Assert::AreEqual(
				static_cast<int>(sf::Music::Status::Playing),
				static_cast<int>(nativeMusic.getStatus())
			);

			music.Pause();

			Assert::AreEqual(
				static_cast<int>(sf::Music::Status::Paused),
				static_cast<int>(nativeMusic.getStatus())
			);
		}

		TEST_METHOD(SFMusic_Stop_WithoutLoadedMusic_RemainsStopped)
		{
			SFMusic music;

			auto& nativeMusic = music.GetNativeMusic();

			Assert::AreEqual(
				static_cast<int>(sf::Music::Status::Stopped),
				static_cast<int>(nativeMusic.getStatus())
			);

			music.Stop();

			Assert::AreEqual(
				static_cast<int>(sf::Music::Status::Stopped),
				static_cast<int>(nativeMusic.getStatus())
			);
		}

		TEST_METHOD(SFMusic_Stop_SetsStatusToStopped)
		{
			SFMusic music;

			std::string path = GameConstants::MusicFilePaths + "DefaultMusic.wav";

			Assert::IsTrue(music.LoadFromFile(path));

			auto& nativeMusic = music.GetNativeMusic();

			Assert::AreEqual(
				static_cast<int>(sf::Music::Status::Stopped),
				static_cast<int>(nativeMusic.getStatus())
			);

			music.Stop();

			Assert::AreEqual(
				static_cast<int>(sf::Music::Status::Stopped),
				static_cast<int>(nativeMusic.getStatus())
			);
		}

		TEST_METHOD(SFMusic_SetLoopTrue_EnablesLooping)
		{
			SFMusic music;

			auto& nativeMusic = music.GetNativeMusic();

			Assert::IsFalse(nativeMusic.isLooping());

			music.SetLoop(true);

			Assert::IsTrue(nativeMusic.isLooping());
		}

		TEST_METHOD(SFMusic_SetLoopFalse_DisablesLooping)
		{
			SFMusic music;

			auto& nativeMusic = music.GetNativeMusic();

			music.SetLoop(true);

			Assert::IsTrue(nativeMusic.isLooping());

			music.SetLoop(false);

			Assert::IsFalse(nativeMusic.isLooping());
		}
	};
}