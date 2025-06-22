#include <tl/expected.hpp>

#include <godot_cpp/classes/confirmation_dialog.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/godot.hpp>

#include "utils/pwm_string_view.hpp"
#include "main_menu_impl.hpp"

namespace pwm
{

constexpr auto ON_CONFIRMED = pwm::string_view{ "on_confirmed" };
constexpr auto ON_CANCELED = pwm::string_view{ "on_canceled" };
constexpr auto ON_PLAY = pwm::string_view{ "on_play_pressed" };
constexpr auto ON_QUIT = pwm::string_view{ "on_quit_pressed" };
constexpr auto PRESSED_SIGNAL = pwm::string_view{ "pressed" };

MainMenuImpl::MainMenuImpl()
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
}

void MainMenuImpl::test_pressed()
{

}

void MainMenuImpl::normal_pressed()
{

}

void MainMenuImpl::on_play_pressed()
{
    test_pressed();
    // normal_pressed();
}

// std::unique_ptr<ConfirmationDialog> MainMenuImpl::form_quit_dialog()
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
