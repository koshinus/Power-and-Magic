#pragma once

#include <optional>

#include <godot_cpp/classes/node.hpp>

#include "hero/hero_info_impl.hpp"

namespace pwm
{

class GlobalLevelImpl: public godot::Node
{
    GDCLASS( GlobalLevelImpl, godot::Node )
private:
    godot::Vector2i m_grid_pos;
protected:
    static void _bind_methods();
public:
    void _ready() override;
    void on_hero_selected( std::optional<HeroInfo> info );
    void on_view_changed();
    GlobalLevelImpl();
    ~GlobalLevelImpl();
};

}
