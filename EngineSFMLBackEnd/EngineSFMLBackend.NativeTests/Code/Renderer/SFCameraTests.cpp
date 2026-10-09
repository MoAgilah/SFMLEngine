#include "CppUnitTest.h"

#include <Fakes/Drawables/FakeSprite.h>
#include <Fakes/GameObjects/FakeDynamicObject.h>
#include <Engine/Core/Constants.h>
#include <Renderer/SFRenderer.h>
#include <Renderer/SFCamera.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Renderer
{
	TEST_CLASS(SFCameraTests)
	{
	public:

		// ======================================================
		// Construction
		// ======================================================

		TEST_METHOD(SFCamera_Constructor_SetsViewSizeAndCenter)
		{
			SFCamera camera;

			auto view = camera.GetView();
			Assert::IsNotNull(view);

			auto size = view->getSize();

			Assert::AreEqual(GameConstants::ScreenDim.x, size.x);
			Assert::AreEqual(GameConstants::ScreenDim.y, size.y);

			auto center = view->getCenter();

			Assert::AreEqual(GameConstants::ScreenDim.x * 0.5f, center.x);
			Assert::AreEqual(GameConstants::ScreenDim.y * 0.5f, center.y);
		}

		TEST_METHOD(SFCamera_Constructor_SetsViewBoxSizeAndPosition)
		{
			SFCamera camera;

			auto viewBox = camera.GetViewBox();
			Assert::IsNotNull(viewBox);

			const auto& bounds = viewBox->GetWorldBounds();

			auto size = bounds.Max() - bounds.Min();

			Assert::AreEqual(GameConstants::ScreenDim.x, size.x);
			Assert::AreEqual(GameConstants::ScreenDim.y, size.y);

			auto position = (bounds.Min() + bounds.Max()) * 0.5f;

			Assert::AreEqual(GameConstants::ScreenDim.x * 0.5f, position.x);
			Assert::AreEqual(GameConstants::ScreenDim.y * 0.5f, position.y);
		}

		// ======================================================
		// Update
		// ======================================================

		TEST_METHOD(SFCamera_Update_PreservesPositionWhenNoObjectToFollow)
		{
			SFCamera camera;

			camera.Update();

			auto view = camera.GetView();
			Assert::IsNotNull(view);

			auto center = view->getCenter();

			Assert::AreEqual(GameConstants::ScreenDim.x * 0.5f, center.x);
			Assert::AreEqual(GameConstants::ScreenDim.y * 0.5f, center.y);

			auto viewBox = camera.GetViewBox();
			Assert::IsNotNull(viewBox);

			const auto& bounds = viewBox->GetWorldBounds();

			auto position = (bounds.Min() + bounds.Max()) * 0.5f;

			Assert::AreEqual(center.x, position.x);
			Assert::AreEqual(center.y, position.y);
		}

		TEST_METHOD(SFCamera_Update_FollowsObjectHorizontalPosition)
		{
			SFCamera camera;

			std::shared_ptr<FakeDynamicGameObject> obj = std::make_shared<FakeDynamicGameObject>();

			obj->SetTestDrawable(std::make_shared<FakeSprite>("obj"));

			obj->SetPosition(Vector2f(500.f, 300.f));

			camera.SetObjectToFollow(obj);

			camera.Update();

			auto view = camera.GetView();
			Assert::IsNotNull(view);

			auto center = view->getCenter();

			Assert::AreEqual(500.f, center.x);
			Assert::AreEqual(300.f, center.y);
		}

		TEST_METHOD(SFCamera_Update_ClampsCameraPositionToLeftBoundary)
		{
			SFCamera camera;

			std::shared_ptr<FakeDynamicGameObject> obj = std::make_shared<FakeDynamicGameObject>();

			obj->SetTestDrawable(std::make_shared<FakeSprite>("obj"));

			obj->SetPosition(Vector2f(100.f, 300.f));

			camera.SetObjectToFollow(obj);

			camera.Update();

			auto view = camera.GetView();
			Assert::IsNotNull(view);

			auto center = view->getCenter();

			Assert::AreEqual(300.f, center.x);
			Assert::AreEqual(300.f, center.y);
		}

		TEST_METHOD(SFCamera_Update_SynchronisesViewBoxWithView)
		{
			SFCamera camera;

			std::shared_ptr<FakeDynamicGameObject> obj = std::make_shared<FakeDynamicGameObject>();

			obj->SetTestDrawable(std::make_shared<FakeSprite>("obj"));

			obj->SetPosition(Vector2f(500.f, 300.f));

			camera.SetObjectToFollow(obj);

			camera.Update();

			auto view = camera.GetView();
			Assert::IsNotNull(view);

			auto center = view->getCenter();

			auto viewBox = camera.GetViewBox();
			Assert::IsNotNull(viewBox);

			const auto& bounds = viewBox->GetWorldBounds();

			auto position = (bounds.Min() + bounds.Max()) * 0.5f;

			Assert::AreEqual(center.x, position.x);
			Assert::AreEqual(center.y, position.y);
		}

		// ======================================================
		// Reset
		// ======================================================

		TEST_METHOD(SFCamera_Reset_HandlesNullRenderer)
		{
			SFCamera camera;

			camera.Reset(nullptr);
		}

		TEST_METHOD(SFCamera_Reset_HandlesUninitialisedRenderer)
		{
			SFCamera camera;

			SFRenderer renderer;

			camera.Reset(&renderer);
		}

		TEST_METHOD(SFCamera_Reset_AppliesViewToWindow)
		{
			SFRenderer renderer;

			Vector2u dimensions(
				static_cast<unsigned int>(GameConstants::ScreenDim.x),
				static_cast<unsigned int>(GameConstants::ScreenDim.y)
			);

			Assert::IsTrue(renderer.Initialise(dimensions, GameConstants::WindowTitle));

			SFCamera camera;

			camera.GetView()->setCenter({ 450.f, 300.f });

			camera.Reset(&renderer);

			auto* window = renderer.GetWindow();
			Assert::IsNotNull(window);

			auto* sfWindow = static_cast<sf::RenderWindow*>(window->GetNativeHandle());
			Assert::IsNotNull(sfWindow);

			const sf::View& activeView = sfWindow->getView();

			auto avCenter = activeView.getCenter();
			auto avSize = activeView.getSize();

			const sf::View* cameraView = camera.GetView();

			auto cvCenter = cameraView->getCenter();
			auto cvSize = cameraView->getSize();

			Assert::AreEqual(cvCenter.x, avCenter.x);
			Assert::AreEqual(cvCenter.y, avCenter.y);

			Assert::AreEqual(cvSize.x, avSize.x);
			Assert::AreEqual(cvSize.y, avSize.y);
		}
	};
}