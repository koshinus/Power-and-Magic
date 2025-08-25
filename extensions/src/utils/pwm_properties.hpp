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
using GetPtrType = RetT(T::*)() const;

template<typename T, typename RetT, typename... Args>
using MemFnPtr = RetT(T::*)(Args...);

template<typename T, typename ParentT>
concept PropertySetMethod = std::is_member_function_pointer_v<SetPtrType<T, ParentT>>;

template<typename T, typename ParentT>
concept PropertyGetMethod = std::is_member_function_pointer_v<GetPtrType<T, ParentT>>;

template<typename T, typename RetT, typename... Args>
concept PropertyMethod = std::is_member_function_pointer_v<MemFnPtr<T, RetT, Args>...>;

template<typename T>
constexpr godot::Variant::Type get_godot_variant_t()
{
    if constexpr ( std::is_same_v<T, double> || std::is_same_v<T, float> )
    {
        return godot::Variant::FLOAT;
    }
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
struct TypedProperty
{
    explicit TypedProperty( pwm::string_view prop_name ) : m_prop_name{ prop_name } {}
    godot::PropertyInfo toPropInfo() { return godot::PropertyInfo{ get_godot_variant_t<T>(), m_prop_name }; }
    pwm::string_view m_prop_name;
};

struct BindHelper
{
    template<GodotNode ParentT, PropertyMethod<ParentT> MethodT, typename... Args>
    static godot::MethodBind* method( pwm::string_view mname, MethodT fn, Args... args )
    {
        return godot::ClassDB::bind_method( godot::D_METHOD( mname ), fn, std::forward( args )... );
    }

    template<GodotNode ParentT, PropertyGetMethod<ParentT> GetFnT, PropertySetMethod<ParentT> SetFnT>
    static void property( pwm::string_view name, GetFnT get_fn, SetFnT set_fn )
    {
        auto get = std::vformat( "get_{}", std::make_format_args( name.toStd() ) );
        auto set = std::vformat( "set_{}", std::make_format_args( name.toStd() ) );
        auto _var_name = std::vformat( "p_{}", std::make_format_args( name.toStd() ) );
        godot::ClassDB::bind_method( godot::D_METHOD( get.c_str() ), get_fn );
        godot::ClassDB::bind_method( godot::D_METHOD( set.c_str(), _var_name.c_str() ), set_fn );
        godot::ClassDB::add_property( ParentT::get_class_static(),
                godot::PropertyInfo( get_godot_variant_t<ParentT>(), name ), set.c_str(), get.c_str() );
    }

    template<GodotNode ParentT, typename... TypedProperty>
    static void signal( pwm::string_view signal_name, TypedProperty... args )
    {
        // godot::ClassDB::add_signal( ParentT::get_class_static(),
        //                            godot::MethodInfo{ signal_name,
        //                                              godot::PropertyInfo{ godot::Variant::BOOL, TOGGLED },
        //                                              godot::PropertyInfo{ godot::Variant::INT, SKILL_NUM },
        //                                              godot::PropertyInfo{ godot::Variant::INT, SKILL_GROUP } } );
    }
};

}
