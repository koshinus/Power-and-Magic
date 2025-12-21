#pragma once

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/variant/array.hpp>

#include "../utils/world_generator_impl.hpp"

namespace godot
{
class TileMapLayer;
class AStarGrid2D;
}

namespace pwm
{

class HeroSceneImpl: public godot::CharacterBody2D
{
    GDCLASS( HeroSceneImpl, godot::CharacterBody2D )
public:
    HeroSceneImpl();
    ~HeroSceneImpl() override;

    void _ready() override;
    void _physics_process( double delta ) override;
    void set_tilemap_layer( godot::TileMapLayer* tml, const GlobalTypesMap& global_tiles_vals );

    int get_start_pos() const { return m_start_pos; }
    void set_start_pos( const int _val ) { m_start_pos = _val; }
protected:
    static void _bind_methods();
private:
    int m_start_pos;
    bool m_is_selected;
    godot::Vector2i m_click_pos;
    // Path calculation can be different from hero to hero:
    // for example one hero uses "Fly" spell, while th other don't.
    // To avoid recalculating AStarGrid2D on each hero switch, we need
    // to store it hero, despite they share one TileMapLayer
    godot::AStarGrid2D* m_astar_grid_2d;
    godot::TypedArray<godot::Vector2i> m_astar_path;
    // For read purpose only and setup astar grid!!
    const godot::TileMapLayer* m_tml_ref;

    godot::Vector2 process_row( godot::Vector2 cur_pos );
    godot::Vector2 process_astar( godot::Vector2 cur_pos );
    void on_hero_selected( bool selection_flag );
};

}
