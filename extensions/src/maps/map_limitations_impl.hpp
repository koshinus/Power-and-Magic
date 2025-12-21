#pragma once

#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/classes/static_body2d.hpp>

namespace godot {
class CollisionShape2D;
}
namespace pwm
{

class MapLimitationsImpl: public godot::StaticBody2D
{
    GDCLASS( MapLimitationsImpl, godot::StaticBody2D )
public:
    MapLimitationsImpl();
    ~MapLimitationsImpl() override;
    void _ready() override;

    godot::Vector2i get_map_size() const { return m_map_size; }
    void set_map_size( const godot::Vector2i val ) { m_map_size = val; }
    godot::Vector2i get_tile_size() const { return m_tile_size; }
    void set_tile_size( const godot::Vector2i val ) { m_tile_size = val; }

protected:
    static void _bind_methods();
private:
    godot::Vector2i m_tile_size;
    godot::Vector2i m_map_size;
    void setup_limits( godot::CollisionShape2D* limit_side, godot::Vector2i limit_size, godot::Vector2i limit_pos );
};

}
