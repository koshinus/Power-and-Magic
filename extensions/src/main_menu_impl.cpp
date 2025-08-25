#include <godot_cpp/classes/confirmation_dialog.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/margin_container.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

#include "utils/pwm_string_view.hpp"
#include "utils/pwm_properties.hpp"
// #include "test_node_impl.hpp"
// #include "global_level_impl.hpp"

#include "main_menu_impl.hpp"

namespace pwm
{

constexpr auto GLOBAL_LVL_SCENE = pwm::string_view{ "res://scenes/global_level.tscn" };
constexpr auto TEST_NODE_SCENE = pwm::string_view{ "res://scenes/test_node.tscn" };

constexpr auto ON_CONFIRMED = pwm::string_view{ "on_confirmed" };
constexpr auto ON_CANCELED = pwm::string_view{ "on_canceled" };
constexpr auto ON_PLAY = pwm::string_view{ "on_play_pressed" };
constexpr auto ON_QUIT = pwm::string_view{ "on_quit_pressed" };
constexpr auto PRESSED_SIGNAL = pwm::string_view{ "pressed" };

constexpr auto AMPLITUDE = pwm::string_view{ "amplitude" };

constexpr auto MARGIN_CONTAINER = pwm::string_view{ "MarginContainer" };

MainMenuImpl::MainMenuImpl()
    : amplitude( 10 )
{
}

MainMenuImpl::~MainMenuImpl()
{
}

void MainMenuImpl::_bind_methods()
{
    godot::ClassDB::bind_method( godot::D_METHOD( ON_PLAY ), &MainMenuImpl::on_play_pressed );
    godot::ClassDB::bind_method( godot::D_METHOD( ON_QUIT ), &MainMenuImpl::on_quit_pressed );
    godot::ClassDB::bind_method( godot::D_METHOD( ON_CONFIRMED ), &MainMenuImpl::on_confirmed );
    godot::ClassDB::bind_method( godot::D_METHOD( ON_CANCELED ), &MainMenuImpl::on_canceled );

    BindHelper::property<MainMenuImpl>( AMPLITUDE, &MainMenuImpl::get_amplitude, &MainMenuImpl::set_amplitude );
}

void MainMenuImpl::test_pressed()
{
    //auto loaded_resource = godot::ResourceLoader::get_singleton()->load( TEST_NODE_SCENE );
    //auto inst = dynamic_cast<TestNodeImpl*>( dynamic_cast<godot::PackedScene*>( loaded_resource.ptr() )->instantiate() );
    // inst->init_by_params( 7, std::vector<int>{ 4, 5, 5, 6 } );
    //get_tree()->get_root()->add_child( inst );
}

void MainMenuImpl::normal_pressed()
{
    //auto loaded_resource = godot::ResourceLoader::get_singleton()->load( GLOBAL_LVL_SCENE );
    //auto glob_lvl = dynamic_cast<GlobalLevelImpl*>( dynamic_cast<godot::PackedScene*>( loaded_resource.ptr() )->instantiate() );
    //get_tree()->get_root()->add_child( glob_lvl );
    // If left buttons in the main scene player could accidentally click on them
    //get_node<godot::MarginContainer>( MARGIN_CONTAINER )->hide();
}

void MainMenuImpl::on_play_pressed()
{
    // test_pressed();
    normal_pressed();
}

godot::ConfirmationDialog* MainMenuImpl::form_quit_dialog()
{
    auto d = memnew( godot::ConfirmationDialog );
    d->set_title( "" );
    d->set_text( "Are you really want to quit?" );

    d->get_ok_button()->connect( PRESSED_SIGNAL, godot::Callable{ this, ON_CONFIRMED } );
    d->get_cancel_button()->connect( PRESSED_SIGNAL, godot::Callable{ this, ON_CANCELED } );

    return d;
}

void MainMenuImpl::on_quit_pressed()
{
    auto dialog = form_quit_dialog();
    get_tree()->get_current_scene()->add_child( dialog );
    dialog->popup_centered();
}

void MainMenuImpl::on_confirmed()
{
    get_tree()->quit();
}

void MainMenuImpl::on_canceled()
{
}

}
