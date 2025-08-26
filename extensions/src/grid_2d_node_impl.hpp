#pragma once

#include <godot_cpp/classes/node2d.hpp>

namespace pwm
{

class Grid2dNodeImpl: public godot::Node2D
{
    GDCLASS( Grid2dNodeImpl, godot::Node2D )
public:
    Grid2dNodeImpl();
    ~Grid2dNodeImpl();

    void _ready() override;
    void _process( double p_delta ) override;
    void _draw() override;

    int get_map_width() const { return m_map_width; }
    void set_map_width( const int val ) { m_map_width = val; }
    int get_map_height() const { return m_map_height; }
    void set_map_height( const int val ) { m_map_height = val; }
    godot::Vector2i get_tile_size() const { return m_tile_size; }
    void set_tile_size( const godot::Vector2i val ) { m_tile_size = val; }
    godot::Color get_grid_color() const { return m_grid_color; }
    void set_grid_color( const godot::Color val ) { m_grid_color = val; }
protected:
    static void _bind_methods();
private:
    int m_map_width;
    int m_map_height;
    godot::Vector2i m_tile_size;
    godot::Color m_grid_color;
};

}
