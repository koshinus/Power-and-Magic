#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/texture_button.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>

#include "utils/pwm_string_view.hpp"
#include "utils/pwm_bindings.hpp"
#include "utils/pwm_signals.hpp"
#include "utils/pwm_object_wrapper.hpp"
#include "skills/skill_button_impl.hpp"

#include "test_node_impl.hpp"

namespace pwm
{

//constinit auto ON_CHANGE_STATE = pwm::string_view{ "on_change_state" };
constinit auto ON_BTN_PRESSED = pwm::string_view{ "on_btn_pressed" };
constinit auto BTN__ = pwm::string_view{ "Button" };
constinit auto LABEL__ = pwm::string_view{ "Label" };
constinit auto OBJ_INFO = pwm::string_view{ "object_info" };
constinit auto ON_OBJ_RECIEVED = pwm::string_view{ "on_obj_received" };

TestNodeImpl::TestNodeImpl()
    : godot::Control()
    , m_button{ nullptr }
    , m_txt_button{ nullptr }
    , m_lbl{ nullptr }
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
    godot::print_line( "TestNodeImpl::_bind_methods" );
    using bh = BindHelper<TestNodeImpl>;
    //bh::method( ON_CHANGE_STATE, &TestNodeImpl::on_change_state );
    bh::method( ON_BTN_PRESSED, &TestNodeImpl::on_btn_pressed );
    //bh::method( godot::D_METHOD( ON_OBJ_RECIEVED, OBJ_INFO ), &TestNodeImpl::on_obj_received );
    //auto meth = godot::D_METHOD( pwm::string_view{ON_OBJ_RECIEVED}, pwm::string_view{OBJ_INFO} );
    //auto meth = godot::D_METHOD( ON_OBJ_RECIEVED, OBJ_INFO );
    //bh::method( meth, &TestNodeImpl::on_obj_received );
    bh::signal( signals::SEND_OBJECT, godot::PropertyInfo{ godot::Variant::OBJECT, OBJ_INFO } );
    // TODO: remove this shit! and fix the fuckin template code in pwm_bindings.hpp!
    godot::ClassDB::bind_method( godot::D_METHOD( ON_OBJ_RECIEVED, OBJ_INFO ), &TestNodeImpl::on_obj_received );
}

void TestNodeImpl::_ready()
{
    godot::print_line( "TestNodeImpl::_ready" );

    m_button = get_node<godot::Button>( BTN__ );
    m_lbl = get_node<godot::Label>( LABEL__ );
    //m_button->connect( signals::PRESSED, godot::Callable{ this, ON_BTN_PRESSED } );
    //this->connect( signals::SEND_OBJECT, godot::Callable{ this, ON_OBJ_RECIEVED } );
}

void TestNodeImpl::on_btn_pressed()
{
    godot::print_line( "button pressed, trying emit new signal" );
    auto rand_generator = memnew( godot::RandomNumberGenerator );
    auto some_str = std::string{ "sadasdasd" } + std::to_string( rand_generator->randi_range( 0, 100 ) );
    emit_signal( signals::SEND_OBJECT, memnew(TestObjInfo{some_str}) );
}

void TestNodeImpl::on_obj_received( TestObjInfo* obj_info )
{
    if( obj_info )
    {
        godot::print_line( "get correct object!", obj_info->m_line.c_str() );
    }
    if ( m_lbl )
    {
        godot::print_line( "get an object from signal!" );
        //m_lbl->set_text( godot::String{ obj_info->m_line.c_str() } );
    }
    else
    {
        godot::print_line( "no valid label!" );
    }
}
    
void TestNodeImpl::on_change_state()
{
    godot::print_line( "state changed!" );
    godot::print_line( ( m_button != nullptr ? "all fine!" : "button didn't casted" ) );
}

}
