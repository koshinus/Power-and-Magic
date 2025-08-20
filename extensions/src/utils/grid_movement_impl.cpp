#include <set>

#include <godot_cpp/classes/tile_set_scenes_collection_source.hpp>
#include <godot_cpp/classes/tile_data.hpp>
#include <godot_cpp/classes/a_star_grid2d.hpp>
#include <godot_cpp/classes/tile_map_layer.hpp>

#include "world_constants.hpp"
#include "grid_movement_impl.hpp"

namespace pwm
{

GridMovement::GridMovement( godot::Vector2i tile_size ) : m_tile_size( tile_size ) {}

bool GridMovement::is_passable( godot::TileData* tdata, int glob_tile_val, HeroInfo hero_info )
{
    if ( glob_tile_val != -1 )
    {
        auto typed_tile_val = static_cast<TYPES>( glob_tile_val );
        return std::set{ TYPES::DEEP_WATER, TYPES::WATER, TYPES::MOUNTAINE }.contains( typed_tile_val );
    }
    // TODO: add checks based on race and actual effects
    auto passable = tdata->get_custom_data( "terrain_t" );
    return passable.get_type() == godot::Variant::BOOL ? passable.booleanize() : true;
}

godot::AStarGrid2D* GridMovement::create_astar( godot::TileMapLayer* tml, const GlobalTypesMap& glob_tiles_vals,
                             HeroInfo hero_info, godot::Vector2i tsize )
{
    godot::Rect2i used_rect = tml->get_used_rect();
    auto astar_grid_2d = memnew( godot::AStarGrid2D );
    astar_grid_2d->set_region( used_rect );
    astar_grid_2d->set_cell_size( tsize );
    astar_grid_2d->set_diagonal_mode( godot::AStarGrid2D::DIAGONAL_MODE_ALWAYS );
    astar_grid_2d->update();
    reset_tiles_passability( astar_grid_2d, tml, glob_tiles_vals, hero_info );
    return astar_grid_2d;
}

bool GridMovement::tile_set_source_is_scene_collection( godot::TileMapLayer* tml )
{
    auto tset_ptr = tml->get_tile_set();
    for ( int i = 0; i < tset_ptr->get_source_count(); i++ )
    {
        auto scenes_source_ptr = dynamic_cast<godot::TileSetScenesCollectionSource*>( *tset_ptr->get_source( tset_ptr->get_source_id( i ) ) );
        if ( scenes_source_ptr )
        {
            return true;
        }
    }
    return false;
}

void GridMovement::reset_tiles_passability( godot::AStarGrid2D* astar_grid, godot::TileMapLayer* tml,
                                            const GlobalTypesMap& glob_tiles_vals, HeroInfo hero_info )
{
    godot::Rect2i used_rect = tml->get_used_rect();
    for ( int y = 0; y < used_rect.size.y; y++ )
    {
        for ( int x = 0; x < used_rect.size.x; x++ )
        {
            // godot::Variant;
            auto tile_pos = godot::Vector2i( x, y ) + used_rect.position;
            godot::TileData* tdata = tml->get_cell_tile_data( tile_pos );
            int glob_tile_val = -1;
            if ( !glob_tiles_vals.empty() )
            {
                auto it = glob_tiles_vals.find( godot::Vector2i( x, y ) );
                glob_tile_val = it != glob_tiles_vals.end() ? int( it->second ) : -1;
            }
            // TileData could be null if tile set source is not a TileSetAtlas,
            // so we need additional check
            if ( ( tdata == nullptr && !tile_set_source_is_scene_collection( tml ) ) ||
                                       !is_passable( tdata, glob_tile_val, hero_info ) )
            {
                astar_grid->set_point_solid( tile_pos );
            }
        }
    }
}

godot::TypedArray<godot::Vector2i> GridMovement::get_grid_path( godot::AStarGrid2D* astar_grid_2d, godot::Vector2i start_point, godot::Vector2i end_point )
{
    return astar_grid_2d ? astar_grid_2d->get_id_path( start_point, end_point ) : godot::Array();
}

godot::Vector2i GridMovement::calculate_grid_coords( godot::Vector2i coords, godot::Vector2i tsize )
{
    auto grid_coords = coords/tsize;
    return grid_coords*tsize + tsize/2;
}

godot::Vector2i GridMovement::calculate_grid( godot::Vector2i coords, godot::Vector2i tsize )
{
    return coords/tsize;
}

godot::AStarGrid2D* GridMovement::create_astar( godot::TileMapLayer* tml, const GlobalTypesMap& glob_tiles_vals, HeroInfo hero_info )
{
    return GridMovement::create_astar( tml, glob_tiles_vals, hero_info, m_tile_size );
}

godot::Vector2i GridMovement::calculate_grid_coords( godot::Vector2i coords )
{
    return GridMovement::calculate_grid_coords( coords, m_tile_size );
}

godot::Vector2i GridMovement::calculate_grid( godot::Vector2i coords )
{
    return GridMovement::calculate_grid( coords, m_tile_size );
}

}
