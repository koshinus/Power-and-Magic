extends Node
class_name HeroProperties

enum Specialization
{
    WARRIOR,
    MAGICIAN,
    ECONOMIST
}

class MovementEffects:
    pass

class RaceEffects:
    pass

class CombatEffects:
    pass

class HeroEffects:
    var move : MovementEffects
    var race : RaceEffects
    var combat : CombatEffects

class HeroInfo:
    var grid_pos : Vector2i
    var effects : HeroEffects
    var specialization : Specialization = Specialization.WARRIOR
