#include <Utilities/Colour.h>

#if USE_SFML
#include <SFML/Graphics/Color.hpp>

// Definitions of the SFML-specific members
Colour::operator sf::Color() const { return sf::Color(r, g, b, a); }

Colour::Colour(const sf::Color& c) : r(c.r), g(c.g), b(c.b), a(c.a) {}

sf::Color Colour::ToSFML() const { return sf::Color(r, g, b, a); }
#endif
