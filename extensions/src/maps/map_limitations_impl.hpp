#pragma once

#include <godot_cpp/variant/vector2i.hpp>
#include <godot_cpp/classes/static_body2d.hpp>

#include "../utils/pwm_properties.hpp"

namespace godot {
class CollisionShape2D;
}
namespace pwm
{

class MapLimitationsImpl: public godot::StaticBody2D
{
    GDCLASS( MapLimitationsImpl, godot::StaticBody2D )
private:
    PwmProperty<godot::Vector2i> m_tile_size;
    PwmProperty<int> m_map_width;
    PwmProperty<int> m_map_height;
    void setup_limits( godot::CollisionShape2D* limit_side, godot::Vector2i limit_size, godot::Vector2i limit_pos );
protected:
    static void _bind_methods();
public:
    MapLimitationsImpl();
    ~MapLimitationsImpl();
    void _ready() override;
};

}
