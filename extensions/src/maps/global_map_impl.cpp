#include <godot_cpp/classes/tile_map_layer.hpp>

#include "../utils/world_generator_impl.hpp"
#include "../utils/world_constants.hpp"
#include "../utils/pwm_bindings.hpp"
#include "../utils/pwm_constants.hpp"

#include "local_map_impl.hpp"

#include "global_map_impl.hpp"

namespace pwm
{

constinit auto GMAP_TILE_SIZE = pwm::string_view{ "px_tile_size" };
constinit auto GMAP_LAYER_WIDTH = pwm::string_view{ "layer_width" };
constinit auto GMAP_LAYER_HEIGHT = pwm::string_view{ "layer_height" };

constinit auto GLOBAL_MAP_SURFACE = pwm::string_view{ "GlobalMapSurface" };

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
    using bh = BindHelper<GlobalMapImpl>;
    bh::property<int>( GMAP_TILE_SIZE, &GlobalMapImpl::get_px_tile_size,
                                       &GlobalMapImpl::set_px_tile_size );
    bh ::property<int>( GMAP_LAYER_WIDTH, &GlobalMapImpl::get_layer_width,
                                          &GlobalMapImpl::set_layer_width );
    bh ::property<int>( GMAP_LAYER_HEIGHT, &GlobalMapImpl::get_layer_height,
                                           &GlobalMapImpl::set_layer_height );
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
    for ( int y = 0; y < m_layer_height; y++ )
    {
        for ( int x = 0; x < m_layer_width; x++ )
        {
            auto grid_pos = godot::Vector2i( x, y );
            int scene_tile_id = loc_scenes.local_maps[ grid_pos ];
            global_surface->set_cell( grid_pos, src_id, VEC_ZERO, scene_tile_id );
            auto loc_map_scene = dynamic_cast<godot::TileSetScenesCollectionSource*>(
                                    *global_surface->get_tile_set()->get_source( src_id ) )
                                                  ->get_scene_tile_scene( scene_tile_id );
            add_child( LocalMapImpl::create_from_packed_scene( loc_map_scene.ptr(),
                            world_info.global_tiles_values, grid_pos,
                            godot::Vector2( m_px_tile_size, m_px_tile_size ), false ) );
        }
    }
    godot::print_line( "Scenes total: ", get_child_count() );
}

}
