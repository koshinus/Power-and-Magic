#pragma once

#include <string>

#include <godot_cpp/classes/control.hpp>

namespace godot
{
class Button;
class TextureButton;
class Label;
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
    void on_btn_pressed();
    void on_obj_received( ObjectWrapper<std::string>* obj_info );
protected:
    static void _bind_methods();
private:
    godot::Button* m_button;
    godot::TextureButton* m_txt_button;
    godot::Label* m_lbl;
    SkillButtonImpl* m_skill_btn;
};

}
