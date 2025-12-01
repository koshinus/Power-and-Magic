#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/texture2d.hpp>

#include "utils/pwm_string_view.hpp"
#include "utils/pwm_bindings.hpp"
#include "skills/skill_button_impl.hpp"

#include "test_node_impl.hpp"

namespace pwm
{

constinit auto ON_CHANGE_STATE = pwm::string_view{ "on_change_state" };
constinit auto SKILL_BTN = pwm::string_view{ "SkillBtn" };
constinit auto BTN__ = pwm::string_view{ "Button" };
constinit auto TXT_BTN = pwm::string_view{ "TxtButton" };

TestNodeImpl::TestNodeImpl()
    : m_button{ nullptr }
    , m_txt_button{ nullptr }
    , m_skill_btn{ nullptr }
{
    godot::print_line( "TestNodeImpl" );
}

TestNodeImpl::~TestNodeImpl()
{
    godot::print_line( "~TestNodeImpl" );
}

void TestNodeImpl::_bind_methods()
{
    using bh = BindHelper<TestNodeImpl>;
    bh::method( ON_CHANGE_STATE, &TestNodeImpl::on_change_state );
}

void TestNodeImpl::_ready()
{
    godot::print_line( "TestNodeImpl::_ready" );

    // auto skill_button = get_node<godot::Button>( SKILL_BTN );
    m_skill_btn = gnode_cast<SkillButtonImpl>( get_node<godot::Button>( SKILL_BTN ) );
    // m_skill_btn->setup_textures( godot::Texture2D:: );

    m_button = get_node<godot::Button>( BTN__ );
    m_txt_button = get_node<godot::TextureButton>( TXT_BTN );
}

void TestNodeImpl::on_change_state()
{
    godot::print_line( "state changed!" );
    godot::print_line( ( m_skill_btn != nullptr ? "all fine!" : "button didn't casted" ) );
    godot::print_line( ( m_button != nullptr ? "all fine!" : "button didn't casted" ) );
    // auto children = get_children();
    // for ( auto i = 0; i < children.size(); i++ ) {
    //     godot::print_line( "current node is ", children.get( i ) );
    // }
    // auto skill_button = get_node<godot::Control>( SKILL_BTN );
    // godot::print_line( "state changed!" );
    // if ( !skill_button ) {
    //     godot::print_line( "button didn't casted" );
    // } else {
    //     godot::print_line( "all fine!" );
    // }
    // auto real_skill_button = gnode_cast<SkillButtonImpl>( skill_button );
    // if ( !real_skill_button ) {
    //     godot::print_line( "button didn't casted" );
    // } else {
    //     godot::print_line( "all fine!" );
    // }
}

}
