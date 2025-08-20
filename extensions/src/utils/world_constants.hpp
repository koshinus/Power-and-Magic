#pragma once

namespace pwm
{

enum class TYPES
{
    DEEP_WATER = 0,
    WATER,
    SNOW,
    TUNDRA,
    STEPPEN,
    GRASS,
    SAND,
    //TODO: add some special "magic" types of terrain
    MOUNTAINE,
    COUNT
};

enum class LOCAL_TILES
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

const int GLOBAL_TILE_SIZE_IN_PIXELS = 64;
const int GLOBAL_MAP_WIDTH = 30;
const int GLOBAL_MAP_HEIGHT = 30;

const int LOCAL_TILE_SIZE_IN_PIXELS = 32;
const int TILE_SIZE_IN_TILESET = 36;
const int LOCAL_MAP_WIDTH = 32;
const int LOCAL_MAP_HEIGHT = 32;

}
