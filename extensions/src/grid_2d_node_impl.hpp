#pragma once

#include <godot_cpp/classes/node2d.hpp>

#include "utils/pwm_properties.hpp"

namespace pwm
{

class Grid2dNodeImpl: public godot::Node2D
{
    GDCLASS( Grid2dNodeImpl, godot::Node2D )
private:
    PwmProperty<int> m_map_width;
    PwmProperty<int> m_map_height;
    PwmProperty<godot::Vector2i> m_tile_size;
    PwmProperty<godot::Color> m_grid_color;
protected:
    static void _bind_methods();
public:
    Grid2dNodeImpl();
    ~Grid2dNodeImpl();

    void _ready() override;
    void _process( double p_delta ) override;
    void _draw() override;

    int get_map_width();
    int get_map_height();
    godot::Vector2i get_tile_size();
    godot::Color get_grid_color();

    void set_map_width( const int val );
    void set_map_height( const int val );
    void set_tile_size( const godot::Vector2i val );
    void set_grid_color( const godot::Color val );
};

}
