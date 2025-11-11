#include <godot_cpp/classes/tile_map_layer.hpp>

#include "../utils/world_generator_impl.hpp"
#include "../utils/world_constants.hpp"
#include "../utils/pwm_bindings.hpp"
#include "../utils/pwm_constants.hpp"
#include "../utils/pwm_funcs.hpp"

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
    bh::property<int>( GMAP_LAYER_WIDTH, &GlobalMapImpl::get_layer_width,
                                          &GlobalMapImpl::set_layer_width );
    bh::property<int>( GMAP_LAYER_HEIGHT, &GlobalMapImpl::get_layer_height,
                                           &GlobalMapImpl::set_layer_height );
}

godot::TileMapLayer* GlobalMapImpl::get_surface()
{
    return get_node<godot::TileMapLayer>( GLOBAL_MAP_SURFACE );
}

void GlobalMapImpl::set_based_on_generated( const WorldInfo& world_info )
{
    auto global_surface = get_node<godot::TileMapLayer>( GLOBAL_MAP_SURFACE );
    int32_t src_id = global_surface->get_tile_set()->add_source( world_info.loc_scenes_info.global_tset_source );
    for_each_2d( world_info.loc_scenes_info.local_maps, godot::Vector2i( m_layer_width, m_layer_height ),
        [this, &gtiles = world_info.global_tiles_values, surf = global_surface, src_id]( godot::Vector2i grid_pos, int scene_tile_id ) {
        surf->set_cell( grid_pos, src_id, VEC_ZERO, scene_tile_id );
        auto loc_map_scene = static_cast<godot::TileSetScenesCollectionSource*>(
                *surf->get_tile_set()->get_source( src_id ) )->get_scene_tile_scene( scene_tile_id );
        add_child( LocalMapImpl::create_from_packed_scene( loc_map_scene.ptr(), gtiles, grid_pos,
                                                           godot::Vector2( m_px_tile_size, m_px_tile_size ), false ) );
    } );
    godot::print_line( "Scenes total: ", get_child_count() );
}

}
