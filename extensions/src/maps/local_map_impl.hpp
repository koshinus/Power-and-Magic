#pragma once

#include <vector>

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

#include "../utils/world_constants.hpp"
#include "../utils/world_generator_impl.hpp"

namespace pwm
{

class LocalMapImpl: public godot::Node2D
{
    GDCLASS( LocalMapImpl, godot::Node2D )
public:
    LocalMapImpl();
    ~LocalMapImpl();
    static LocalMapImpl* create_from_packed_scene( godot::PackedScene* loc_map_scene,
                                                  const GlobalTypesMap& glob_tiles_vals,
                                                  godot::Vector2i grid_pos, godot::Vector2 orig_size,
                                                  bool show_grid );
    void init_by_params( int global_tile_type, const std::vector<int>& neighbours );
protected:
    static void _bind_methods();
private:
    int get_local_tile_type_by_neighbours( int big_tile_type, std::vector<int> neighbours );
    LOCAL_TILES get_tile_offset_by_coords( int x, int y );
    static std::vector<int> get_neighbours( const GlobalTypesMap& glob_tiles_vals, int i, int j );
};

}
