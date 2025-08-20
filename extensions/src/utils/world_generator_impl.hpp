#pragma once

#include <unordered_map>

#include <godot_cpp/classes/tile_set_scenes_collection_source.hpp>
#include "world_constants.hpp"

namespace godot
{
class FastNoiseLite;
}

namespace std
{

template<>
struct hash<godot::Vector2i>
{
    size_t operator()( const godot::Vector2i& vec2i ) const
    {
        return std::hash<int32_t>{}( vec2i.x ) ^ std::hash<int32_t>{}( vec2i.y );
    }
};

}

namespace pwm
{

using GlobalTypesMap = std::unordered_map<godot::Vector2i, TYPES>;

struct ScenesInfo
{
    godot::TileSetScenesCollectionSource* global_tset_source;
    std::unordered_map<godot::Vector2i, int> local_maps; // Maps (x, y) -> tile_id for global_tset_source
};

struct WorldInfo
{
    GlobalTypesMap global_tiles_values; // Array[Array[int]] actually
    ScenesInfo loc_scenes_info;
};

class WorldGenerator
{
public:
    // WorldGenerator() = default;
    // ~WorldGenerator();
    WorldGenerator( const WorldGenerator& ) = delete;
    WorldGenerator& operator=( const WorldGenerator& ) = delete;
    static WorldInfo generate();
protected:
private:
    static double normalize( double noise_val );
    static TYPES get_tile_type_from_noise( double noise_val );
    static godot::FastNoiseLite* get_prepared_noise();
    static GlobalTypesMap generate_global_tiles_types( godot::FastNoiseLite* noise );
    static ScenesInfo generate_local_maps( const GlobalTypesMap& global_tiles_vals );
};

}
