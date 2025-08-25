#pragma once

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/variant/array.hpp>

#include "../utils/world_generator_impl.hpp"

namespace godot
{
class TileMapLayer;
}

namespace pwm
{

class HeroSceneImpl: public godot::CharacterBody2D
{
    GDCLASS( HeroSceneImpl, godot::CharacterBody2D )
public:
    HeroSceneImpl();
    ~HeroSceneImpl();

    void _ready() override;
    void _physics_process( double delta ) override;
    void set_tilemap_layer( godot::TileMapLayer* tml, const GlobalTypesMap& global_tiles_vals );

    int get_px_tile_size() { return m_start_pos; }
    void set_px_tile_size( const int _val ) { m_start_pos = _val; }
protected:
    static void _bind_methods();
private:
    int m_start_pos;
    bool m_is_selected;

    godot::Vector2 process_row( godot::Vector2 cur_pos );
    godot::Vector2 process_astar( godot::Vector2 cur_pos );
    void on_hero_selected( bool selection_flag );
};

}
