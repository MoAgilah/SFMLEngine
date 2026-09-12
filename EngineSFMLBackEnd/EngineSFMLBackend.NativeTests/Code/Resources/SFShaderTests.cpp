#include "CppUnitTest.h"

#include <Testables/Resources/TestableSFShader.h>
#include <Engine/Core/Constants.h>
#include <SFML/Graphics/Shader.hpp>
#include <string>
#include <type_traits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Resources
{
	TEST_CLASS(SFShaderTests)
	{
	public:
		TEST_METHOD(SFShader_Constructor_ConstructsValidTexture)
		{
			TestableSFShader shader;

			sf::Shader& nativeShader = shader.GetNativeShader();

			Assert::IsNotNull(&nativeShader);
		}

		TEST_METHOD(SFShader_LoadFromFile_FailsWhenPathIsEmpty)
		{
			TestableSFShader shader;

			Assert::IsFalse(shader.LoadFromFile(""));
		}

		TEST_METHOD(SFShader_LoadFromFile_FailsWhenNoExtension)
		{
			TestableSFShader shader;

			Assert::IsFalse(shader.LoadFromFile("FadeInOutShader"));
		}

		TEST_METHOD(SFShader_LoadFromFile_FailsWhenInvalidExtension)
		{
			TestableSFShader shader;

			Assert::IsFalse(shader.LoadFromFile("FadeInOutShader.fake"));
		}

		TEST_METHOD(SFShader_LoadFromFile_FailsWhenPathIsInvalid)
		{
			TestableSFShader shader;

			Assert::IsFalse(shader.LoadFromFile("FadeInOutShader.frag"));
		}

		TEST_METHOD(SFShader_LoadFromFile_Succeeds)
		{
			TestableSFShader shader;

			std::string path = GameConstants::ShaderFilePaths + "FadeInOutShader.frag";

			Assert::IsTrue(shader.LoadFromFile(path));
		}

		TEST_METHOD(SFShader_GetNativeTexture_ReturnsReference)
		{
			TestableSFShader shader;

			auto& nativeShader = shader.GetNativeShader();

			static_assert(
				std::is_same_v<decltype(nativeShader), sf::Shader&>
				);
		}

		TEST_METHOD(SFShader_GetNativeTexture_ReturnsConstReference)
		{
			const TestableSFShader shader;

			const auto& nativeShader = shader.GetNativeShader();

			static_assert(
				std::is_same_v<decltype(nativeShader), const sf::Shader&>
				);
		}

		TEST_METHOD(SFShader_GetNativeShaderType_Vertex_ReturnsVertex)
		{
			TestableSFShader shader;

			auto retType = shader.GetNativeShaderTypeForTesting(ShaderType::Vertex);

			Assert::IsTrue(retType.has_value());

			Assert::AreEqual(static_cast<int>(sf::Shader::Type::Vertex), retType.value());
		}

		TEST_METHOD(SFShader_GetNativeShaderType_Fragment_ReturnsFragment)
		{
			TestableSFShader shader;

			auto retType = shader.GetNativeShaderTypeForTesting(ShaderType::Fragment);

			Assert::IsTrue(retType.has_value());

			Assert::AreEqual(static_cast<int>(sf::Shader::Type::Fragment), retType.value());
		}

		TEST_METHOD(SFShader_GetNativeShaderType_Geometry_ReturnsGeometry)
		{
			TestableSFShader shader;

			auto retType = shader.GetNativeShaderTypeForTesting(ShaderType::Geometry);

			Assert::IsTrue(retType.has_value());

			Assert::AreEqual(static_cast<int>(sf::Shader::Type::Geometry), retType.value());
		}

		TEST_METHOD(SFShader_GetNativeShaderType_Nullopt_ReturnsNullopt)
		{
			TestableSFShader shader;

			auto retType = shader.GetNativeShaderTypeForTesting(static_cast<ShaderType>(-1));

			Assert::IsFalse(retType.has_value());
		}

	};
}