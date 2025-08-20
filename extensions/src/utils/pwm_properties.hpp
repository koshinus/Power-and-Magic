#pragma once

#include <format>
#include <concepts>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/godot.hpp>

#include "pwm_string_view.hpp"

namespace pwm
{

template<typename NodeT>
concept GodotNode = std::derived_from<NodeT, godot::Node>;

template<typename RetT, typename T>
using SetPtrType = void(T::*)(const RetT);

template<typename RetT, typename T>
using GetPtrType = RetT(T::*)();

template<typename T, typename ParentT>
concept PropertySetMethod =
    // std::invocable<void(const T)> &&
    // std::is_member_function_pointer_v<ParentT>;
    std::is_member_function_pointer_v<SetPtrType<T, ParentT>>;


template<typename T, typename ParentT>
concept PropertyGetMethod =
    // std::invocable<T(void)> &&
    // std::is_member_function_pointer_v<ParentT>;
    std::is_member_function_pointer_v<GetPtrType<T, ParentT>>;

// template<typename T, typename ParentT>
// concept ParamGetMethod = requires( ParentT obj )
// {
//     { ParentT::*() } -> int
// };

//Change to any type instead of GodotNode?
// template<GodotNode NodeT>
// concept f = requires(NodeT);

template<typename T>
constexpr godot::Variant::Type get_godot_variant_t()
{
    if constexpr ( std::is_same_v<T, int> )
    {
        return godot::Variant::INT;
    }
    if constexpr ( std::is_same_v<T, godot::Vector2i> )
    {
        return godot::Variant::VECTOR2I;
    }
    if constexpr ( std::is_same_v<T, godot::Color> )
    {
        return godot::Variant::COLOR;
    }
    return godot::Variant::NIL;
}

template<typename T>
struct PwmProperty
{
    // explicit PwmProperty( const char* prop_name ): val{}, name{ prop_name }{}
    // explicit PwmProperty( pwm::string_view prop_name ): val{}, name{ prop_name }{}
    explicit PwmProperty( T _val ): val{ _val }{}
    //template<GodotNode ParentT>
    // godot::MethodBind* bind( GetFn* get_fn, SetFn* set_fn, godot::Variant::Type var_t )
    // void bind( ParamGetMethod<ParentT> auto get_fn,
    //            ParamSetMethod<ParentT> auto set_fn,
    //            godot::Variant::Type var_t )
    // {
    //     PwmProperty::bind( name, get_fn, set_fn, var_t );
    // }
    template<GodotNode ParentT, PropertyGetMethod<ParentT> GetFnT, PropertySetMethod<ParentT> SetFnT>
    static void bind( pwm::string_view name, GetFnT get_fn, SetFnT set_fn )
    {
        auto get = std::vformat( "get_{}", std::make_format_args( name.toStd() ) );
        auto set = std::vformat( "set_{}", std::make_format_args( name.toStd() ) );
        auto _var_name = std::vformat( "_{}", std::make_format_args( name.toStd() ) );
        godot::ClassDB::bind_method( godot::D_METHOD( get.c_str() ), get_fn );
        godot::ClassDB::bind_method( godot::D_METHOD( set.c_str(), _var_name.c_str() ), set_fn );
        godot::ClassDB::add_property( ParentT::get_class_static(),
                godot::PropertyInfo( get_godot_variant_t<T>(), name ), set.c_str(), get.c_str() );
    }

    T val;
};

// template<GodotNode ParentT>
// class Node: public ParentT
// {
// #define fff
// protected:
//     template<typename Fn>
//     void bind_method( pwm::string_view mname, Fn* fn )
//     {
//         godot::ClassDB::bind_method( godot::D_METHOD( mname ), fn );
//     }

//     template<typename T>
//     void bind_property( T* prop )
//     {
//         // godot::ClassDB::bind_method(godot::D_METHOD("get_amplitude"), &GDExample::get_amplitude);
//         // godot::ClassDB::bind_method(godot::D_METHOD("set_amplitude", "p_amplitude"), &GDExample::set_amplitude);
//         // ADD_PROPERTY(godot::PropertyInfo(godot::Variant::FLOAT, "amplitude"), "set_amplitude", "get_amplitude");
//     }
// #undef fff
// };

struct BindHelper
{
    template<typename Fn>
    static godot::MethodBind* method( pwm::string_view mname, Fn* fn )
    {
        return godot::ClassDB::bind_method( godot::D_METHOD( mname ), fn );
    }

// #define PROP_BIND_MACRO( class_name, prop_name, set_name, get_name, var_name, var_type ) \
//     godot::ClassDB::bind_method( godot::D_METHOD( get_name ), &##class_name::get_##var_name ); \
//     godot::ClassDB::bind_method( godot::D_METHOD( set_name, _##var_name ), &##class_name::set_##var_name ); \
//     ADD_PROPERTY( godot::PropertyInfo( var_type, prop_name ), set_name, get_name );
// #undef PROP_BIND_MACRO
#define PROP_BIND_MACRO( class_name, prop_name, var_name, var_type ) \
    auto get_name = std::vformat( "get_{}", std::make_format_args( prop_name ) ); \
    auto set_name = std::vformat( "set_{}", std::make_format_args( prop_name ) ); \
    auto _var_name = std::vformat( "_{}", std::make_format_args( prop_name ) ); \
    godot::ClassDB::bind_method( godot::D_METHOD( get_name.c_str() ), &class_name::get_##var_name ); \
    godot::ClassDB::bind_method( godot::D_METHOD( set_name.c_str(), _var_name.c_str() ), &class_name::set_##var_name ); \
    ADD_PROPERTY( godot::PropertyInfo( var_type, prop_name ), set_name.c_str(), get_name.c_str() );
// #undef PROP_BIND_MACRO
};

}
