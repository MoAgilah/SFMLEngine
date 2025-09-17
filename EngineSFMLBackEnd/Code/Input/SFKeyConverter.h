#pragma once

#include <Engine/Interface/Input/IKeyConverter.h>
#include <SFML/Window/Keyboard.hpp>

class SFKeyConverter : public IKeyConverter<sf::Keyboard::Key>
{
public:
    KeyCode Convert(sf::Keyboard::Key key) const override {
        switch (key) {
        case sf::Keyboard::Key::A: return KeyCode::A;
        case sf::Keyboard::Key::B: return KeyCode::B;
        case sf::Keyboard::Key::C: return KeyCode::C;
        case sf::Keyboard::Key::D: return KeyCode::D;
        case sf::Keyboard::Key::E: return KeyCode::E;
        case sf::Keyboard::Key::F: return KeyCode::F;
        case sf::Keyboard::Key::G: return KeyCode::G;
        case sf::Keyboard::Key::H: return KeyCode::H;
        case sf::Keyboard::Key::I: return KeyCode::I;
        case sf::Keyboard::Key::J: return KeyCode::J;
        case sf::Keyboard::Key::K: return KeyCode::K;
        case sf::Keyboard::Key::L: return KeyCode::L;
        case sf::Keyboard::Key::M: return KeyCode::M;
        case sf::Keyboard::Key::N: return KeyCode::N;
        case sf::Keyboard::Key::O: return KeyCode::O;
        case sf::Keyboard::Key::P: return KeyCode::P;
        case sf::Keyboard::Key::Q: return KeyCode::Q;
        case sf::Keyboard::Key::R: return KeyCode::R;
        case sf::Keyboard::Key::S: return KeyCode::S;
        case sf::Keyboard::Key::T: return KeyCode::T;
        case sf::Keyboard::Key::U: return KeyCode::U;
        case sf::Keyboard::Key::V: return KeyCode::V;
        case sf::Keyboard::Key::W: return KeyCode::W;
        case sf::Keyboard::Key::X: return KeyCode::X;
        case sf::Keyboard::Key::Y: return KeyCode::Y;
        case sf::Keyboard::Key::Z: return KeyCode::Z;

        case sf::Keyboard::Key::Num0: return KeyCode::Num0;
        case sf::Keyboard::Key::Num1: return KeyCode::Num1;
        case sf::Keyboard::Key::Num2: return KeyCode::Num2;
        case sf::Keyboard::Key::Num3: return KeyCode::Num3;
        case sf::Keyboard::Key::Num4: return KeyCode::Num4;
        case sf::Keyboard::Key::Num5: return KeyCode::Num5;
        case sf::Keyboard::Key::Num6: return KeyCode::Num6;
        case sf::Keyboard::Key::Num7: return KeyCode::Num7;
        case sf::Keyboard::Key::Num8: return KeyCode::Num8;
        case sf::Keyboard::Key::Num9: return KeyCode::Num9;

        case sf::Keyboard::Key::Escape: return KeyCode::Escape;
        case sf::Keyboard::Key::LControl: return KeyCode::LControl;
        case sf::Keyboard::Key::LShift: return KeyCode::LShift;
        case sf::Keyboard::Key::LAlt: return KeyCode::LAlt;
        case sf::Keyboard::Key::LSystem: return KeyCode::LSystem;
        case sf::Keyboard::Key::RControl: return KeyCode::RControl;
        case sf::Keyboard::Key::RShift: return KeyCode::RShift;
        case sf::Keyboard::Key::RAlt: return KeyCode::RAlt;
        case sf::Keyboard::Key::RSystem: return KeyCode::RSystem;
        case sf::Keyboard::Key::Menu: return KeyCode::Menu;

        case sf::Keyboard::Key::LBracket: return KeyCode::LBracket;
        case sf::Keyboard::Key::RBracket: return KeyCode::RBracket;
        case sf::Keyboard::Key::Semicolon: return KeyCode::Semicolon;
        case sf::Keyboard::Key::Comma: return KeyCode::Comma;
        case sf::Keyboard::Key::Period: return KeyCode::Period;
        case sf::Keyboard::Key::Apostrophe: return KeyCode::Apostrophe;
        case sf::Keyboard::Key::Slash: return KeyCode::Slash;
        case sf::Keyboard::Key::Backslash: return KeyCode::Backslash;
        case sf::Keyboard::Key::Grave: return KeyCode::Grave;
        case sf::Keyboard::Key::Equal: return KeyCode::Equal;
        case sf::Keyboard::Key::Hyphen: return KeyCode::Hyphen;

        case sf::Keyboard::Key::Space: return KeyCode::Space;
        case sf::Keyboard::Key::Enter: return KeyCode::Enter;
        case sf::Keyboard::Key::Backspace: return KeyCode::Backspace;
        case sf::Keyboard::Key::Tab: return KeyCode::Tab;
        case sf::Keyboard::Key::PageUp: return KeyCode::PageUp;
        case sf::Keyboard::Key::PageDown: return KeyCode::PageDown;
        case sf::Keyboard::Key::End: return KeyCode::End;
        case sf::Keyboard::Key::Home: return KeyCode::Home;
        case sf::Keyboard::Key::Insert: return KeyCode::Insert;
        case sf::Keyboard::Key::Delete: return KeyCode::Delete;

        case sf::Keyboard::Key::Add: return KeyCode::Add;
        case sf::Keyboard::Key::Subtract: return KeyCode::Subtract;
        case sf::Keyboard::Key::Multiply: return KeyCode::Multiply;
        case sf::Keyboard::Key::Divide: return KeyCode::Divide;

        case sf::Keyboard::Key::Left: return KeyCode::Left;
        case sf::Keyboard::Key::Right: return KeyCode::Right;
        case sf::Keyboard::Key::Up: return KeyCode::Up;
        case sf::Keyboard::Key::Down: return KeyCode::Down;

        case sf::Keyboard::Key::Numpad0: return KeyCode::Numpad0;
        case sf::Keyboard::Key::Numpad1: return KeyCode::Numpad1;
        case sf::Keyboard::Key::Numpad2: return KeyCode::Numpad2;
        case sf::Keyboard::Key::Numpad3: return KeyCode::Numpad3;
        case sf::Keyboard::Key::Numpad4: return KeyCode::Numpad4;
        case sf::Keyboard::Key::Numpad5: return KeyCode::Numpad5;
        case sf::Keyboard::Key::Numpad6: return KeyCode::Numpad6;
        case sf::Keyboard::Key::Numpad7: return KeyCode::Numpad7;
        case sf::Keyboard::Key::Numpad8: return KeyCode::Numpad8;
        case sf::Keyboard::Key::Numpad9: return KeyCode::Numpad9;

        case sf::Keyboard::Key::F1: return KeyCode::F1;
        case sf::Keyboard::Key::F2: return KeyCode::F2;
        case sf::Keyboard::Key::F3: return KeyCode::F3;
        case sf::Keyboard::Key::F4: return KeyCode::F4;
        case sf::Keyboard::Key::F5: return KeyCode::F5;
        case sf::Keyboard::Key::F6: return KeyCode::F6;
        case sf::Keyboard::Key::F7: return KeyCode::F7;
        case sf::Keyboard::Key::F8: return KeyCode::F8;
        case sf::Keyboard::Key::F9: return KeyCode::F9;
        case sf::Keyboard::Key::F10: return KeyCode::F10;
        case sf::Keyboard::Key::F11: return KeyCode::F11;
        case sf::Keyboard::Key::F12: return KeyCode::F12;
        case sf::Keyboard::Key::F13: return KeyCode::F13;
        case sf::Keyboard::Key::F14: return KeyCode::F14;
        case sf::Keyboard::Key::F15: return KeyCode::F15;

        case sf::Keyboard::Key::Pause: return KeyCode::Pause;

        default:
            return KeyCode::Unknown;
        }
    }
};