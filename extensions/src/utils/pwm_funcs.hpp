#pragma once

#include <concepts>

#include <godot_cpp/variant/vector2i.hpp>

template<typename ContainerT, typename FuncT>
requires requires ( ContainerT c, FuncT f, godot::Vector2i v )
{
    { c.at( v ) };
    { std::invocable<FuncT, godot::Vector2i, std::remove_cvref_t<decltype( c.at( v ) )>> };
}
void for_each_2d( const ContainerT& container, godot::Vector2i border, FuncT func )
{
    for ( int y = 0; y < border.y; y++ )
    {
        for ( int x = 0; x < border.x; x++ )
        {
            // "maps" can potentially modify container with "operator[]"
            // which can't be used for "const" containers, so use "at" instead
            func( godot::Vector2i( x, y ), container.at( godot::Vector2i( x, y ) ) );
        }
    }
}

template<typename ContainerT, typename FuncT>
requires requires ( ContainerT c, FuncT f, godot::Vector2i v )
{
    { c.operator[]( v.x ) };
    { c[ v.x ].operator[]( v.y ) };
    { std::invocable<FuncT, godot::Vector2i, std::remove_cvref_t<decltype( c[v.x][v.y] )>> };
}
void for_each_2d( const ContainerT& container, godot::Vector2i border, FuncT func )
{
    for ( int y = 0; y < border.y; y++ )
    {
        for ( int x = 0; x < border.x; x++ )
        {
            func( godot::Vector2i( x, y ), container[ x ][ y ] );
        }
    }
}

template<typename FuncT>
requires requires ( FuncT f, godot::Vector2i v )
{
    { std::invocable<FuncT, godot::Vector2i> };
}
void for_each_2d( godot::Vector2i border, FuncT func )
{
    for ( int y = 0; y < border.y; y++ )
    {
        for ( int x = 0; x < border.x; x++ )
        {
            func( godot::Vector2i( x, y ) );
        }
    }
}

