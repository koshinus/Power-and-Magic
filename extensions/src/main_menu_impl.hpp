#pragma once

#include <godot_cpp/classes/control.hpp>

namespace godot
{
class ConfirmationDialog;
}

namespace pwm
{

class MainMenuImpl: public godot::Control
{
    GDCLASS( MainMenuImpl, godot::Control )
public:
    MainMenuImpl();
    ~MainMenuImpl();
    void on_quit_pressed();
    void on_confirmed();
    void on_canceled();
    void on_play_pressed();

    double get_amplitude() const { return amplitude; }
    void set_amplitude( const double p_amplitude ) { amplitude = p_amplitude; }
protected:
    static void _bind_methods();
private:
    godot::ConfirmationDialog* form_quit_dialog();
    void test_pressed();
    void normal_pressed();

    double amplitude;
};

}
