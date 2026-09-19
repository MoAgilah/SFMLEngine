#include "CppUnitTest.h"

#include <Engine/Core/GameManager.h>
#include <Engine/Collisions/BoundingBox.h>
#include <Drawables/SFShape.h>
#include <Fakes/Drawables/FakeSprite.h>
#include <Fakes/GameObjects/FakeDynamicObject.h>
#include <Testables/Collisions/TestableSFTile.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Collisions
{
    TEST_CLASS(SFTileTests)
    {
    public:

        // ======================================================
        // Constructors
        // ======================================================

        TEST_METHOD(SFTile_Constructor_NoFont_CreatesValidTile)
        {
            TestableSFTile tile(0, 1);

            Assert::IsNull(tile.GetTextObject().get());
        }

        TEST_METHOD(SFTile_Constructor_WithFont_CreatesTileWithText)
        {
            GameManager gm;

            TestableSFTile tile(0, 1, "Arial");

            Assert::IsNotNull(tile.GetTextObject().get());
        }

        TEST_METHOD(SFTile_Constructor_NegativeCoordinates_Throws)
        {
            Assert::ExpectException<std::invalid_argument>([]
                {
                    TestableSFTile tile(0, -1);
                });
        }


        // ======================================================
        // Render
        // ======================================================

        TEST_METHOD(SFTile_Render_NullRenderer_DoesNothing)
        {
            TestableSFTile tile(0, 1);

            tile.Render(nullptr);
        }


        // ======================================================
        // Resolve Collision - Shared Guards
        // ======================================================

        TEST_METHOD(SFTile_ResolveCollision_NullObject_DoesNothing)
        {
            TestableSFTile tile(0, 1);

            tile.ResolveCollision(nullptr, 0, 1);
        }

        TEST_METHOD(SFTile_ResolveCollision_NullObjectVolume_DoesNothing)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));

            TestableSFTile tile(0, 1);

            tile.ResolveCollision(&obj, 0, 1);
        }

        TEST_METHOD(SFTile_ResolveCollision_NullTileVolume_DoesNothing)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>());

            TestableSFTile tile(0, 1);

            tile.ForTestingMakeVolumeNull();

            tile.ResolveCollision(&obj, 0, 1);
        }

        TEST_METHOD(SFTile_ResolveCollision_EmptyTile_DoesNothing)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>());

            TestableSFTile tile(0, 1);

            tile.SetType(static_cast<int>(TileTypes::EMPTY));

            tile.ResolveCollision(&obj, 0, 1);
        }

        // ======================================================
        // Resolve Collision - One-Way Tile
        // ======================================================

        TEST_METHOD(SFTile_ResolveCollision_OWAY_FacingUp_DoesNothing)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>());

            obj.SetPosition(Vector2f(0.f, 12.f));
            obj.SetVelocity(Vector2f(0.f, -1.f));

            TestableSFTile tile(0, 1);

            tile.SetType(static_cast<int>(TileTypes::OWAY));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsFalse(tile.boxTopCalled);
        }

        TEST_METHOD(SFTile_ResolveCollision_OWAY_NoIntersection_DoesNothing)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f)));

            obj.SetPosition(Vector2f(0.f, -32.f));

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());
            obj.SetVelocity(Vector2f(0.f, 1.f));

            TestableSFTile tile(0, 1);

            tile.SetPosition(Vector2f(0.f, 0.f));

            tile.SetType(static_cast<int>(TileTypes::OWAY));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsFalse(tile.boxTopCalled);
        }

        TEST_METHOD(SFTile_ResolveCollision_OWAY_TopNotAboveObjectBottom_DoesNothing)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f)));

            obj.SetPosition(Vector2f(0.f, -20.f));

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());
            obj.SetVelocity(Vector2f(0.f, 1.f));

            TestableSFTile tile(0, 1);

            tile.SetPosition(Vector2f(0.f, 0.f));

            tile.SetType(static_cast<int>(TileTypes::OWAY));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsFalse(tile.boxTopCalled);
        }

        TEST_METHOD(SFTile_ResolveCollision_OWAY_ValidContact_ResolvesBoxTop)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f)));

            obj.SetPosition(Vector2f(0.f, -12.f));

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());
            obj.SetVelocity(Vector2f(0.f, 1.f));

            TestableSFTile tile(0, 1);

            tile.SetPosition(Vector2f(0.f, 0.f));

            tile.SetType(static_cast<int>(TileTypes::OWAY));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsTrue(tile.boxTopCalled);
        }


        // ======================================================
        // Resolve Collision - Ground Tile
        // ======================================================

        TEST_METHOD(SFTile_ResolveCollision_GRND_FacingUp_DoesNothing)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>());

            obj.SetPosition(Vector2f(0.f, 12.f));
            obj.SetVelocity(Vector2f(0.f, -1.f));

            TestableSFTile tile(0, 1);

            tile.SetType(static_cast<int>(TileTypes::GRND));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsFalse(tile.boxTopCalled);
        }

        TEST_METHOD(SFTile_ResolveCollision_GRND_TopNotAboveObjectBottom_DoesNothing)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f)));

            obj.SetPosition(Vector2f(0.f, -20.f));

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());
            obj.SetVelocity(Vector2f(0.f, 1.f));

            TestableSFTile tile(0, 1);

            tile.SetPosition(Vector2f(0.f, 0.f));

            tile.SetType(static_cast<int>(TileTypes::GRND));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsFalse(tile.boxTopCalled);
        }

        TEST_METHOD(SFTile_ResolveCollision_GRND_ValidContact_ResolvesBoxTop)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f)));

            obj.SetPosition(Vector2f(0.f, -12.f));

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());
            obj.SetVelocity(Vector2f(0.f, 1.f));

            TestableSFTile tile(0, 1);

            tile.SetPosition(Vector2f(0.f, 0.f));

            tile.SetType(static_cast<int>(TileTypes::GRND));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsTrue(tile.boxTopCalled);
        }


        // ======================================================
        // Resolve Collision - Corner Tiles
        // ======================================================

        // Left corner

        TEST_METHOD(SFTile_ResolveCollision_LCRN_FacingUp_DoesNothing)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>());

            obj.SetPosition(Vector2f(0.f, 12.f));
            obj.SetVelocity(Vector2f(0.f, -1.f));

            TestableSFTile tile(0, 1);

            tile.SetType(static_cast<int>(TileTypes::LCRN));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsFalse(tile.boxTopCalled);
        }

        TEST_METHOD(SFTile_ResolveCollision_LCRN_FacingDownAndCollisionDownButTopNotAbove_DoesNothing)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f)));

            obj.SetPosition(Vector2f(0.f, -20.f));

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());
            obj.SetVelocity(Vector2f(0.f, 1.f));

            TestableSFTile tile(0, 1);

            tile.SetPosition(Vector2f(0.f, 0.f));

            tile.SetType(static_cast<int>(TileTypes::LCRN));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsFalse(tile.boxTopCalled);
        }


        TEST_METHOD(SFTile_ResolveCollision_LCRN_FacingDownAndCollisionDown_ResolvesBoxTop)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f)));

            obj.SetPosition(Vector2f(0.f, 12.f));

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());
            obj.SetVelocity(Vector2f(0.f, 1.f));

            TestableSFTile tile(0, 1);

            tile.SetPosition(Vector2f(0.f, 0.f));

            tile.SetType(static_cast<int>(TileTypes::LCRN));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsTrue(tile.boxTopCalled);
        }

        TEST_METHOD(SFTile_ResolveCollision_LCRN_HorizontalCollision_ResolvesBoxHorizontally)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f)));

            obj.SetPosition(Vector2f(12.f, 0.f));

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());
            obj.SetVelocity(Vector2f(0.f, 1.f));

            TestableSFTile tile(0, 1);

            tile.SetPosition(Vector2f(0.f, 0.f));

            tile.SetType(static_cast<int>(TileTypes::LCRN));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsTrue(tile.boxHorizontalCalled);
        }

        TEST_METHOD(SFTile_ResolveCollision_LCRN_HorizontalFacingAndNonHorizontalCollision_ResolvesEdgeBounds)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f)));

            obj.SetPosition(Vector2f(0.f, -12.f));
            obj.SetPrevPosition(Vector2f(0.f, -12.f));

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());
            obj.SetVelocity(Vector2f(1.f, 0.f));

            TestableSFTile tile(0, 1);

            tile.SetPosition(Vector2f(0.f, 0.f));

            tile.SetType(static_cast<int>(TileTypes::LCRN));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsTrue(tile.edgeBoundsCalled);
            Assert::IsFalse(tile.boxTopCalled);
        }

        TEST_METHOD(SFTile_ResolveCollision_LCRN_HorizontalFacingAndNonHorizontalCollisionWithTopAbove_ResolvesBoxTopAndEdgeBounds)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f)));

            obj.SetPosition(Vector2f(0.f, -12.f));
            obj.SetPrevPosition(Vector2f(0.f, -20.f));

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());
            obj.SetVelocity(Vector2f(-1.f, 0.f));

            TestableSFTile tile(0, 1);

            tile.SetPosition(Vector2f(0.f, 0.f));

            tile.SetType(static_cast<int>(TileTypes::LCRN));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsTrue(tile.edgeBoundsCalled);
            Assert::IsTrue(tile.boxTopCalled);
        }


        // Right corner
        TEST_METHOD(SFTile_ResolveCollision_RCRN_FacingUp_DoesNothing)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>());

            obj.SetPosition(Vector2f(0.f, 12.f));
            obj.SetVelocity(Vector2f(0.f, -1.f));

            TestableSFTile tile(0, 1);

            tile.SetType(static_cast<int>(TileTypes::RCRN));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsFalse(tile.boxTopCalled);
        }

        TEST_METHOD(SFTile_ResolveCollision_RCRN_FacingDownAndCollisionDownButTopNotAbove_DoesNothing)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f)));

            obj.SetPosition(Vector2f(0.f, -20.f));

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());
            obj.SetVelocity(Vector2f(0.f, 1.f));

            TestableSFTile tile(0, 1);

            tile.SetPosition(Vector2f(0.f, 0.f));

            tile.SetType(static_cast<int>(TileTypes::RCRN));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsFalse(tile.boxTopCalled);
        }

        TEST_METHOD(SFTile_ResolveCollision_RCRN_FacingDownAndCollisionDown_ResolvesBoxTop)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f)));

            obj.SetPosition(Vector2f(0.f, 12.f));

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());
            obj.SetVelocity(Vector2f(0.f, 1.f));

            TestableSFTile tile(0, 1);

            tile.SetPosition(Vector2f(0.f, 0.f));

            tile.SetType(static_cast<int>(TileTypes::RCRN));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsTrue(tile.boxTopCalled);
        }

        TEST_METHOD(SFTile_ResolveCollision_RCRN_HorizontalCollision_ResolvesBoxHorizontally)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f)));

            obj.SetPosition(Vector2f(12.f, 0.f));

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());
            obj.SetVelocity(Vector2f(0.f, 1.f));

            TestableSFTile tile(0, 1);

            tile.SetPosition(Vector2f(0.f, 0.f));

            tile.SetType(static_cast<int>(TileTypes::RCRN));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsTrue(tile.boxHorizontalCalled);
        }

        TEST_METHOD(SFTile_ResolveCollision_RCRN_HorizontalFacingAndNonHorizontalCollision_ResolvesEdgeBounds)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f)));

            obj.SetPosition(Vector2f(0.f, -12.f));
            obj.SetPrevPosition(Vector2f(0.f, -12.f));

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());
            obj.SetVelocity(Vector2f(1.f, 0.f));

            TestableSFTile tile(0, 1);

            tile.SetPosition(Vector2f(0.f, 0.f));

            tile.SetType(static_cast<int>(TileTypes::RCRN));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsTrue(tile.edgeBoundsCalled);
            Assert::IsFalse(tile.boxTopCalled);
        }

        TEST_METHOD(SFTile_ResolveCollision_RCRN_HorizontalFacingAndNonHorizontalCollisionWithTopAbove_ResolvesBoxTopAndEdgeBounds)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f)));

            obj.SetPosition(Vector2f(0.f, -12.f));
            obj.SetPrevPosition(Vector2f(0.f, -20.f));

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());
            obj.SetVelocity(Vector2f(-1.f, 0.f));

            TestableSFTile tile(0, 1);

            tile.SetPosition(Vector2f(0.f, 0.f));

            tile.SetType(static_cast<int>(TileTypes::RCRN));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsTrue(tile.edgeBoundsCalled);
            Assert::IsTrue(tile.boxTopCalled);
        }


        // ======================================================
        // Resolve Collision - Wall Tile
        // ======================================================

        TEST_METHOD(SFTile_ResolveCollision_WALL_ResolvesBoxHorizontally)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>());

            TestableSFTile tile(0, 1);

            tile.SetType(static_cast<int>(TileTypes::WALL));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsTrue(tile.boxHorizontalCalled);
        }


        // ======================================================
        // Resolve Collision - Diagonal-Up Tile
        // ======================================================

        TEST_METHOD(SFTile_ResolveCollision_DIAGU_FacingUp_DoesNothing)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>());

            obj.SetPosition(Vector2f(0.f, 12.f));
            obj.SetVelocity(Vector2f(0.f, -1.f));

            TestableSFTile tile(0, 1);

            tile.SetType(static_cast<int>(TileTypes::DIAGU));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsFalse(tile.slopeTopCalled);
            Assert::IsFalse(tile.slopeInclineCalled);
            Assert::IsFalse(tile.slopeDeclineCalled);
        }

        TEST_METHOD(SFTile_ResolveCollision_DIAGU_FacingDown_ResolvesSlopeTop)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>());

            obj.SetPosition(Vector2f(0.f, -12.f));
            obj.SetVelocity(Vector2f(0.f, 1.f));

            TestableSFTile tile(0, 1);

            tile.SetType(static_cast<int>(TileTypes::DIAGU));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsTrue(tile.slopeTopCalled);
            Assert::IsFalse(tile.slopeInclineCalled);
            Assert::IsFalse(tile.slopeDeclineCalled);
        }

        TEST_METHOD(SFTile_ResolveCollision_DIAGU_FacingRight_ResolvesSlopeIncline)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>());

            obj.SetPosition(Vector2f(-12.f, 0.f));
            obj.SetVelocity(Vector2f(1.f, 0.f));

            TestableSFTile tile(0, 1);

            tile.SetType(static_cast<int>(TileTypes::DIAGU));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsFalse(tile.slopeTopCalled);
            Assert::IsTrue(tile.slopeInclineCalled);
            Assert::IsFalse(tile.slopeDeclineCalled);
        }

        TEST_METHOD(SFTile_ResolveCollision_DIAGU_FacingLeft_ResolvesSlopeDecline)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>());

            obj.SetPosition(Vector2f(12.f, 0.f));
            obj.SetVelocity(Vector2f(-1.f, 0.f));

            TestableSFTile tile(0, 1);

            tile.SetType(static_cast<int>(TileTypes::DIAGU));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsFalse(tile.slopeTopCalled);
            Assert::IsFalse(tile.slopeInclineCalled);
            Assert::IsTrue(tile.slopeDeclineCalled);
        }

        TEST_METHOD(SFTile_ResolveCollision_DIAGU_SlopeResolved_EnablesSlideLeft)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>());

            obj.SetPosition(Vector2f(0.f, -12.f));
            obj.SetVelocity(Vector2f(0.f, 1.f));

            TestableSFTile tile(0, 1);

            tile.SetType(static_cast<int>(TileTypes::DIAGU));
            tile.slopeTopResult = true;

            Assert::IsFalse(obj.GetShouldSlideLeft());

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsTrue(tile.slopeTopCalled);
            Assert::IsFalse(tile.slopeInclineCalled);
            Assert::IsFalse(tile.slopeDeclineCalled);

            Assert::IsTrue(obj.GetShouldSlideLeft());
        }

        TEST_METHOD(SFTile_ResolveCollision_DIAGU_SlopeNotResolved_DoesNotEnableSlideLeft)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>());

            obj.SetPosition(Vector2f(0.f, -12.f));
            obj.SetVelocity(Vector2f(0.f, 1.f));

            TestableSFTile tile(0, 1);

            tile.SetType(static_cast<int>(TileTypes::DIAGU));
            tile.slopeTopResult = false;

            Assert::IsFalse(obj.GetShouldSlideLeft());

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsTrue(tile.slopeTopCalled);
            Assert::IsFalse(tile.slopeInclineCalled);
            Assert::IsFalse(tile.slopeDeclineCalled);

            Assert::IsFalse(obj.GetShouldSlideLeft());
        }


        // ======================================================
        // Resolve Collision - Diagonal-Down Tile
        // ======================================================

        TEST_METHOD(SFTile_ResolveCollision_DIAGD_FacingUp_DoesNothing)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>());

            obj.SetPosition(Vector2f(0.f, 12.f));
            obj.SetVelocity(Vector2f(0.f, -1.f));

            TestableSFTile tile(0, 1);

            tile.SetType(static_cast<int>(TileTypes::DIAGD));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsFalse(tile.slopeTopCalled);
            Assert::IsFalse(tile.slopeInclineCalled);
            Assert::IsFalse(tile.slopeDeclineCalled);
        }

        TEST_METHOD(SFTile_ResolveCollision_DIAGD_FacingDown_ResolvesSlopeTop)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>());

            obj.SetPosition(Vector2f(0.f, -12.f));
            obj.SetVelocity(Vector2f(0.f, 1.f));

            TestableSFTile tile(0, 1);

            tile.SetType(static_cast<int>(TileTypes::DIAGD));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsTrue(tile.slopeTopCalled);
            Assert::IsFalse(tile.slopeInclineCalled);
            Assert::IsFalse(tile.slopeDeclineCalled);
        }

        TEST_METHOD(SFTile_ResolveCollision_DIAGD_FacingLeft_ResolvesSlopeIncline)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>());

            obj.SetPosition(Vector2f(12.f, 0.f));
            obj.SetVelocity(Vector2f(-1.f, 0.f));

            TestableSFTile tile(0, 1);

            tile.SetType(static_cast<int>(TileTypes::DIAGD));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsFalse(tile.slopeTopCalled);
            Assert::IsTrue(tile.slopeInclineCalled);
            Assert::IsFalse(tile.slopeDeclineCalled);
        }

        TEST_METHOD(SFTile_ResolveCollision_DIAGD_FacingRight_ResolvesSlopeDecline)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>());

            obj.SetPosition(Vector2f(-12.f, 0.f));
            obj.SetVelocity(Vector2f(1.f, 0.f));

            TestableSFTile tile(0, 1);

            tile.SetType(static_cast<int>(TileTypes::DIAGD));

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsFalse(tile.slopeTopCalled);
            Assert::IsFalse(tile.slopeInclineCalled);
            Assert::IsTrue(tile.slopeDeclineCalled);
        }

        TEST_METHOD(SFTile_ResolveCollision_DIAGD_SlopeResolved_EnablesSlideRight)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>());

            obj.SetPosition(Vector2f(0.f, -12.f));
            obj.SetVelocity(Vector2f(0.f, 1.f));

            TestableSFTile tile(0, 1);

            tile.SetType(static_cast<int>(TileTypes::DIAGD));
            tile.slopeTopResult = true;

            Assert::IsFalse(obj.GetShouldSlideRight());

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsTrue(tile.slopeTopCalled);
            Assert::IsFalse(tile.slopeInclineCalled);
            Assert::IsFalse(tile.slopeDeclineCalled);

            Assert::IsTrue(obj.GetShouldSlideRight());
        }

        TEST_METHOD(SFTile_ResolveCollision_DIAGD_SlopeNotResolved_DoesNotEnableSlideRight)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>());

            obj.SetPosition(Vector2f(0.f, -12.f));
            obj.SetVelocity(Vector2f(0.f, 1.f));

            TestableSFTile tile(0, 1);

            tile.SetType(static_cast<int>(TileTypes::DIAGD));
            tile.slopeTopResult = false;

            Assert::IsFalse(obj.GetShouldSlideRight());

            tile.ResolveCollision(&obj, 0, 1);

            Assert::IsTrue(tile.slopeTopCalled);
            Assert::IsFalse(tile.slopeInclineCalled);
            Assert::IsFalse(tile.slopeDeclineCalled);

            Assert::IsFalse(obj.GetShouldSlideRight());
        }


        // ======================================================
        // Set Position
        // ======================================================

        TEST_METHOD(SFTile_SetPosition_NullVolume_DoesNothing)
        {
            TestableSFTile tile(0, 1);

            auto pos = tile.GetPosition();

            tile.ForTestingMakeVolumeNull();

            tile.SetPosition(Vector2f(16.f, 16.f));

            Assert::AreEqual(pos.x, tile.GetPosition().x);
            Assert::AreEqual(pos.y, tile.GetPosition().y);
        }

        TEST_METHOD(SFTile_SetPosition_ValidPosition_UpdatesVolume)
        {
            TestableSFTile tile(0, 1);

            auto pos = tile.GetPosition();

            Assert::AreEqual(0.f, pos.x);
            Assert::AreEqual(0.f, pos.y);

            tile.SetPosition(Vector2f(16.f, 16.f));

            Assert::AreEqual(16.f, tile.GetPosition().x);
            Assert::AreEqual(16.f, tile.GetPosition().y);

            auto box = tile.GetBoundingBox();
            Assert::IsNotNull(box);

            Assert::AreEqual(tile.GetPosition().x, box->GetPosition().x);
            Assert::AreEqual(tile.GetPosition().y, box->GetPosition().y);
        }

        TEST_METHOD(SFTile_SetPosition_DIAGU_UpdatesSlopeGeometry)
        {
            TestableSFTile tile(0, 1);

            auto slope = tile.GetSlope(0, 1);

            Assert::AreEqual(0.f, slope.start.x);
            Assert::AreEqual(0.f, slope.start.y);
            Assert::AreEqual(0.f, slope.end.x);
            Assert::AreEqual(0.f, slope.end.y);

            tile.SetType(static_cast<int>(TileTypes::DIAGU));

            tile.SetPosition(Vector2f(16.f, 16.f));

            slope = tile.GetSlope(0, 1);

            Assert::AreEqual(-8.f, slope.start.x);
            Assert::AreEqual(8.f, slope.start.y);
            Assert::AreEqual(8.f, slope.end.x);
            Assert::AreEqual(-8.f, slope.end.y);
        }

        TEST_METHOD(SFTile_SetPosition_DIAGD_UpdatesSlopeGeometry)
        {
            TestableSFTile tile(0, 1);

            auto slope = tile.GetSlope(1, 0);

            Assert::AreEqual(0.f, slope.start.x);
            Assert::AreEqual(0.f, slope.start.y);
            Assert::AreEqual(0.f, slope.end.x);
            Assert::AreEqual(0.f, slope.end.y);

            tile.SetType(static_cast<int>(TileTypes::DIAGD));

            tile.SetPosition(Vector2f(16.f, 16.f));

            slope = tile.GetSlope(0, 1);

            Assert::AreEqual(-8.f, slope.start.x);
            Assert::AreEqual(-8.f, slope.start.y);
            Assert::AreEqual(8.f, slope.end.x);
            Assert::AreEqual(8.f, slope.end.y);
        }

        TEST_METHOD(SFTile_SetPosition_LCRN_UpdatesEdge)
        {
            TestableSFTile tile(0, 1);

            auto edge = tile.GetEdge();

            Assert::AreEqual(0.f, edge.start.x);
            Assert::AreEqual(0.f, edge.start.y);
            Assert::AreEqual(0.f, edge.end.x);
            Assert::AreEqual(0.f, edge.end.y);

            tile.SetType(static_cast<int>(TileTypes::LCRN));

            tile.SetPosition(Vector2f(16.f, 16.f));

            edge = tile.GetEdge();

            Assert::AreEqual(24.f, edge.start.x);
            Assert::AreEqual(8.f, edge.start.y);
            Assert::AreEqual(24.f, edge.end.x);
            Assert::AreEqual(-8.f, edge.end.y);
        }

        TEST_METHOD(SFTile_SetPosition_RCRN_UpdatesEdge)
        {
            TestableSFTile tile(0, 1);

            auto edge = tile.GetEdge();

            Assert::AreEqual(0.f, edge.start.x);
            Assert::AreEqual(0.f, edge.start.y);
            Assert::AreEqual(0.f, edge.end.x);
            Assert::AreEqual(0.f, edge.end.y);

            tile.SetType(static_cast<int>(TileTypes::RCRN));

            tile.SetPosition(Vector2f(16.f, 16.f));

            edge = tile.GetEdge();

            Assert::AreEqual(8.f, edge.start.x);
            Assert::AreEqual(8.f, edge.start.y);
            Assert::AreEqual(8.f, edge.end.x);
            Assert::AreEqual(-8.f, edge.end.y);
        }

        TEST_METHOD(SFTile_SetPosition_ValidText_UpdatesTextPosition)
        {
            GameManager gm;

            TestableSFTile tile(0, 1, "Arial");

            auto textObj = tile.GetTextObject();

            Assert::IsNotNull(textObj.get());

            auto pos = textObj->GetPosition();

            Assert::AreEqual(0.f, pos.x);
            Assert::AreEqual(0.f, pos.y);

            tile.SetPosition(Vector2f(16.f, 16.f));

            pos = textObj->GetPosition();

            Assert::AreEqual(6.f, pos.x);
            Assert::AreEqual(8.5f, pos.y);
        }



        // ======================================================
        // Set Fill Colour
        // ======================================================

        TEST_METHOD(SFTile_SetFillColour_NullVolume_DoesNothing)
        {
            TestableSFTile tile(0, 1);

            tile.ForTestingMakeVolumeNull();

            tile.SetFillColour(Colour::Red);

            auto box = tile.GetBoundingBox();
            Assert::IsNull(box);
        }

        TEST_METHOD(SFTile_SetFillColour_ValidShape_UpdatesFillColour)
        {
            TestableSFTile tile(0, 1);

            tile.SetFillColour(Colour::Red);

            auto box = tile.GetBoundingBox();
            Assert::IsNotNull(box);

            auto sfAABB = dynamic_cast<BoundingBox<SFRect>*>(box);
            Assert::IsNotNull(sfAABB);

            auto shape = sfAABB->GetShape();
            Assert::IsNotNull(shape);

            auto col = shape->GetFillColour();

            Assert::AreEqual(Colour::Red.r, col.r);
            Assert::AreEqual(Colour::Red.g, col.g);
            Assert::AreEqual(Colour::Red.b, col.b);
            Assert::AreEqual(Colour::Red.a, col.a);
        }

        // ======================================================
        // Set Outline Colour
        // ======================================================

        TEST_METHOD(SFTile_SetOutlineColour_NullVolume_DoesNothing)
        {
            TestableSFTile tile(0, 1);

            tile.ForTestingMakeVolumeNull();

            tile.SetOutlineColour(Colour::Red);

            auto box = tile.GetBoundingBox();
            Assert::IsNull(box);
        }

        TEST_METHOD(SFTile_SetOutlineColour_ValidShape_UpdatesOutlineColour)
        {
            TestableSFTile tile(0, 1);

            tile.SetOutlineColour(Colour::Red);

            auto box = tile.GetBoundingBox();
            Assert::IsNotNull(box);

            auto sfAABB = dynamic_cast<BoundingBox<SFRect>*>(box);
            Assert::IsNotNull(sfAABB);

            auto shape = sfAABB->GetShape();
            Assert::IsNotNull(shape);

            auto col = shape->GetOutlineColour();

            Assert::AreEqual(Colour::Red.r, col.r);
            Assert::AreEqual(Colour::Red.g, col.g);
            Assert::AreEqual(Colour::Red.b, col.b);
            Assert::AreEqual(Colour::Red.a, col.a);
        }

        // ======================================================
        // Resolve Object to Box Top
        // ======================================================

        TEST_METHOD(SFTile_ResolveObjectToBoxTop_NullObject_DoesNothing)
        {
            TestableSFTile tile(0, 1);

            tile.CallOriginalResolveObjectToBoxTop(nullptr, 0, 1);
        }

        TEST_METHOD(SFTile_ResolveObjectToBoxTop_DownwardVelocity_SnapsAndStopsVerticalMovement)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f)));

            auto pos = Vector2f(0.f, -12.f);

            obj.SetPosition(pos);

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());
            obj.SetVelocity(Vector2f(0.f, 1.f));

            TestableSFTile tile(0, 1);

            tile.SetPosition(Vector2f(0.f, 0.f));

            tile.CallOriginalResolveObjectToBoxTop(&obj, 1, 0);

            auto otherPos = obj.GetPrevPosition();

            Assert::AreEqual(pos.x, otherPos.x);
            Assert::AreEqual(pos.y, otherPos.y);

            pos = obj.GetPosition();

            Assert::AreEqual(0.f, pos.x);
            Assert::AreEqual(-16.f, pos.y);

            auto box = obj.GetVolume();
            Assert::IsNotNull(box);

            otherPos = box->GetPosition();

            Assert::AreEqual(pos.x, otherPos.x);
            Assert::AreEqual(pos.y, otherPos.y);

            Assert::AreEqual(0.f, obj.GetXVelocity());
            Assert::AreEqual(0.f, obj.GetYVelocity());
        }

        TEST_METHOD(SFTile_ResolveObjectToBoxTop_ResolvesGroundState)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f)));

            auto pos = Vector2f(0.f, -12.f);

            obj.SetPosition(pos);
            obj.SetOnGround(false);

            Assert::IsFalse(obj.GetOnGround());

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());
            obj.SetVelocity(Vector2f(0.f, 1.f));

            TestableSFTile tile(0, 1);

            tile.SetPosition(Vector2f(0.f, 0.f));

            tile.CallOriginalResolveObjectToBoxTop(&obj, 1, 0);

            Assert::IsTrue(obj.GetOnGround());
            Assert::IsFalse(obj.GetOnSlope());
        }


        // ======================================================
        // Resolve Object to Box Bottom
        // ======================================================

        TEST_METHOD(SFTile_ResolveObjectToBoxBottom_NullObject_DoesNothing)
        {
            TestableSFTile tile(0, 1);

            tile.CallOriginalResolveObjectToBoxBottom(nullptr, 0, 1);
        }

        TEST_METHOD(SFTile_ResolveObjectToBoxBottom_UpwardVelocity_SnapsAndStopsVerticalMovement)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f)));

            auto pos = Vector2f(0.f, 12.f);

            obj.SetPosition(pos);

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());
            obj.SetVelocity(Vector2f(0.f, -1.f));

            TestableSFTile tile(0, 1);

            tile.SetPosition(Vector2f(0.f, 0.f));

            tile.CallOriginalResolveObjectToBoxBottom(&obj, 1, 0);

            auto otherPos = obj.GetPrevPosition();

            Assert::AreEqual(pos.x, otherPos.x);
            Assert::AreEqual(pos.y, otherPos.y);

            pos = obj.GetPosition();

            Assert::AreEqual(0.f, pos.x);
            Assert::AreEqual(16.f, pos.y);

            auto box = obj.GetVolume();
            Assert::IsNotNull(box);

            otherPos = box->GetPosition();

            Assert::AreEqual(pos.x, otherPos.x);
            Assert::AreEqual(pos.y, otherPos.y);

            Assert::AreEqual(0.f, obj.GetXVelocity());
            Assert::AreEqual(0.f, obj.GetYVelocity());
        }


        // ======================================================
        // Resolve Object to Box Horizontally
        // ======================================================

        TEST_METHOD(SFTile_ResolveObjectToBoxHorizontally_NullObject_DoesNothing)
        {
            TestableSFTile tile(0, 1);

            tile.CallOriginalResolveObjectToBoxHorizontally(nullptr, 0, 1);
        }

        TEST_METHOD(SFTile_ResolveObjectToBoxHorizontally_PositiveSeparation_SnapsToRightAndStopsHorizontalMovement)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f)));

            auto pos = Vector2f(12.f, 0.f);

            obj.SetPosition(pos);

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());
            obj.SetVelocity(Vector2f(1.f, 0.f));

            TestableSFTile tile(0, 1);

            tile.SetPosition(Vector2f(0.f, 0.f));

            tile.CallOriginalResolveObjectToBoxHorizontally(&obj, 1, 0);

            auto otherPos = obj.GetPrevPosition();

            Assert::AreEqual(pos.x, otherPos.x);
            Assert::AreEqual(pos.y, otherPos.y);

            pos = obj.GetPosition();

            Assert::AreEqual(16.f, pos.x);
            Assert::AreEqual(0.f, pos.y);

            auto box = obj.GetVolume();
            Assert::IsNotNull(box);

            otherPos = box->GetPosition();

            Assert::AreEqual(pos.x, otherPos.x);
            Assert::AreEqual(pos.y, otherPos.y);

            Assert::AreEqual(0.f, obj.GetXVelocity());
            Assert::AreEqual(0.f, obj.GetYVelocity());
        }

        TEST_METHOD(SFTile_ResolveObjectToBoxHorizontally_NonPositiveSeparation_SnapsToLeftAndStopsHorizontalMovement)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f)));

            auto pos = Vector2f(-12.f, 0.f);

            obj.SetPosition(pos);

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());
            obj.SetVelocity(Vector2f(-1.f, 0.f));

            TestableSFTile tile(0, 1);

            tile.SetPosition(Vector2f(0.f, 0.f));

            tile.CallOriginalResolveObjectToBoxHorizontally(&obj, 1, 0);

            auto otherPos = obj.GetPrevPosition();

            Assert::AreEqual(pos.x, otherPos.x);
            Assert::AreEqual(pos.y, otherPos.y);

            pos = obj.GetPosition();

            Assert::AreEqual(-16.f, pos.x);
            Assert::AreEqual(0.f, pos.y);

            auto box = obj.GetVolume();
            Assert::IsNotNull(box);

            otherPos = box->GetPosition();

            Assert::AreEqual(pos.x, otherPos.x);
            Assert::AreEqual(pos.y, otherPos.y);

            Assert::AreEqual(0.f, obj.GetXVelocity());
            Assert::AreEqual(0.f, obj.GetYVelocity());
        }

        // ======================================================
        // Resolve Object to Slope Top
        // ======================================================

        TEST_METHOD(SFTile_ResolveObjectToSlopeTop_NullObject_ReturnsFalse)
        {
            TestableSFTile tile(0, 1);

            Assert::IsFalse(tile.CallOriginalResolveObjectToSlopeTop(nullptr, 0, 1));
        }

        TEST_METHOD(SFTile_ResolveObjectToSlopeTop_BottomNotAboveSlope_ReturnsFalse)
        {
            GameManager gm;

            FakeDynamicGameObject obj;
            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f)));

            const Vector2f pos(0.f, 100.f);
            obj.SetPosition(pos);

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);
            volume->Update(obj.GetPosition());

            obj.SetVelocity(Vector2f(0.f, 1.f));

            TestableSFTile tile(0, 1);
            tile.SetType(static_cast<int>(TileTypes::DIAGU));
            tile.SetPosition(Vector2f(0.f, 0.f));

            const bool resolved = tile.CallOriginalResolveObjectToSlopeTop(&obj, 1.f, 0.f);

            Assert::IsFalse(resolved);
            Assert::IsFalse(obj.GetOnGround());
            Assert::IsFalse(obj.GetOnSlope());
        }

        TEST_METHOD(SFTile_ResolveObjectToSlopeTop_NoIntersection_ReturnsFalse)
        {
            GameManager gm;

            FakeDynamicGameObject obj;
            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f)));

            const Vector2f pos(0.f, -100.f);
            obj.SetPosition(pos);

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);
            volume->Update(obj.GetPosition());

            obj.SetVelocity(Vector2f(0.f, 1.f));

            TestableSFTile tile(0, 1);
            tile.SetType(static_cast<int>(TileTypes::DIAGU));
            tile.SetPosition(Vector2f(0.f, 0.f));

            const bool resolved = tile.CallOriginalResolveObjectToSlopeTop(&obj, 1.f, 0.f);

            Assert::IsFalse(resolved);
            Assert::IsFalse(obj.GetOnGround());
            Assert::IsFalse(obj.GetOnSlope());
        }

        TEST_METHOD(SFTile_ResolveObjectToSlopeTop_DIAGU_ValidContact_SetsGroundAndSlope)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f)));

            auto pos = Vector2f(0.f, -6.f);

            obj.SetPosition(pos);

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());
            obj.SetVelocity(Vector2f(0.f, 1.f));

            TestableSFTile tile(0, 1);
            tile.SetType(static_cast<int>(TileTypes::DIAGU));
            tile.SetPosition(Vector2f(0.f, 0.f));

            const bool resolved = tile.CallOriginalResolveObjectToSlopeTop(&obj, 1, 0);

            Assert::IsTrue(resolved);
            Assert::IsTrue(obj.GetOnGround());
            Assert::IsTrue(obj.GetOnSlope());
        }

        TEST_METHOD(SFTile_ResolveObjectToSlopeTop_DIAGD_ValidContact_SetsGroundAndSlope)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f)));

            auto pos = Vector2f(0.f, -10.f);

            obj.SetPosition(pos);

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());
            obj.SetVelocity(Vector2f(0.f, 1.f));

            TestableSFTile tile(0, 1);
            tile.SetType(static_cast<int>(TileTypes::DIAGD));
            tile.SetPosition(Vector2f(0.f, 0.f));

            const bool resolved = tile.CallOriginalResolveObjectToSlopeTop(&obj, 1, 0);

            Assert::IsTrue(resolved);
            Assert::IsTrue(obj.GetOnGround());
            Assert::IsTrue(obj.GetOnSlope());
        }

        // ======================================================
        // Resolve Object to Slope Incline
        // ======================================================

        TEST_METHOD(SFTile_ResolveObjectToSlopeIncline_NullObject_ReturnsFalse)
        {
            TestableSFTile tile(0, 1);

            Assert::IsFalse(tile.CallOriginalResolveObjectToSlopeIncline(nullptr, 0, 1, 0, 1));
        }

        TEST_METHOD(SFTile_ResolveObjectToSlopeIncline_NoIntersection_ReturnsFalse)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(
                std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f))
            );

            const Vector2f initialPos(100.f, 100.f);

            obj.SetPosition(initialPos);
            obj.SetVelocity(Vector2f(0.f, 1.f));

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());

            TestableSFTile tile(0, 1);
            tile.SetType(static_cast<int>(TileTypes::DIAGU));
            tile.SetPosition(Vector2f(0.f, 0.f));

            const bool resolved =
                tile.CallOriginalResolveObjectToSlopeIncline(
                    &obj, 0, 1, 1.f, 0.f
                );

            Assert::IsFalse(resolved);
            Assert::IsFalse(obj.GetOnSlope());

            const auto finalPos = obj.GetPosition();

            Assert::AreEqual(initialPos.x, finalPos.x, 0.001f);
            Assert::AreEqual(initialPos.y, finalPos.y, 0.001f);

            const auto volumePos = volume->GetPosition();

            Assert::AreEqual(initialPos.x, volumePos.x, 0.001f);
            Assert::AreEqual(initialPos.y, volumePos.y, 0.001f);
        }

        TEST_METHOD(SFTile_ResolveObjectToSlopeIncline_NegligibleOffset_ReturnsFalse)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f)));

            const Vector2f pos(0.f, 0.f);

            obj.SetPosition(pos);
            obj.SetVelocity(Vector2f(0.f, 1.f));

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());

            TestableSFTile tile(0, 1);

            tile.SetType(static_cast<int>(TileTypes::DIAGU));
            tile.SetPosition(Vector2f(0.f, 0.f));

            const bool resolved =
                tile.CallOriginalResolveObjectToSlopeIncline(&obj, 1, 0, 1.f, 0.f);

            Assert::IsFalse(resolved);
            Assert::IsFalse(obj.GetOnSlope());

            const auto finalPos = obj.GetPosition();

            Assert::AreEqual(pos.x, finalPos.x);
            Assert::AreEqual(pos.y, finalPos.y);

            const auto volumePos = volume->GetPosition();

            Assert::AreEqual(pos.x, volumePos.x);
            Assert::AreEqual(pos.y, volumePos.y);
        }

        TEST_METHOD(SFTile_ResolveObjectToSlopeIncline_LargeOffset_ClampsMovement)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(
                std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f))
            );

            const Vector2f initialPos(0.f, 2.f);

            obj.SetPosition(initialPos);
            obj.SetVelocity(Vector2f(0.f, 1.f));

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());

            TestableSFTile tile(0, 1);

            tile.SetType(static_cast<int>(TileTypes::DIAGU));
            tile.SetPosition(Vector2f(0.f, 0.f));

            const Line2f slope = tile.GetSlope(0, 1);
            const Vector2f bottom = volume->GetPoint(Side::Bottom);

            const float horizontalDistance =
                std::abs(bottom.x - slope.start.x);

            const float expectedUnclampedMovement =
                volume->GetPosition().y -
                (horizontalDistance + slope.start.y);

            constexpr float maxMovement = 6.f;

            Assert::IsTrue(
                std::abs(expectedUnclampedMovement) > maxMovement
            );

            const float expectedClampedMovement =
                std::clamp(
                    expectedUnclampedMovement,
                    -maxMovement,
                    maxMovement
                );

            const bool resolved =
                tile.CallOriginalResolveObjectToSlopeIncline(
                    &obj, 0, 1, 1.f, 0.f
                );

            Assert::IsTrue(resolved);
            Assert::IsTrue(obj.GetOnSlope());

            const auto finalPos = obj.GetPosition();

            Assert::AreEqual(initialPos.x, finalPos.x, 0.001f);

            Assert::AreEqual(
                expectedClampedMovement,
                finalPos.y - initialPos.y,
                0.001f
            );

            const auto volumePos = volume->GetPosition();

            Assert::AreEqual(finalPos.x, volumePos.x, 0.001f);
            Assert::AreEqual(finalPos.y, volumePos.y, 0.001f);
        }

        // ======================================================
        // Resolve Object to Slope Decline
        // ======================================================

        TEST_METHOD(SFTile_ResolveObjectToSlopeDecline_NullObject_ReturnsFalse)
        {
            TestableSFTile tile(0, 1);

            Assert::IsFalse(tile.CallOriginalResolveObjectToSlopeDecline(nullptr, 1, 0, 0, 1));
        }


        TEST_METHOD(SFTile_ResolveObjectToSlopeDecline_Intersection_ReturnsFalse)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(
                std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f))
            );

            const Vector2f initialPos(0, -8.f);

            obj.SetPosition(initialPos);
            obj.SetVelocity(Vector2f(0.f, 1.f));

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());

            TestableSFTile tile(0, 1);
            tile.SetType(static_cast<int>(TileTypes::DIAGU));
            tile.SetPosition(Vector2f(0.f, 0.f));

            const bool resolved =
                tile.CallOriginalResolveObjectToSlopeDecline(
                    &obj, 1, 0, 1.f, 0.f
                );

            Assert::IsFalse(resolved);
            Assert::IsFalse(obj.GetOnSlope());

            const auto finalPos = obj.GetPosition();

            Assert::AreEqual(initialPos.x, finalPos.x, 0.001f);
            Assert::AreEqual(initialPos.y, finalPos.y, 0.001f);

            const auto volumePos = volume->GetPosition();

            Assert::AreEqual(initialPos.x, volumePos.x, 0.001f);
            Assert::AreEqual(initialPos.y, volumePos.y, 0.001f);
        }


        TEST_METHOD(SFTile_ResolveObjectToSlopeDecline_NegligibleOffset_ReturnsFalse)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(
                std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f))
            );

            const Vector2f initialPos(40.f, -40.f);

            obj.SetPosition(initialPos);
            obj.SetVelocity(Vector2f(0.f, 1.f));

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());

            TestableSFTile tile(0, 1);
            tile.SetType(static_cast<int>(TileTypes::DIAGU));
            tile.SetPosition(Vector2f(0.f, 0.f));

            const bool resolved =
                tile.CallOriginalResolveObjectToSlopeDecline(
                    &obj, 1, 0, 1.f, 0.f
                );

            Assert::IsFalse(resolved);
            Assert::IsFalse(obj.GetOnSlope());

            const auto finalPos = obj.GetPosition();

            Assert::AreEqual(initialPos.x, finalPos.x, 0.001f);
            Assert::AreEqual(initialPos.y, finalPos.y, 0.001f);

            const auto volumePos = volume->GetPosition();

            Assert::AreEqual(finalPos.x, volumePos.x, 0.001f);
            Assert::AreEqual(finalPos.y, volumePos.y, 0.001f);
        }



        TEST_METHOD(SFTile_ResolveObjectToSlopeDecline_LargeOffset_ClampsMovement)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(
                std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f))
            );

            const Vector2f initialPos(40.f, 0.f);

            obj.SetPosition(initialPos);
            obj.SetVelocity(Vector2f(0.f, 1.f));

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());

            TestableSFTile tile(0, 1);

            tile.SetType(static_cast<int>(TileTypes::DIAGU));
            tile.SetPosition(Vector2f(0.f, 0.f));

            const Line2f slope = tile.GetSlope(1, 0);
            const Vector2f bottom = volume->GetPoint(Side::Bottom);

            const float horizontalDistance =
                bottom.x - slope.start.x;

            const float expectedUnclampedMovement =
                volume->GetPosition().y -
                (horizontalDistance + slope.start.y);

            constexpr float maxMovement = 6.f;

            Assert::IsTrue(
                std::abs(expectedUnclampedMovement) > maxMovement
            );

            const float expectedClampedMovement =
                std::clamp(
                    expectedUnclampedMovement,
                    -maxMovement,
                    maxMovement
                );

            const bool resolved =
                tile.CallOriginalResolveObjectToSlopeDecline(
                    &obj, 1, 0, 1.f, 0.f
                );

            Assert::IsTrue(resolved);
            Assert::IsTrue(obj.GetOnSlope());

            const auto finalPos = obj.GetPosition();

            Assert::AreEqual(initialPos.x, finalPos.x, 0.001f);

            Assert::AreEqual(
                expectedClampedMovement,
                finalPos.y - initialPos.y,
                0.001f
            );

            const auto volumePos = volume->GetPosition();

            Assert::AreEqual(finalPos.x, volumePos.x, 0.001f);
            Assert::AreEqual(finalPos.y, volumePos.y, 0.001f);
        }

        // ======================================================
        // Resolve Object to Edge Bounds
        // ======================================================

        TEST_METHOD(SFTile_ResolveObjectToEdgeBounds_NullObject_DoesNothing)
        {
            TestableSFTile tile(0, 1);

            tile.CallOriginalResolveObjectToEdgeBounds(nullptr);
        }

        TEST_METHOD(SFTile_ResolveObjectToEdgeBounds_MovingAway_DoesNotChangeDirection)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(
                std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f))
            );

            obj.SetPosition(Vector2f(1.f, -8.f));
            obj.SetVelocity(Vector2f(-1.f, 0.f));

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());

            const bool initialDirection = obj.GetDirection();
            Assert::IsTrue(initialDirection);

            TestableSFTile tile(0, 1);
            tile.SetType(static_cast<int>(TileTypes::LCRN));
            tile.SetPosition(Vector2f(0.f, 0.f));

            tile.CallOriginalResolveObjectToEdgeBounds(&obj);

            Assert::AreEqual(initialDirection, obj.GetDirection());
        }

        TEST_METHOD(SFTile_ResolveObjectToEdgeBounds_MovingTowardsWithoutIntersection_DoesNotChangeDirection)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(
                std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f))
            );

            obj.SetPosition(Vector2f(2.f, 0.f));
            obj.SetVelocity(Vector2f(1.f, 0.f));

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());

            const bool initialDirection = obj.GetDirection();
            Assert::IsTrue(initialDirection);

            TestableSFTile tile(0, 1);
            tile.SetType(static_cast<int>(TileTypes::LCRN));
            tile.SetPosition(Vector2f(0.f, 0.f));

            tile.CallOriginalResolveObjectToEdgeBounds(&obj);

            Assert::AreEqual(initialDirection, obj.GetDirection());
        }


        TEST_METHOD(SFTile_ResolveObjectToEdgeBounds_MovingTowardsWithIntersection_ReversesDirection)
        {
            GameManager gm;

            FakeDynamicGameObject obj;

            obj.SetTestDrawable(std::make_shared<FakeSprite>("obj"));
            obj.SetTestVolume(
                std::make_shared<BoundingBox<SFRect>>(Vector2f(16.f, 16.f))
            );

            obj.SetPosition(Vector2f(1.f, -8.f));
            obj.SetVelocity(Vector2f(1.f, 0.f));

            auto* volume = obj.GetVolume();
            Assert::IsNotNull(volume);

            volume->Update(obj.GetPosition());

            const bool initialDirection = obj.GetDirection();
            Assert::IsTrue(initialDirection);

            TestableSFTile tile(0, 1);
            tile.SetType(static_cast<int>(TileTypes::LCRN));
            tile.SetPosition(Vector2f(0.f, 0.f));

            tile.CallOriginalResolveObjectToEdgeBounds(&obj);

            Assert::AreEqual(!initialDirection, obj.GetDirection());
        }
    };
}