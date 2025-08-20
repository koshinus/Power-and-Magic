#pragma once

#include <string_view>

#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/node_path.hpp>

namespace pwm
{

class string_view
{
public:
    constexpr explicit string_view( std::string_view view ) noexcept : m_view( view ){}
    constexpr explicit string_view( const char* cstr ) noexcept : m_view( cstr ){}
    operator godot::String() const;
    operator godot::StringName() const;
    operator godot::NodePath() const;
    constexpr std::string_view toStd() const { return m_view; }
protected:
private:
    std::string_view m_view;
};

}
