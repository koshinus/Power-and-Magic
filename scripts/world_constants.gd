extends Node

class_name GLOBAL_MAP

enum TYPES
{
	DEEP_WATER = 0,
	WATER,
	SNOW,
	TUNDRA,
	STEPPEN,
	GRASS,
	SAND,
	#TODO: add some special "magic" types of terrain
	MOUNTAINE,
	COUNT
};

enum LOCAL_TILES
{
	MIDDLE_EVEN = 0,
	MIDDLE_ODD = 1,
	BOTTOM_LEFT = 2,
	BOTTOM = 3,
	BOTTOM_RIGHT = 4,
	TOP_LEFT = 5,
	TOP = 6,
	TOP_RIGHT = 7,
	LEFT_EVEN = 8,
	RIGHT_EVEN = 9,
	LEFT_ODD = 10,
	RIGHT_ODD = 11,
};

const GLOBAL_TILE_SIZE_IN_PIXELS : int = 64;
const GLOBAL_MAP_WIDTH : int = 30;
const GLOBAL_MAP_HEIGHT : int = 30;

const LOCAL_TILE_SIZE_IN_PIXELS : int = 32;
const TILE_SIZE_IN_TILESET : int = 36;
const LOCAL_MAP_WIDTH : int = 32;
const LOCAL_MAP_HEIGHT : int = 32;
