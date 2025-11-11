#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

#include "utils/pwm_string_view.hpp"
#include "utils/pwm_signals.hpp"
#include "utils/pwm_bindings.hpp"

#include "selectable_impl.hpp"

namespace pwm
{

constinit auto BUTTON = pwm::string_view{ "Button" };

constinit auto EXCLUSIVE = pwm::string_view{ "exclusive" };
constinit auto GROUP_NAME = pwm::string_view{ "group_name" };
constinit auto SELECTED_FLAG = pwm::string_view{ "selection_flag" };

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
    using bh = BindHelper<SelectableImpl>;

    bh::property<godot::String>( GROUP_NAME, &SelectableImpl::get_group_name,
                                             &SelectableImpl::set_group_name );
    bh::property<bool>( EXCLUSIVE, &SelectableImpl::get_exclusive,
                                   &SelectableImpl::set_exclusive );

    bh::signal( signals::SELECTED, godot::PropertyInfo{ godot::Variant::BOOL, SELECTED_FLAG } );
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

}
