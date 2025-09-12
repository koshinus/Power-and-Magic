#include "pwm_string_view.hpp"

namespace pwm
{

string_view::operator godot::String() const
{
    return m_view.data();
}

string_view::operator godot::StringName() const
{
    return m_view.data();
}

string_view::operator godot::NodePath() const
{
    return m_view.data();
}

}
