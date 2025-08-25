#pragma once

#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/control.hpp>

#include "utils/pwm_properties.hpp"

namespace pwm
{

class NumberedTextureImpl: public godot::Control
{
    GDCLASS( NumberedTextureImpl, godot::Control )
public:
    NumberedTextureImpl();
    ~NumberedTextureImpl();
    void _ready() override;
    void set_amount( int new_amount );

    godot::Texture2D get_button_texture() { return m_button_texture; }
    void set_button_texture( const godot::Texture2D val ) { /*TODO*/}
    bool get_btn_is_active() { return m_button_is_active; }
    void set_btn_is_active( const bool val ) { m_button_is_active = val; }
    bool get_hide_on_zero() { return m_hide_on_zero; }
    void set_hide_on_zero( const bool val ) { m_hide_on_zero = val; }
protected:
    static void _bind_methods();
private:
    godot::Texture2D m_button_texture;
    bool m_hide_on_zero;
    bool m_button_is_active;

    void on_btn_pressed();
};

}
