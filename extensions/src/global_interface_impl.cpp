#include <godot_cpp/core/print_string.hpp>
#include <godot_cpp/classes/h_box_container.hpp>
#include <godot_cpp/classes/panel.hpp>

#include "utils/pwm_string_view.hpp"
#include "global_interface_impl.hpp"

namespace pwm
{

constexpr auto HBOX_ARMY = pwm::string_view{ "HBoxArmy" };
constexpr auto HERO_PANEL = pwm::string_view{ "HeroPanel" };
constexpr auto HBOX_ADDITIONAL_BTNS = pwm::string_view{ "HBoxAdditionalButtons" };

namespace signals
{
constexpr auto VIEW_CHANGED = pwm::string_view{ "view_changed" };
constexpr auto MAGIC_BOOK_CLICKED = pwm::string_view{ "magic_book_clicked" };
}

void GlobalInterfaceImpl::_ready()
{
    get_node<godot::HBoxContainer>( HBOX_ARMY )->hide();
    get_node<godot::Panel>( HERO_PANEL )->hide();
    get_node<godot::HBoxContainer>( HBOX_ADDITIONAL_BTNS )->hide();
}

void GlobalInterfaceImpl::_bind_methods()
{
    // godot::ClassDB::add_signal( get_class_static(), godot::MethodInfo{ signals::VIEW_CHANGED } );
    // godot::ClassDB::add_signal( get_class_static(), godot::MethodInfo{ signals::MAGIC_BOOK_CLICKED } );
}

void GlobalInterfaceImpl::show_hero_depending_parts( std::optional<HeroInfo> info )
{
    // godot::print_line( "Info is ", info );
    if ( info )
    {
        get_node<godot::HBoxContainer>( HBOX_ARMY )->hide();
        get_node<godot::Panel>( HERO_PANEL )->hide();
        get_node<godot::HBoxContainer>( HBOX_ADDITIONAL_BTNS )->hide();
    }
    else
    {
        get_node<godot::HBoxContainer>( HBOX_ARMY )->show();
        get_node<godot::Panel>( HERO_PANEL )->show();
        get_node<godot::HBoxContainer>( HBOX_ADDITIONAL_BTNS )->show();
    }
}

void GlobalInterfaceImpl::on_btn_change_view_pressed()
{
    emit_signal( signals::VIEW_CHANGED );
}

void GlobalInterfaceImpl::on_btn_magic_book_pressed()
{
    emit_signal( signals::MAGIC_BOOK_CLICKED );
}

}
