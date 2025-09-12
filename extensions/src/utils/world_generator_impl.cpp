#include <random>
#include <godot_cpp/classes/fast_noise_lite.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include "pwm_string_view.hpp"
#include "world_generator_impl.hpp"

namespace pwm
{

constinit auto LOCAL_MAP_SCENE_PATH = pwm::string_view{ "res://scenes/maps/local_map.tscn" };

double WorldGenerator::normalize( double noise_val )
{
    return ( noise_val + 0.7 ) * static_cast<int>( TYPES::COUNT );
}

TYPES WorldGenerator::get_tile_type_from_noise( double noise_val )
{
    auto is_between = []( double val, TYPES l, TYPES r ) { return val >= double( l ) && val < double( r ); };
    //min_noise = minf( min_noise, noise_val )
    //max_noise = maxf( max_noise, noise_val )
    noise_val = normalize( noise_val );
    if ( noise_val < double( TYPES::WATER ) )
        return TYPES::DEEP_WATER;
    else if ( is_between( noise_val, TYPES::WATER, TYPES::SNOW ) )
        return TYPES::WATER;
    else if ( is_between( noise_val, TYPES::SNOW, TYPES::TUNDRA ) )
        return TYPES::SNOW;
    else if ( is_between( noise_val, TYPES::SNOW, TYPES::STEPPEN ) )
        return TYPES::TUNDRA;
    else if ( is_between( noise_val, TYPES::STEPPEN, TYPES::GRASS ) )
        return TYPES::STEPPEN;
    else if ( is_between( noise_val, TYPES::GRASS, TYPES::SAND ) )
        return TYPES::GRASS;
    else if ( is_between( noise_val, TYPES::SAND, TYPES::MOUNTAINE ) )
        return TYPES::SAND;
    else
        return TYPES::MOUNTAINE;
}

godot::FastNoiseLite* WorldGenerator::get_prepared_noise()
{
    auto noise = memnew( godot::FastNoiseLite );
    noise->set_seed( std::random_device{}() );
    noise->set_noise_type( godot::FastNoiseLite::TYPE_SIMPLEX );
    noise->set_frequency( 0.01 );
    noise->set_fractal_lacunarity( 2 );
    noise->set_fractal_gain( 0.5 );
    noise->set_fractal_type( godot::FastNoiseLite::FRACTAL_FBM );
    return noise;
}

GlobalTypesMap WorldGenerator::generate_global_tiles_types( godot::FastNoiseLite* noise )
{
    auto tiles_types = std::unordered_map<godot::Vector2i, TYPES>{};
    for ( int y = 0; y < GLOBAL_MAP_WIDTH; y++ )
    {
        for ( int x = 0; x < GLOBAL_MAP_HEIGHT; x++ )
        {
            tiles_types.insert( { godot::Vector2i( x, y ),
                WorldGenerator::get_tile_type_from_noise( noise->get_noise_2d( x, y ) ) } );
        }
    }
    return tiles_types;
}

ScenesInfo WorldGenerator::generate_local_maps( const GlobalTypesMap& global_tiles_vals )
{
    auto tset_source = memnew( godot::TileSetScenesCollectionSource );
    ScenesInfo loc_scenes_info;
    auto loader = godot::ResourceLoader::get_singleton();
    for ( int y = 0; y < GLOBAL_MAP_WIDTH; y++ )
    {
        for ( int x = 0; x < GLOBAL_MAP_HEIGHT; x++ )
        {
            auto loc_map_scene = loader->load( LOCAL_MAP_SCENE_PATH );
            loc_scenes_info.local_maps.insert( { godot::Vector2i( x, y ),
                                 tset_source->create_scene_tile( loc_map_scene ) } );
        }
    }
    loc_scenes_info.global_tset_source = tset_source;
    return loc_scenes_info;
}

WorldInfo WorldGenerator::generate()
{
    auto noise = WorldGenerator::get_prepared_noise();
    auto global_tiles_vals = WorldGenerator::generate_global_tiles_types( noise );
    //print( "Dict:", winfo.loc_scenes_info.local_maps );
    memfree( noise );
    return WorldInfo{ global_tiles_vals, WorldGenerator::generate_local_maps( global_tiles_vals ) };
}

}
