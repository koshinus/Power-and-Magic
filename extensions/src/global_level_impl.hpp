#pragma once

#include <optional>

#include <godot_cpp/classes/node.hpp>

#include "hero/hero_info_impl.hpp"
#include "utils/pwm_object_wrapper.hpp"

namespace pwm
{

class GlobalLevelImpl: public godot::Node
{
    GDCLASS( GlobalLevelImpl, godot::Node )
public:
    void _ready() override;
    void on_hero_selected( ObjectWrapper<std::optional<HeroInfo>>* info );
    void on_view_changed();
    GlobalLevelImpl();
    ~GlobalLevelImpl() override;
protected:
    static void _bind_methods();
private:
    godot::Vector2i m_grid_pos;
};

}
