#pragma once

#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/color.hpp>

namespace pwm
{

namespace vec
{
const auto ZERO = godot::Vector2i( 0, 0 );
const auto MINUS_ONE = godot::Vector2i( -1, -1 );
const auto ONE = godot::Vector2i( 1, 1 );
}

namespace colors
{

const auto YELLOW = godot::Color::hex( 0xFFFF00FF );
const auto WHITE = godot::Color::hex( 0xFFFFFFFF );

}

}
