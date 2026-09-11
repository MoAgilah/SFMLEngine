#include "CppUnitTest.h"

#include <Utilities/Colour.h>
#include <SFML/Graphics/Color.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Utilities
{
	TEST_CLASS(SFColourTests)
	{
	public:
		TEST_METHOD(SFColour_Constructor_SetsRGBAValuesCorrectly)
		{
			sf::Color sfCol(sf::Color::Blue);

			Colour col(sfCol);

			Assert::AreEqual(sf::Color::Blue.r, col.r);
			Assert::AreEqual(sf::Color::Blue.g, col.g);
			Assert::AreEqual(sf::Color::Blue.b, col.b);
			Assert::AreEqual(sf::Color::Blue.a, col.a);
		}

		TEST_METHOD(SFColour_ToSFML_ConvertsRGBAValuesCorrectly)
		{
			Colour col = Colour::Blue;

			sf::Color sfCol = col.ToSFML();

			Assert::AreEqual(col.r, sfCol.r);
			Assert::AreEqual(col.g, sfCol.g);
			Assert::AreEqual(col.b, sfCol.b);
			Assert::AreEqual(col.a, sfCol.a);
		}

		TEST_METHOD(SFColour_ImplicitConversion_ConvertsRGBAValuesCorrectly)
		{
			Colour col = Colour::Blue;

			sf::Color sfCol = col;

			Assert::AreEqual(col.r, sfCol.r);
			Assert::AreEqual(col.g, sfCol.g);
			Assert::AreEqual(col.b, sfCol.b);
			Assert::AreEqual(col.a, sfCol.a);
		}
	};
}