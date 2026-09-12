#include "CppUnitTest.h"

#include <Resources/SFSound.h>
#include <Engine/Core/Constants.h>
#include <SFML/Audio/Sound.hpp>
#include <chrono>
#include <string>
#include <thread>
#include <type_traits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Resources
{
	TEST_CLASS(SFSoundTests)
	{
	public:
		TEST_METHOD(SFSound_Constructor_ConstructsValidTexture)
		{
			SFSound sound;

			sf::Sound& nativeSound = sound.GetNativeSound();

			Assert::IsNotNull(&nativeSound);
		}

		TEST_METHOD(SFSound_LoadFromFile_FailsWhenInvalidPath)
		{
			SFSound sound;

			Assert::IsFalse(sound.LoadFromFile(""));
		}

		TEST_METHOD(SFSound_LoadFromFile_Succeeds)
		{
			SFSound sound;

			std::string path = GameConstants::SoundFilePaths + "DefaultSound.wav";

			Assert::IsTrue(sound.LoadFromFile(path));
		}

		TEST_METHOD(SFSound_GetNativeTexture_ReturnsReference)
		{
			SFSound sound;

			auto& nativeSound = sound.GetNativeSound();

			static_assert(
				std::is_same_v<decltype(nativeSound), sf::Sound&>
				);
		}

		TEST_METHOD(SFSound_GetNativeTexture_ReturnsConstReference)
		{
			const SFSound sound;

			const auto& nativeSound = sound.GetNativeSound();

			static_assert(
				std::is_same_v<decltype(nativeSound), const sf::Sound&>
				);
		}

		TEST_METHOD(SFSound_Play_WithoutLoadedSound_RemainsStopped)
		{
			SFSound sound;

			auto& nativeSound = sound.GetNativeSound();

			Assert::AreEqual(
				static_cast<int>(sf::Sound::Status::Stopped),
				static_cast<int>(nativeSound.getStatus())
			);

			sound.Play();

			std::this_thread::sleep_for(std::chrono::milliseconds(5));

			Assert::AreEqual(
				static_cast<int>(sf::Sound::Status::Stopped),
				static_cast<int>(nativeSound.getStatus())
			);
		}

		TEST_METHOD(SFSound_Play_SetsStatusToPlaying)
		{
			SFSound sound;

			std::string path = GameConstants::SoundFilePaths + "DefaultSound.wav";

			Assert::IsTrue(sound.LoadFromFile(path));

			auto& nativeSound = sound.GetNativeSound();

			Assert::AreEqual(
				static_cast<int>(sf::Sound::Status::Stopped),
				static_cast<int>(nativeSound.getStatus())
			);

			sound.Play();

			Assert::AreEqual(
				static_cast<int>(sf::Sound::Status::Playing),
				static_cast<int>(nativeSound.getStatus())
			);
		}

		TEST_METHOD(SFSound_Pause_WithoutLoadedSound_RemainsStopped)
		{
			SFSound sound;

			auto& nativeSound = sound.GetNativeSound();

			Assert::AreEqual(
				static_cast<int>(sf::Sound::Status::Stopped),
				static_cast<int>(nativeSound.getStatus())
			);

			sound.Pause();

			Assert::AreEqual(
				static_cast<int>(sf::Sound::Status::Stopped),
				static_cast<int>(nativeSound.getStatus())
			);
		}

		TEST_METHOD(SFSound_Pause_SetsStatusToPaused)
		{
			SFSound sound;

			std::string path = GameConstants::SoundFilePaths + "DefaultSound.wav";

			Assert::IsTrue(sound.LoadFromFile(path));

			auto& nativeSound = sound.GetNativeSound();

			sound.Play();

			Assert::AreEqual(
				static_cast<int>(sf::Sound::Status::Playing),
				static_cast<int>(nativeSound.getStatus())
			);

			sound.Pause();

			Assert::AreEqual(
				static_cast<int>(sf::Sound::Status::Paused),
				static_cast<int>(nativeSound.getStatus())
			);
		}

		TEST_METHOD(SFSound_Stop_WithoutLoadedSound_RemainsStopped)
		{
			SFSound sound;

			auto& nativeSound = sound.GetNativeSound();

			Assert::AreEqual(
				static_cast<int>(sf::Sound::Status::Stopped),
				static_cast<int>(nativeSound.getStatus())
			);

			sound.Stop();

			Assert::AreEqual(
				static_cast<int>(sf::Sound::Status::Stopped),
				static_cast<int>(nativeSound.getStatus())
			);
		}

		TEST_METHOD(SFSound_Stop_SetsStatusToStopped)
		{
			SFSound sound;

			std::string path = GameConstants::SoundFilePaths + "DefaultSound.wav";

			Assert::IsTrue(sound.LoadFromFile(path));

			auto& nativeSound = sound.GetNativeSound();

			Assert::AreEqual(
				static_cast<int>(sf::Sound::Status::Stopped),
				static_cast<int>(nativeSound.getStatus())
			);

			sound.Stop();

			Assert::AreEqual(
				static_cast<int>(sf::Sound::Status::Stopped),
				static_cast<int>(nativeSound.getStatus())
			);
		}

		TEST_METHOD(SFSound_SetLoopTrue_EnablesLooping)
		{
			SFSound sound;

			auto& nativeSound = sound.GetNativeSound();

			Assert::IsFalse(nativeSound.isLooping());

			sound.SetLoop(true);

			Assert::IsTrue(nativeSound.isLooping());
		}

		TEST_METHOD(SFSound_SetLoopFalse_DisablesLooping)
		{
			SFSound sound;

			auto& nativeSound = sound.GetNativeSound();

			sound.SetLoop(true);

			Assert::IsTrue(nativeSound.isLooping());

			sound.SetLoop(false);

			Assert::IsFalse(nativeSound.isLooping());
		}
	};
}