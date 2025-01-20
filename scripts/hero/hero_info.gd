extends Node
class_name HeroProperties

enum Specialization
{
	WARRIOR,
	MAGICIAN,
	ECONOMIST
}

class HeroInfo:
	var specialization : Specialization = Specialization.WARRIOR
