#include <godot_cpp/classes/tile_map_layer.hpp>

#include "../utils/world_generator_impl.hpp"
#include "../utils/world_constants.hpp"
#include "local_map_impl.hpp"

#include "global_map_impl.hpp"

namespace pwm
{

constexpr auto PX_TILE_SIZE = pwm::string_view{ "px_tile_size" };
constexpr auto LAYER_WIDTH = pwm::string_view{ "layer_width" };
constexpr auto LAYER_HEIGHT = pwm::string_view{ "layer_height" };

constexpr auto GLOBAL_MAP_SURFACE = pwm::string_view{ "GlobalMapSurface" };

GlobalMapImpl::GlobalMapImpl()
    : m_px_tile_size( GLOBAL_TILE_SIZE_IN_PIXELS )
    , m_layer_width( GLOBAL_MAP_WIDTH )
    , m_layer_height( GLOBAL_MAP_HEIGHT )
{
}

GlobalMapImpl::~GlobalMapImpl()
{
}

void GlobalMapImpl::_bind_methods()
{
    PwmProperty<int>::bind<GlobalMapImpl>( PX_TILE_SIZE,
                                          &GlobalMapImpl::get_px_tile_size,
                                          &GlobalMapImpl::set_px_tile_size );
    PwmProperty<int>::bind<GlobalMapImpl>( LAYER_WIDTH,
                                          &GlobalMapImpl::get_layer_width,
                                          &GlobalMapImpl::set_layer_width );
    PwmProperty<int>::bind<GlobalMapImpl>( LAYER_HEIGHT,
                                          &GlobalMapImpl::get_layer_height,
                                          &GlobalMapImpl::set_layer_height );
}

void GlobalMapImpl::set_px_tile_size( const int val )
{
    m_px_tile_size.val = val;
}

void GlobalMapImpl::set_layer_width( const int val )
{
    m_layer_width.val = val;
}

void GlobalMapImpl::set_layer_height( const int val )
{
    m_layer_height.val = val;
}

int GlobalMapImpl::get_px_tile_size()
{
    return m_px_tile_size.val;
}

int GlobalMapImpl::get_layer_width()
{
    return m_layer_width.val;
}

int GlobalMapImpl::get_layer_height()
{
    return m_layer_height.val;
}

godot::TileMapLayer* GlobalMapImpl::get_surface()
{
    return get_node<godot::TileMapLayer>( GLOBAL_MAP_SURFACE );
}

void GlobalMapImpl::set_based_on_generated( const WorldInfo& world_info )
{
    auto loc_scenes = world_info.loc_scenes_info;
    auto global_surface = get_node<godot::TileMapLayer>( GLOBAL_MAP_SURFACE );
    auto src_id = global_surface->get_tile_set()->add_source( loc_scenes.global_tset_source );
    for ( int y = 0; y < m_layer_height.val; y++ )
    {
        for ( int x = 0; x < m_layer_width.val; x++ )
        {
            auto grid_pos = godot::Vector2i( x, y );
            int scene_tile_id = loc_scenes.local_maps[ grid_pos ];
            global_surface->set_cell( grid_pos, src_id, godot::Vector2i( 0, 0 ), scene_tile_id );
            auto loc_map_scene = dynamic_cast<godot::TileSetScenesCollectionSource*>(
                                    *global_surface->get_tile_set()->get_source( src_id ) )
                                                  ->get_scene_tile_scene( scene_tile_id );
            add_child( LocalMapImpl::create_from_packed_scene( loc_map_scene.ptr(),
                            world_info.global_tiles_values, grid_pos,
                            godot::Vector2( m_px_tile_size.val, m_px_tile_size.val ), false ) );
        }
    }
    godot::print_line( "Scenes total: ", get_child_count() );
}
// func set_based_on_generated( world_info : Genarators.WorldInfo ); -> void:
//     var loc_scenes = world_info.loc_scenes_info
//     var src_id = $GlobalMapSurface.tile_set.add_source( loc_scenes.global_tset_source )
//     for y in range( layer_height ):
//         for x in range( layer_width ):
//             var grid_pos : Vector2i = Vector2i( x, y )
//             var scene_tile_id: int = loc_scenes.local_maps[ grid_pos ]
//             $GlobalMapSurface.set_cell( grid_pos, src_id, Vector2i.ZERO, scene_tile_id )
//             var loc_map_scene: PackedScene = $GlobalMapSurface.tile_set\
//                                                 .get_source( src_id )\
//                                                 .get_scene_tile_scene( scene_tile_id )
//             add_child( LocalMap.create_from_packed_scene( loc_map_scene,
//                             world_info.global_tiles_values, grid_pos,
//                             Vector2( px_tile_size, px_tile_size ), false ) )
//     print("Scenes total: ", get_child_count())

}
