#pragma once

#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/control.hpp>

#include "utils/pwm_properties.hpp"

namespace pwm
{

class NumberedTextureImpl: public godot::Control
{
    GDCLASS( NumberedTextureImpl, godot::Control )
private:
    PwmProperty<godot::Texture2D> m_button_texture;
    PwmProperty<bool> m_hide_on_zero;
    PwmProperty<bool> m_button_is_active;

    void on_btn_pressed();
protected:
    static void _bind_methods();
public:
    NumberedTextureImpl();
    ~NumberedTextureImpl();
    void _ready() override;
    void set_amount( int new_amount );

    godot::Texture2D get_button_texture();
    bool get_btn_is_active();
    bool get_hide_on_zero();

    void set_button_texture( const godot::Texture2D );
    void set_btn_is_active( const bool val );
    void set_hide_on_zero( const bool val );
};

}
