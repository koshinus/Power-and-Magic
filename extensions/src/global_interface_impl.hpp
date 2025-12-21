#pragma once

#include <optional>

#include <godot_cpp/classes/canvas_layer.hpp>
#include "hero/hero_info_impl.hpp"

namespace pwm
{

class GlobalInterfaceImpl: public godot::CanvasLayer
{
    GDCLASS( GlobalInterfaceImpl, godot::CanvasLayer )
private:
protected:
    static void _bind_methods();
public:
    GlobalInterfaceImpl();
    ~GlobalInterfaceImpl() override;
    void on_btn_change_view_pressed();
    void on_btn_magic_book_pressed();
    void show_hero_depending_parts( std::optional<HeroInfo> info );
    void _ready() override;
};

}
