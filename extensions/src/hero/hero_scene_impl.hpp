#pragma once

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/variant/array.hpp>

#include "../utils/pwm_properties.hpp"
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
private:
    PwmProperty<int> m_start_pos;
    bool m_is_selected;

    godot::Vector2 process_row( godot::Vector2 cur_pos );
    godot::Vector2 process_astar( godot::Vector2 cur_pos );
    void on_hero_selected( bool selection_flag );
protected:
    static void _bind_methods();
public:
    HeroSceneImpl();
    ~HeroSceneImpl();

    void _ready() override;
    void _physics_process( double delta ) override;
    void set_tilemap_layer( godot::TileMapLayer* tml, const GlobalTypesMap& /*Array[Array[int]]*/ global_tiles_vals );

    int get_px_tile_size();
    void set_px_tile_size( const int _val );
};

}
