#include "CppUnitTest.h"

#include <Engine/Core/Constants.h>
#include <Drawables/SFShape.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Drawables
{
    TEST_CLASS(SFTriangleTests)
    {
    public:
        // ======================================================
        // Constructors
        // ======================================================

        TEST_METHOD(SFTriangle_DefaultConstructor_SetsDefaults)
        {
            SFTriangle triangle;

            auto scl = triangle.GetScale();

            Assert::AreEqual(GameConstants::Scale.x, scl.x);
            Assert::AreEqual(GameConstants::Scale.y, scl.y);

            auto defFillCol = Colour::Transparent;

            auto fillCol = triangle.GetFillColour();

            Assert::AreEqual(defFillCol.r, fillCol.r);
            Assert::AreEqual(defFillCol.g, fillCol.g);
            Assert::AreEqual(defFillCol.b, fillCol.b);
            Assert::AreEqual(defFillCol.a, fillCol.a);

            auto defOutCol = Colour::Red;

            auto outCol = triangle.GetOutlineColour();

            Assert::AreEqual(defOutCol.r, outCol.r);
            Assert::AreEqual(defOutCol.g, outCol.g);
            Assert::AreEqual(defOutCol.b, outCol.b);
            Assert::AreEqual(defOutCol.a, outCol.a);

            float defThk = 1.0f;

            auto outThk = triangle.GetOutlineThickness();

            Assert::AreEqual(defThk, outThk);
        }

        TEST_METHOD(SFTriangle_ConstructorWithPointsAndPos_SetsPointsAndPosition)
        {
            std::array<Vector2f, 3> points =
            {
                Vector2f(10.0f, 20.0f),
                Vector2f(50.0f, 80.0f),
                Vector2f(90.0f, 30.0f)
            };

            Vector2f pos(125.0f, 75.0f);

            SFTriangle triangle(points, pos);

            auto retPoints = triangle.GetPoints();

            Assert::AreEqual(points.size(), retPoints.size());

            Assert::AreEqual(points[0].x, retPoints[0].x);
            Assert::AreEqual(points[0].y, retPoints[0].y);

            Assert::AreEqual(points[1].x, retPoints[1].x);
            Assert::AreEqual(points[1].y, retPoints[1].y);

            Assert::AreEqual(points[2].x, retPoints[2].x);
            Assert::AreEqual(points[2].y, retPoints[2].y);

            auto retPos = triangle.GetPosition();

            Assert::AreEqual(pos.x, retPos.x);
            Assert::AreEqual(pos.y, retPos.y);

            auto cen = triangle.GetCenter();

            Assert::AreEqual(retPos.x, cen.x);
            Assert::AreEqual(retPos.y, cen.y);
        }

        // ======================================================
        // Update
        // ======================================================

        TEST_METHOD(SFTriangle_Update_SetsPositionAndCenter)
        {
            SFTriangle triangle;

            Vector2f pos(125.0f, 75.0f);

            triangle.Update(pos);

            auto retPos = triangle.GetPosition();

            Assert::AreEqual(pos.x, retPos.x);
            Assert::AreEqual(pos.y, retPos.y);

            auto cen = triangle.GetCenter();

            Assert::AreEqual(retPos.x, cen.x);
            Assert::AreEqual(retPos.y, cen.y);
        }

        // ======================================================
        // Reset
        // ======================================================

        TEST_METHOD(SFTriangle_Reset_SetsPoints)
        {
            SFTriangle triangle;

            std::array<Vector2f, 3> points =
            {
                Vector2f(10.0f, 20.0f),
                Vector2f(50.0f, 80.0f),
                Vector2f(90.0f, 30.0f)
            };

            triangle.Reset(points);

            auto retPoints = triangle.GetPoints();

            Assert::AreEqual(points.size(), retPoints.size());

            Assert::AreEqual(points[0].x, retPoints[0].x);
            Assert::AreEqual(points[0].y, retPoints[0].y);

            Assert::AreEqual(points[1].x, retPoints[1].x);
            Assert::AreEqual(points[1].y, retPoints[1].y);

            Assert::AreEqual(points[2].x, retPoints[2].x);
            Assert::AreEqual(points[2].y, retPoints[2].y);
        }

        // ======================================================
        // GetTriangle
        // ======================================================

        TEST_METHOD(SFTriangle_GetTriangle_ReturnsConvexShape)
        {
            SFTriangle triangle;

            auto* expected = triangle.GetPrimaryDrawableAs<sf::ConvexShape>();
            auto* actual = triangle.GetTriangle();

            Assert::IsNotNull(expected);
            Assert::IsNotNull(actual);

            Assert::IsTrue(expected == actual);
        }

        // ======================================================
        // GetPoint
        // ======================================================

        TEST_METHOD(SFTriangle_GetPoint_ThrowsIfRangeIsInvalid)
        {
            SFTriangle triangle;

            Assert::ExpectException<std::runtime_error>([&]
                {
                    triangle.GetPoint(-1);
                });

            Assert::ExpectException<std::runtime_error>([&]
                {
                    triangle.GetPoint(3);
                });
        }

        TEST_METHOD(SFTriangle_GetPoint_ReturnsPoint)
        {
            SFTriangle triangle;

            std::array<Vector2f, 3> points =
            {
                Vector2f(10.0f, 20.0f),
                Vector2f(50.0f, 80.0f),
                Vector2f(90.0f, 30.0f)
            };

            triangle.Reset(points);

            int pntIdx = 1;

            auto retPnt = triangle.GetPoint(pntIdx);

            Assert::AreEqual(points[pntIdx].x, retPnt.x);
            Assert::AreEqual(points[pntIdx].y, retPnt.y);
        }

        // ======================================================
        // GetLine
        // ======================================================

        TEST_METHOD(SFTriangle_GetLine_ThrowsIfStartEqualsEnd)
        {
            SFTriangle triangle;

            Assert::ExpectException<std::runtime_error>([&]
                {
                    triangle.GetLine(0, 0);
                });
        }

        TEST_METHOD(SFTriangle_GetLine_ThrowsIfStartIsOutOfRange)
        {
            SFTriangle triangle;

            Assert::ExpectException<std::runtime_error>([&]
                {
                    triangle.GetLine(-1, 0);
                });
        }

        TEST_METHOD(SFTriangle_GetLine_ThrowsIfEndIsOutOfRange)
        {
            SFTriangle triangle;

            Assert::ExpectException<std::runtime_error>([&]
                {
                    triangle.GetLine(0, 3);
                });
        }

        TEST_METHOD(SFTriangle_GetLine_ReturnsLine)
        {
            SFTriangle triangle;

            std::array<Vector2f, 3> points =
            {
                Vector2f(10.0f, 20.0f),
                Vector2f(50.0f, 80.0f),
                Vector2f(90.0f, 30.0f)
            };

            triangle.Reset(points);

            int lineStr = 0;
            int lineEnd = 1;

            Line2f line(points[lineStr], points[lineEnd]);

            auto retLine = triangle.GetLine(lineStr, lineEnd);

            Assert::AreEqual(line.start.x, retLine.start.x);
            Assert::AreEqual(line.start.y, retLine.start.y);
            Assert::AreEqual(line.end.x, retLine.end.x);
            Assert::AreEqual(line.end.y, retLine.end.y);
        }

        // ======================================================
        // GetPoints
        // ======================================================

        TEST_METHOD(SFTriangle_GetPoints_ReturnsDefaultPointsIfNoTriangle)
        {
            SFTriangle triangle;

            triangle.SetDrawable(nullptr);

            std::array<Vector2f, 3> defPnts =
            {
                Vector2f(),
                Vector2f(),
                Vector2f()
            };

            auto retPoints = triangle.GetPoints();

            Assert::AreEqual(defPnts.size(), retPoints.size());

            Assert::AreEqual(defPnts[0].x, retPoints[0].x);
            Assert::AreEqual(defPnts[0].y, retPoints[0].y);

            Assert::AreEqual(defPnts[1].x, retPoints[1].x);
            Assert::AreEqual(defPnts[1].y, retPoints[1].y);

            Assert::AreEqual(defPnts[2].x, retPoints[2].x);
            Assert::AreEqual(defPnts[2].y, retPoints[2].y);
        }

        // ======================================================
        // SetPoints
        // ======================================================

        TEST_METHOD(SFTriangle_SetPoints_DoesNothingIfNoTriangle)
        {
            SFTriangle triangle;

            triangle.SetDrawable(nullptr);

            std::array<Vector2f, 3> points =
            {
                Vector2f(10.0f, 20.0f),
                Vector2f(50.0f, 80.0f),
                Vector2f(90.0f, 30.0f)
            };

            triangle.SetPoints(points);

            std::array<Vector2f, 3> defPnts =
            {
                Vector2f(),
                Vector2f(),
                Vector2f()
            };

            auto retPoints = triangle.GetPoints();

            Assert::AreEqual(defPnts.size(), retPoints.size());

            Assert::AreEqual(defPnts[0].x, retPoints[0].x);
            Assert::AreEqual(defPnts[0].y, retPoints[0].y);

            Assert::AreEqual(defPnts[1].x, retPoints[1].x);
            Assert::AreEqual(defPnts[1].y, retPoints[1].y);

            Assert::AreEqual(defPnts[2].x, retPoints[2].x);
            Assert::AreEqual(defPnts[2].y, retPoints[2].y);
        }

        TEST_METHOD(SFTriangle_SetPoints_SetsPoints)
        {
            SFTriangle triangle;

            std::array<Vector2f, 3> points =
            {
                Vector2f(10.0f, 20.0f),
                Vector2f(50.0f, 80.0f),
                Vector2f(90.0f, 30.0f)
            };

            triangle.SetPoints(points);

            auto retPoints = triangle.GetPoints();

            Assert::AreEqual(points.size(), retPoints.size());

            Assert::AreEqual(points[0].x, retPoints[0].x);
            Assert::AreEqual(points[0].y, retPoints[0].y);

            Assert::AreEqual(points[1].x, retPoints[1].x);
            Assert::AreEqual(points[1].y, retPoints[1].y);

            Assert::AreEqual(points[2].x, retPoints[2].x);
            Assert::AreEqual(points[2].y, retPoints[2].y);
        }
    };
}