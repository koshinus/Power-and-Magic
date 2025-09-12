#pragma once

#include <format>
#include <concepts>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

#include "pwm_string_view.hpp"

namespace pwm
{

template<typename NodeT>
concept GodotNode = std::derived_from<NodeT, godot::Node>;

template<typename T>
concept GodotVariant = std::convertible_to<T, godot::Variant>;

template<typename T>
concept GodotPropertyInfo = std::convertible_to<T, godot::PropertyInfo>;

template<typename RetT, typename T>
using SetPtrType = void(T::*)(const RetT);

template<typename RetT, typename T>
using GetPtrType = RetT(T::*)() const;

template<typename T, typename RetT, typename... Args>
using MemFnPtr = RetT(T::*)(Args...);

template<typename T, typename... Args>
using VoidMemFnPtr = void(T::*)(Args...);

template<typename T, typename ParentT>
concept PropertySetMethod = std::is_member_function_pointer_v<SetPtrType<T, ParentT>>;

template<typename T, typename ParentT>
concept PropertyGetMethod = std::is_member_function_pointer_v<GetPtrType<T, ParentT>>;

template<typename T, typename RetT, typename... Args>
concept PropertyMethod = std::is_member_function_pointer_v<MemFnPtr<T, RetT, Args>...>;

template<typename T, typename RetT, typename... Args>
concept VoidPropertyMethod = std::is_member_function_pointer_v<VoidMemFnPtr<T, Args>...>;

template<typename T>
consteval godot::Variant::Type get_godot_variant_t()
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

template<GodotNode T>
T* loadSceneAsNode( pwm::string_view path_to_scene )
{
    auto loaded_resource = godot::ResourceLoader::get_singleton()->load( path_to_scene );
    return static_cast<T*>( static_cast<godot::PackedScene*>( loaded_resource.ptr() )->instantiate() );
}

template<GodotNode T>
godot::Window* getRoot( T* scene )
{
    return scene->get_tree()->get_root();
}

template<GodotNode ParentT>
struct BindHelper
{
    template<typename RetT, typename MethodT, GodotVariant... Args>
    requires std::same_as<MemFnPtr<ParentT, RetT, Args...>, MethodT>
    static godot::MethodBind* method( pwm::string_view mname, MethodT fn, Args... args )
    {
        return godot::ClassDB::bind_method( godot::D_METHOD( mname ), fn, args... );
    }

    template<typename MethodT, GodotVariant... Args>
    requires std::same_as<VoidMemFnPtr<ParentT, Args...>, MethodT>
    static godot::MethodBind* method( pwm::string_view mname, MethodT fn, Args... args )
    {
        return godot::ClassDB::bind_method( godot::D_METHOD( mname ), fn, args... );
    }

    template<typename PropT, typename GetFnT, typename SetFnT>
    requires std::same_as<GetPtrType<PropT, ParentT>, GetFnT> &&
             std::same_as<SetPtrType<PropT, ParentT>, SetFnT>
    static void property( pwm::string_view name, GetFnT get_fn, SetFnT set_fn )
    {
        auto get = std::vformat( "get_{}", std::make_format_args( name.toStd() ) );
        auto set = std::vformat( "set_{}", std::make_format_args( name.toStd() ) );
        auto _var_name = std::vformat( "p_{}", std::make_format_args( name.toStd() ) );
        godot::ClassDB::bind_method( godot::D_METHOD( get.c_str() ), get_fn );
        godot::ClassDB::bind_method( godot::D_METHOD( set.c_str(), _var_name.c_str() ), set_fn );
        godot::ClassDB::add_property( ParentT::get_class_static(),
                godot::PropertyInfo( get_godot_variant_t<PropT>(), name ), set.c_str(), get.c_str() );
    }

    template<GodotPropertyInfo... Args>
    static void signal( pwm::string_view signal_name, const Args&... args )
    {
        godot::ClassDB::add_signal( ParentT::get_class_static(), godot::MethodInfo{ signal_name, args...} );
    }
};

}
