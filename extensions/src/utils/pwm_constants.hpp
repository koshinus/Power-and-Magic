#pragma once

#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/variant/string.hpp>

namespace pwm
{

const auto VEC_ZERO = godot::Vector2i( 0, 0 );
const auto VEC_MINUS_ONE = godot::Vector2i( -1, -1 );

namespace colors
{

const auto YELLOW = godot::Color::named( godot::String( "YELLOW" ) );
const auto WHITE = godot::Color::named( godot::String( "WHITE" ) );

}

}
