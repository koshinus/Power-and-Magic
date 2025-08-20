#pragma once

#include <godot_cpp/variant/vector2i.hpp>

namespace pwm
{

enum class Specialization
{
    WARRIOR,
    MAGICIAN,
    ECONOMIST
};

struct MovementEffects
{
};

struct RaceEffects
{
};

struct CombatEffects
{
};

struct HeroEffects
{
    MovementEffects move;
    RaceEffects race;
    CombatEffects combat;
};

struct HeroInfo
{
    godot::Vector2i grid_pos;
    HeroEffects effects;
    Specialization specialization = Specialization::WARRIOR;
};

}
