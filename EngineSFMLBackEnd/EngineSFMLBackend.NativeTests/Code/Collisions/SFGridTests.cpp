#include "CppUnitTest.h"

#include <Engine/Core/GameManager.h>
#include <Collisions/SFGrid.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Collisions
{
    TEST_CLASS(SFGridTests)
    {
    public:
        TEST_METHOD(SFGrid_Constructor_CreatesExpectedTileCount)
        {
            SFGrid grid(2, 4, "", "Resources/TileTypes_Test.txt");

            auto tiles = grid.GetGrid();

            Assert::IsFalse(tiles.empty());

            Assert::AreEqual(std::size_t(2 * 4), tiles.size());
        }

        TEST_METHOD(SFGrid_Constructor_CreatesSFTiles)
        {
            SFGrid grid(2, 4, "", "Resources/TileTypes_Test.txt");

            auto tiles = grid.GetGrid();

            Assert::IsFalse(tiles.empty());

            for (const auto& tile : tiles)
            {
                Assert::IsNotNull(tile.get());

                auto sfTile = dynamic_cast<SFTile*>(tile.get());
                Assert::IsNotNull(sfTile);

                Assert::IsFalse(sfTile->GetHasFont());
            }
        }

        TEST_METHOD(SFGrid_Constructor_CreatesSFTilesWithSFText)
        {
            GameManager gm;

            SFGrid grid(2, 4, "Arial", "Resources/TileTypes_Test.txt");

            auto tiles = grid.GetGrid();

            Assert::IsFalse(tiles.empty());

            for (const auto& tile : tiles)
            {
                Assert::IsNotNull(tile.get());

                auto sfTile = dynamic_cast<SFTile*>(tile.get());
                Assert::IsNotNull(sfTile);

                Assert::IsTrue(sfTile->GetHasFont());
            }
        }

        TEST_METHOD(SFGrid_Constructor_LoadsTileTypesFromFile)
        {
            SFGrid grid(2, 4, "", "Resources/TileTypes_Test.txt");

            const auto& tiles = grid.GetGrid();

            for (std::size_t i = 0; i < tiles.size(); i++)
            {
                Assert::IsNotNull(tiles[i].get());

                Assert::AreEqual(static_cast<int>(i),
                    static_cast<int>(tiles[i]->GetType()));
            }
        }

        TEST_METHOD(SFGrid_Constructor_ArrangesTilePositions)
        {
            SFGrid grid(2, 4, "", "Resources/TileTypes_Test.txt");

            const auto& tiles = grid.GetGrid();

            for (std::size_t i = 0; i < tiles.size(); ++i)
            {
                Assert::IsNotNull(tiles[i].get());

                const std::size_t row = i / 4;
                const std::size_t col = i % 4;

                const float expectedX = 8.f + col * 16.f;
                const float expectedY = 8.f + row * 16.f;

                const auto pos = tiles[i]->GetPosition();

                Assert::AreEqual(expectedX, pos.x);
                Assert::AreEqual(expectedY, pos.y);

                auto box = tiles[i]->GetBoundingBox();
                Assert::IsNotNull(box);

                const auto boxPos = box->GetPosition();

                Assert::AreEqual(pos.x, boxPos.x);
                Assert::AreEqual(pos.y, boxPos.y);
            }
        }
    };
}