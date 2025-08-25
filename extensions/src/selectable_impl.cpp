//extends Control
//class_name Selectable

#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

#include "utils/pwm_string_view.hpp"

#include "selectable_impl.hpp"

namespace pwm
{

constexpr auto EXCLUSIVE = pwm::string_view{ "exclusive" };
constexpr auto GROUP_NAME = pwm::string_view{ "group_name" };
constexpr auto BUTTON = pwm::string_view{ "Button" };
constexpr auto SELECTED = pwm::string_view{ "selection_flag" };

namespace signals
{
constexpr auto SELECTED = pwm::string_view{ "selected" };
}

//signal selected( selection_flag : bool )

// @export var exclusive = true
// @export var group_name : String

// var is_selected : bool = false : set = set_selected;

SelectableImpl::SelectableImpl()
    : m_group_name( "" )
    , m_exclusive( true )
{
}

SelectableImpl::~SelectableImpl()
{
}

void SelectableImpl::_bind_methods()
{
    // BindHelper::property<SelectableImpl>( GROUP_NAME,
    //                                        &SelectableImpl::get_group_name,
    //                                        &SelectableImpl::set_group_name );
    // BindHelper::property<SelectableImpl>( EXCLUSIVE,
    //                                        &SelectableImpl::get_exclusive,
    //                                        &SelectableImpl::set_exclusive );

    // godot::ClassDB::add_signal( get_class_static(), godot::MethodInfo{ signals::SELECTED,
    //                                                 godot::PropertyInfo{ godot::Variant::BOOL, SELECTED } } );
}

void SelectableImpl::set_selected( bool selection_flag )
{
    //print("Setting selected to ", selection_flag, " for node ", self)
    if ( selection_flag )
    {
        make_exclusive();
        add_to_group( m_group_name );
    }
    else
    {
        get_node<godot::Button>( BUTTON )->release_focus();
        remove_from_group( m_group_name );
    }
    m_is_selected = selection_flag;
    emit_signal( signals::SELECTED, m_is_selected );
}

void SelectableImpl::make_exclusive()
{
    if ( m_exclusive )
    {
        get_tree()->call_group( m_group_name, "set_selected", false );
    }
}

void SelectableImpl::on_button_pressed()
{
    set_selected( !m_is_selected );
}


godot::String SelectableImpl::get_group_name()
{
    return m_group_name;
}

void SelectableImpl::set_group_name( const godot::String val )
{
    m_group_name = val;
}

bool SelectableImpl::get_exclusive()
{
    return m_exclusive;
}

void SelectableImpl::set_exclusive( const bool val )
{
    m_exclusive = val;
}

}
