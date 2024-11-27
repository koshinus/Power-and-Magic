extends Node

class_name GLOBAL_MAP
enum TYPES
{
	DEEP_WATER = 0,
	WATER,
	SWAMP,
	GRASS,
	SNOW,
	FROZEN_LAVA,
	DIRT,
	SAND,
	ROUGH,
	WASTELAND,
	#TODO: add some special "magic" types of terrain
	MOUNTAINE,
	COUNT
};

const GLOBAL_TILE_SIZE_IN_PIXELS : int = 64;
const LOCAL_TILE_SIZE_IN_PIXELS : int = 32;
const GLOBAL_MAP_WIDTH : int = 40;
const GLOBAL_MAP_HEIGHT : int = 40;
