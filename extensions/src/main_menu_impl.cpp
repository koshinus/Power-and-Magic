#include <godot_cpp/classes/confirmation_dialog.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/margin_container.hpp>

#include "utils/pwm_string_view.hpp"
#include "utils/pwm_bindings.hpp"
#include "utils/pwm_signals.hpp"
// #include "global_level_impl.hpp"

#include "main_menu_impl.hpp"

namespace pwm
{

constinit auto GLOBAL_LVL_SCENE = pwm::string_view{ "res://scenes/global_level.tscn" };

constinit auto ON_CONFIRMED = pwm::string_view{ "on_confirmed" };
constinit auto ON_CANCELED = pwm::string_view{ "on_canceled" };
constinit auto ON_PLAY = pwm::string_view{ "on_play_pressed" };
constinit auto ON_QUIT = pwm::string_view{ "on_quit_pressed" };

constinit auto MARGIN_CONTAINER = pwm::string_view{ "MarginContainer" };

MainMenuImpl::MainMenuImpl()
    : godot::Control()
{
}

MainMenuImpl::~MainMenuImpl()
{
}

void MainMenuImpl::_bind_methods()
{
    using bh = BindHelper<MainMenuImpl>;
    bh::method( ON_PLAY, &MainMenuImpl::on_play_pressed );
    bh::method( ON_QUIT, &MainMenuImpl::on_quit_pressed );
    bh::method( ON_CONFIRMED, &MainMenuImpl::on_confirmed );
    bh::method( ON_CANCELED, &MainMenuImpl::on_canceled );
}

void MainMenuImpl::on_play_pressed()
{
    // auto glob_lvl = loadSceneAsNode<GlobalLevelImpl>( GLOBAL_LVL_SCENE );
    // add_child( glob_lvl );
    // If left buttons in the main scene player could accidentally click on them
    // get_node<godot::MarginContainer>( MARGIN_CONTAINER )->hide();
}

godot::ConfirmationDialog* MainMenuImpl::form_quit_dialog()
{
    auto d = memnew( godot::ConfirmationDialog );
    d->set_title( "" );
    d->set_text( "Are you really want to quit?" );

    d->get_ok_button()->connect( signals::PRESSED, godot::Callable{ this, ON_CONFIRMED } );
    d->get_cancel_button()->connect( signals::PRESSED, godot::Callable{ this, ON_CANCELED } );

    return d;
}

void MainMenuImpl::on_quit_pressed()
{
    auto dialog = form_quit_dialog();
    add_child( dialog );
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
