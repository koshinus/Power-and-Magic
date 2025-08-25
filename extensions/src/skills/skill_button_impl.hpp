#pragma once

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/ref.hpp>

namespace pwm
{

class SkillButtonImpl: public godot::Control
{
    GDCLASS( SkillButtonImpl, godot::Control )
public:
    SkillButtonImpl();
    ~SkillButtonImpl();

    void on_btn_toggled( bool toggled_on );
    void enable_button( bool enable );
    void setup_textures( const godot::Ref<godot::Texture2D>& txtr );

    godot::ImageTexture get_texture() { return m_texture; }
    void set_texture( const godot::ImageTexture val ) { /*TODO*/ }
    int get_skill_num() { return m_skill_num; }
    void set_skill_num( const int val ) { m_skill_num = val; }
    int get_skill_group() { return m_skill_group; }
    void set_skill_group( const int val ) { m_skill_group = val; }
protected:
    static void _bind_methods();
private:
    godot::ImageTexture m_texture;
    int m_skill_num;
    int m_skill_group;

    godot::Ref<godot::Texture2D> circled_texture( godot::Ref<godot::Texture2D> txtr, godot::Color color, int radius, godot::Vector2 center );
    godot::Ref<godot::Texture2D> grayscaled_texture( godot::Ref<godot::Texture2D> txtr );
};

}
