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

    godot::Vector2i get_grid_size() const { return m_grid_size; }
    void set_grid_size( const godot::Vector2i val ) { m_grid_size = val; }
    godot::Vector2i get_grid_tile_size() const { return m_grid_tile_size; }
    void set_grid_tile_size( const godot::Vector2i val ) { m_grid_tile_size = val; }
    godot::Color get_grid_color() const { return m_grid_color; }
    void set_grid_color( const godot::Color val ) { m_grid_color = val; }
protected:
    static void _bind_methods();
private:
    godot::Vector2i m_grid_size;
    godot::Vector2i m_grid_tile_size;
    godot::Color m_grid_color;
};

}
