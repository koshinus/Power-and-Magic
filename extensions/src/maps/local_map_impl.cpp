#include <algorithm>
#include <random>
#include <chrono>
#include <limits>
#include <map>

#include <godot_cpp/classes/tile_map_layer.hpp>

#include "../grid_2d_node_impl.hpp"
#include "../utils/pwm_string_view.hpp"
#include "local_map_impl.hpp"
#include "../utils/pwm_funcs.hpp"

namespace pwm
{

constinit auto GRID_2D_NODE = pwm::string_view{ "Grid2DNode" };
constinit auto LOCAL_MAP_SURFACE = pwm::string_view{ "LocalMapSurface" };

LocalMapImpl::LocalMapImpl()
{
}

LocalMapImpl::~LocalMapImpl()
{
}

void LocalMapImpl::_bind_methods()
{
}

// Generating tile type for local adventure map:
// >=50% - should be of type that big_tile_type have
// other part depends on the big tile neighbours
// for example, if tile is grass, other 4 tiles are also grass
// but also there are 2 steppens and 2 deserts then:
// 50 + 6.25*4 - grass local tile chance
// 6.25*2 - steppen and desert chances for each
int LocalMapImpl::get_local_tile_type_by_neighbours( int big_tile_type, std::vector<int> neighbours )
{
    std::sort( neighbours.begin(), neighbours.end() );
    std::vector<int> tiles_arr( neighbours.size(), big_tile_type );
    auto it = std::find( neighbours.begin(), neighbours.end(), big_tile_type );
    for ( int i : tiles_arr ) neighbours.insert( it, i );

    std::mt19937 engine( std::chrono::high_resolution_clock::now().time_since_epoch().count() );
    std::uniform_int_distribution<int> dist( std::numeric_limits<int>::min(), std::numeric_limits<int>::max() );
    int randi = dist( engine );

    return neighbours[ randi % neighbours.size() ];
}

LOCAL_TILES LocalMapImpl::get_tile_offset_by_coords( int x, int y )
{
    int w = LOCAL_MAP_WIDTH;
    int h = LOCAL_MAP_HEIGHT;
    auto rule_dict = std::map<godot::Vector2i, LOCAL_TILES>{
        { godot::Vector2i(0, 0), LOCAL_TILES::TOP_LEFT },
        { godot::Vector2i(w-1, 0), LOCAL_TILES::TOP_RIGHT },
        { godot::Vector2i(0, h-1), LOCAL_TILES::BOTTOM_LEFT },
        { godot::Vector2i(w-1, h-1), LOCAL_TILES::BOTTOM_RIGHT }
    };
    if ( auto it = rule_dict.find( godot::Vector2i( x, y ) ); it != rule_dict.end() ) return it->second;
    if ( y == 0 ) return LOCAL_TILES::TOP;
    else if ( y == h-1 ) return LOCAL_TILES::BOTTOM;
    else if ( x == 0 ) return ( y % 2 == 1 ) ? LOCAL_TILES::LEFT_ODD : LOCAL_TILES::LEFT_EVEN;
    else if ( x == w-1 ) return ( y % 2 == 1 ) ? LOCAL_TILES::RIGHT_ODD : LOCAL_TILES::RIGHT_EVEN;
    else if ( y % 2 == 1 ) return LOCAL_TILES::MIDDLE_ODD;
    else return LOCAL_TILES::MIDDLE_EVEN;
}

void LocalMapImpl::init_by_params( int global_tile_type, const std::vector<int>& neighbours )
{
    for_each_2d( godot::Vector2i( LOCAL_MAP_WIDTH, LOCAL_MAP_HEIGHT ),
        [this, &neighbours, gtype = global_tile_type]( godot::Vector2i v ) {
            int tile_x_offset = static_cast<int>( get_tile_offset_by_coords( v.x, v.y ) );
            int tile_y_offset = get_local_tile_type_by_neighbours( gtype, neighbours );
            auto tileset_offset = godot::Vector2i( tile_x_offset, tile_y_offset );
            get_node<godot::TileMapLayer>( LOCAL_MAP_SURFACE )->set_cell( v, 0, tileset_offset );
        } );
}

std::vector<int> LocalMapImpl::get_neighbours( const GlobalTypesMap& glob_tiles_vals, int i, int j )
{
    // Assuming that TileMap is quadratic
    size_t rows = size_t( std::sqrt( glob_tiles_vals.size() ) );
    // size_t cols = glob_tiles_vals.front().size();
    // TODO: pass width somehow
    size_t cols = rows;
    // Define the possible relative positions for neighbours
    auto directions = std::vector{
        godot::Vector2i(-1,-1), godot::Vector2i(-1, 0), godot::Vector2i(-1,1), // Top-left   ,  Top   , Top-right
        godot::Vector2i( 0,-1),                         godot::Vector2i( 0,1), // Left       ,        , Right
        godot::Vector2i( 1,-1), godot::Vector2i( 1, 0), godot::Vector2i( 1,1)  // Bottom-left, Bottom , Bottom-right
    };
    std::vector<int> neighbours;
    // Check each direction for valid neighbours
    for ( auto& dir : directions )
    {
        int new_row = i + dir.x;
        int new_col = j + dir.y;
        // Check if the new position is within bounds
        if ( ( new_row >= 0 ) && ( new_row < rows ) && ( new_col >= 0 ) && ( new_col < cols ) )
        {
            auto it = glob_tiles_vals.find( godot::Vector2i( new_row, new_col ) );
            neighbours.push_back( int( it->second ) );
        }
    }
    return neighbours;
}

LocalMapImpl* LocalMapImpl::create_from_packed_scene( godot::PackedScene* loc_map_scene,
                                       const GlobalTypesMap& global_tiles_values,
                                       godot::Vector2i grid_pos, godot::Vector2 orig_size,
                                       bool show_grid )
{
    auto loc_map = static_cast<LocalMapImpl*>( loc_map_scene->instantiate() );
    if ( !loc_map ) return nullptr;
    int x = grid_pos.x;
    int y = grid_pos.y;
    auto it = global_tiles_values.find( godot::Vector2i( x, y ) );
    loc_map->init_by_params( int( it->second ), get_neighbours( global_tiles_values, x, y ) );
    int loc_w_px = LOCAL_MAP_WIDTH*LOCAL_TILE_SIZE_IN_PIXELS;
    int loc_h_px = LOCAL_MAP_HEIGHT*LOCAL_TILE_SIZE_IN_PIXELS;
    godot::Vector2 scale_vec = orig_size/godot::Vector2( loc_w_px, loc_h_px );
    loc_map->set_scale( scale_vec );
    loc_map->set_position( godot::Vector2i( x,y )*godot::Vector2i( orig_size ) );
    loc_map->get_node<Grid2dNodeImpl>( GRID_2D_NODE )->set_visible( show_grid );
    return loc_map;
}

}
