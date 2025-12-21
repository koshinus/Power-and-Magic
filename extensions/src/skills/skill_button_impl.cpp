#include <godot_cpp/classes/texture_button.hpp>

#include "../utils/pwm_string_view.hpp"
#include "../utils/pwm_bindings.hpp"
#include "../utils/pwm_signals.hpp"
#include "../utils/pwm_constants.hpp"
#include "../utils/pwm_funcs.hpp"

#include "skill_button_impl.hpp"

namespace pwm
{

constinit auto BTN = pwm::string_view{ "Btn" };

constinit auto TEXTURE = pwm::string_view{ "texture" };
constinit auto SKILL_NUM = pwm::string_view{ "skill_num" };
constinit auto SKILL_GROUP = pwm::string_view{ "skill_group" };

constinit auto TOGGLED = pwm::string_view{ "toggled" };

SkillButtonImpl::SkillButtonImpl()
    : godot::Control()
    // : m_texture( nullptr )
    , m_skill_num( 0 )
    , m_skill_group( 0 )
{

}

SkillButtonImpl::~SkillButtonImpl()
{
}

void SkillButtonImpl::_bind_methods()
{
    using bh = BindHelper<SkillButtonImpl>;

    // TODO: godot::ImageTexture is not in Variant type
    // PwmProperty<godot::ImageTexture>::bind<SkillButtonImpl>( TEXTURE,
    //                                       &SkillButtonImpl::get_texture,
    //                                       &SkillButtonImpl::set_texture );
    bh::property<int>( SKILL_NUM, &SkillButtonImpl::get_skill_num,
                                  &SkillButtonImpl::set_skill_num );
    bh::property<int>( SKILL_GROUP, &SkillButtonImpl::get_skill_group,
                                    &SkillButtonImpl::set_skill_group );

    bh::signal( signals::SKILL_ACTIVATED, godot::PropertyInfo{ godot::Variant::BOOL, TOGGLED },
                                          godot::PropertyInfo{ godot::Variant::INT, SKILL_NUM },
                                          godot::PropertyInfo{ godot::Variant::INT, SKILL_GROUP } );
}

godot::Ref<godot::Texture2D> SkillButtonImpl::circled_texture( godot::Ref<godot::Texture2D> txtr, godot::Color color, int radius, godot::Vector2 center )
{
    auto res_img = txtr->get_image();
    for_each_2d( txtr->get_size(), [&res_img, color, radius, center]( godot::Vector2i v ) {
        if ( ( godot::Vector2( v ) - center ).length() == radius )
        {
            res_img->set_pixelv( v, color );
        }
    } );
    return godot::ImageTexture::create_from_image( res_img );
}

godot::Ref<godot::Texture2D> SkillButtonImpl::grayscaled_texture( godot::Ref<godot::Texture2D> txtr )
{
    auto res_img = txtr->get_image();
    for_each_2d( txtr->get_size(), [&res_img]( godot::Vector2i v ) {
        godot::Color color = res_img->get_pixelv( v );
        auto grayed = ( color.r + color.g + color.b )/3;
        res_img->set_pixelv( v, godot::Color( grayed, grayed, grayed ) );
    } );
    return godot::ImageTexture::create_from_image( res_img );
}

void SkillButtonImpl::enable_button( bool enable )
{
    get_node<godot::TextureButton>( BTN )->set_disabled( !enable );
}

void SkillButtonImpl::setup_textures( const godot::Ref<godot::Texture2D>& txtr )
{
    auto btn = get_node<godot::TextureButton>( BTN );
    btn->set_texture_normal( txtr );
    btn->set_texture_disabled( grayscaled_texture( txtr ) );
    btn->set_texture_pressed( circled_texture( btn->get_texture_disabled(),
                                colors::YELLOW, txtr->get_width()/2, txtr->get_size()/2 ) );
}

void SkillButtonImpl::on_btn_toggled( bool toggled_on )
{
    emit_signal( signals::SKILL_ACTIVATED, toggled_on, m_skill_num, m_skill_group );
    emit_signal( signals::SKILL_ACTIVATED, toggled_on, 0, 0 );
}

}
