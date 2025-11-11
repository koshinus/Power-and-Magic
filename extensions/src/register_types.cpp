#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "utils/pwm_bindings.hpp"

#include "main_menu_impl.hpp"
#include "test_node_impl.hpp"
#include "skills/skill_button_impl.hpp"
#include "global_level_impl.hpp"
#include "combat_interface_impl.hpp"
#include "selectable_impl.hpp"
#include "resources_info_impl.hpp"
#include "grid_2d_node_impl.hpp"
#include "global_level_impl.hpp"
#include "combat_interface_impl.hpp"
#include "army_info_impl.hpp"
#include "skills/skill_wheel_impl.hpp"
#include "skills/military_skills_impl.hpp"
#include "skills/economy_skills_impl.hpp"
#include "skills/magic_skills_impl.hpp"
#include "maps/map_limitations_impl.hpp"
#include "maps/local_map_impl.hpp"
#include "maps/combat_map_impl.hpp"


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

    pwm::registrate<
        pwm::MainMenuImpl
        , pwm::TestNodeImpl
        , pwm::SkillButtonImpl
        , pwm::GlobalLevelImpl
        , pwm::CombatInterfaceImpl
        , pwm::CombatMapImpl
        , pwm::ArmyInfoImpl
        , pwm::SelectableImpl
        , pwm::ResourcesInfoImpl
        , pwm::Grid2dNodeImpl
        , pwm::MilitarySkillsImpl
        , pwm::EconomySkillsImpl
        , pwm::SkillWheelImpl
        , pwm::MagicSkillsImpl
        , pwm::MapLimitationsImpl
        , pwm::LocalMapImpl
        >();
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
