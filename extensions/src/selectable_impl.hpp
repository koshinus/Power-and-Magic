#pragma once

#include <godot_cpp/classes/control.hpp>

#include "utils/pwm_properties.hpp"

namespace pwm
{

class SelectableImpl: public godot::Control
{
    GDCLASS( SelectableImpl, godot::Control )
private:
    PwmProperty<godot::String> m_group_name;
    PwmProperty<bool> m_exclusive;

    bool m_is_selected;

    void make_exclusive();
protected:
    static void _bind_methods();
public:
    SelectableImpl();
    ~SelectableImpl();

    void on_button_pressed();
    void set_selected( bool selection_flag );

    godot::String get_group_name();
    void set_group_name( const godot::String val );

    bool get_exclusive();
    void set_exclusive( const bool val );
};

}
