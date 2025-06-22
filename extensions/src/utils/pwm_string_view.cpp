#include "pwm_string_view.hpp"

namespace pwm
{

// constexpr string_view::string_view( std::string_view view ) noexcept: m_view{ view } {}

// constexpr string_view::string_view( const char* cstr ) noexcept: m_view{ cstr } {}

constexpr std::string_view string_view::toStd() const
{
    return m_view;
}

string_view::operator godot::String() const
{
    return m_view.data();
}

string_view::operator godot::StringName() const
{
    return m_view.data();
}

}
