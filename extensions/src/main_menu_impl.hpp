#pragma once

#include <godot_cpp/classes/control.hpp>

namespace godot
{
class ConfirmationDialog;
}

namespace pwm
{

/*
 * MainMenu
 *  MarginContainer, type - MarginContainer
 *      VBoxContainer, type - VBoxContainer
 *          Play, type - Button
 *          Quit, type - Button
 */
class MainMenuImpl: public godot::Control
{
    GDCLASS( MainMenuImpl, godot::Control )
public:
    MainMenuImpl();
    ~MainMenuImpl() override;
    void on_quit_pressed();
    void on_confirmed();
    void on_canceled();
    void on_play_pressed();

protected:
    static void _bind_methods();
private:
    godot::ConfirmationDialog* form_quit_dialog();
};

}
