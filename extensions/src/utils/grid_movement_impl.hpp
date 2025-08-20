#pragma once

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/vector2i.hpp>

#include "../hero/hero_info_impl.hpp"
#include "world_generator_impl.hpp"

// @export var tile_size : Vector2i = Vector2i.ONE
namespace godot
{
class AStarGrid2D;
class TileData;
class TileMapLayer;
}

namespace pwm
{

// class GridMovementImpl: public godot::Node
// {
//     GDCLASS( GridMovementImpl, godot::Node )
// private:
// protected:
//     static void _bind_methods();
//     void _process( double p_delta ) override;
// public:
//     GridMovementImpl();
//     ~GridMovementImpl();
// };


class GridMovement
{
public:
    explicit GridMovement( godot::Vector2i tile_size );
    static godot::AStarGrid2D* create_astar( godot::TileMapLayer* tml, const GlobalTypesMap& glob_tiles_vals,
                             HeroInfo hero_info, godot::Vector2i tsize );
    static void reset_tiles_passability( godot::AStarGrid2D* astar_grid, godot::TileMapLayer* tml,
                                         const GlobalTypesMap& glob_tiles_vals, HeroInfo hero_info );
    static godot::TypedArray<godot::Vector2i> get_grid_path( godot::AStarGrid2D* astar_grid_2d, godot::Vector2i start_point, godot::Vector2i end_point );
    static godot::Vector2i calculate_grid_coords( godot::Vector2i coords, godot::Vector2i tsize );
    static godot::Vector2i calculate_grid( godot::Vector2i coords, godot::Vector2i tsize );

    godot::AStarGrid2D* create_astar( godot::TileMapLayer* tml, const GlobalTypesMap& glob_tiles_vals,
                                     HeroInfo hero_info );
    godot::Vector2i calculate_grid_coords( godot::Vector2i coords );
    godot::Vector2i calculate_grid( godot::Vector2i coords );
private:
    static bool is_passable( godot::TileData* tdata, int glob_tile_val, HeroInfo hero_info );
    static bool tile_set_source_is_scene_collection( godot::TileMapLayer* tml );

    godot::Vector2i m_tile_size;
};

}
