#pragma once

#include <godot_cpp/classes/control.hpp>

namespace godot
{
class Button;
class TextureButton;
}

namespace pwm
{

class SkillButtonImpl;


class TestNodeImpl: public godot::Control
{
    GDCLASS( TestNodeImpl, godot::Control )
public:
    void _ready() override;
    TestNodeImpl();
    ~TestNodeImpl();

    void on_change_state();
protected:
    static void _bind_methods();
private:
    godot::Button* m_button;
    godot::TextureButton* m_txt_button;
    SkillButtonImpl* m_skill_btn;
};

}
