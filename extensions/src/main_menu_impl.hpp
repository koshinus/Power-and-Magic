#pragma once

#include <godot_cpp/classes/node.hpp>

namespace godot
{
class ConfirmationDialog;
}

namespace pwm
{

class MainMenuImpl: public godot::Node
{
    GDCLASS( MainMenuImpl, godot::Node )
private:
    godot::ConfirmationDialog* form_quit_dialog();
    void test_pressed();
    void normal_pressed();

    // double amplitude;
protected:
    static void _bind_methods();
public:
    MainMenuImpl();
    ~MainMenuImpl();
    void on_quit_pressed();
    void on_confirmed();
    void on_canceled();
    void on_play_pressed();

    // double get_amplitude() { return amplitude; }
    // void set_amplitude( const double _amplitude ) { amplitude = _amplitude; }
};

}
