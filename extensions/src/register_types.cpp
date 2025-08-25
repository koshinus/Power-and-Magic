#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "utils/pwm_properties.hpp"

#include "main_menu_impl.hpp"
// #include "global_level_impl.hpp"
// #include "combat_interface_impl.hpp"

#include "register_types.hpp"

namespace pwm
{

template<GodotNode T>
void registrate_one()
{
    godot::ClassDB::register_runtime_class< T >();
}

template<GodotNode... Types>
void registrate()
{
    (registrate_one<Types>(), ...);
}

}

void initialize_pwmlibs_module( godot::ModuleInitializationLevel p_level )
{
    if ( p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE )
    {
        return;
    }

    pwm::registrate< pwm::MainMenuImpl >();
}

void uninitialize_pwmlibs_module( godot::ModuleInitializationLevel p_level )
{
    if ( p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE )
    {
        return;
    }
}

extern "C"
{

// Initialization.
GDExtensionBool GDE_EXPORT pwmlibs_library_init( GDExtensionInterfaceGetProcAddress p_get_proc_address,
                                                 const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization )
{
    godot::GDExtensionBinding::InitObject init_obj( p_get_proc_address, p_library, r_initialization );

    init_obj.register_initializer( initialize_pwmlibs_module );
    init_obj.register_terminator( uninitialize_pwmlibs_module );
    init_obj.set_minimum_library_initialization_level( godot::MODULE_INITIALIZATION_LEVEL_SCENE );

    return init_obj.init();
}

}
