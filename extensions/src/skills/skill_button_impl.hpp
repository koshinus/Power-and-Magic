#pragma once

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/ref.hpp>

#include "../utils/pwm_properties.hpp"

namespace pwm
{

class SkillButtonImpl: public godot::Control
{
    GDCLASS( SkillButtonImpl, godot::Control )
private:
    PwmProperty<godot::ImageTexture> m_texture;
    PwmProperty<int> m_skill_num;
    PwmProperty<int> m_skill_group;

    godot::Ref<godot::Texture2D> circled_texture( godot::Ref<godot::Texture2D> txtr, godot::Color color, int radius, godot::Vector2 center );
    godot::Ref<godot::Texture2D> grayscaled_texture( godot::Ref<godot::Texture2D> txtr );
protected:
    static void _bind_methods();
public:
    SkillButtonImpl();
    ~SkillButtonImpl();

    void on_btn_toggled( bool toggled_on );
    void enable_button( bool enable );
    void setup_textures( const godot::Ref<godot::Texture2D>& txtr );

    godot::ImageTexture get_texture();
    void set_texture( const godot::ImageTexture val );
    int get_skill_num();
    void set_skill_num( const int val );
    int get_skill_group();
    void set_skill_group( const int val );
};

}
