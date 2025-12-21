#pragma once

#include <godot_cpp/classes/control.hpp>

namespace pwm
{

class SelectableImpl: public godot::Control
{
    GDCLASS( SelectableImpl, godot::Control )
public:
    SelectableImpl();
    ~SelectableImpl() override;

    void on_button_pressed();
    void set_selected( bool selection_flag );

    godot::String get_group_name() const { return m_group_name; }
    void set_group_name( const godot::String val ) { m_group_name = val; }

    bool get_exclusive() const { return m_exclusive; }
    void set_exclusive( const bool val ) { m_exclusive = val; }
protected:
    static void _bind_methods();
private:
    godot::String m_group_name;
    bool m_exclusive;
    bool m_is_selected;
    void make_exclusive();
};

}
