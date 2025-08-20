#include <godot_cpp/classes/texture_button.hpp>

#include "../utils/pwm_string_view.hpp"

#include "skill_button_impl.hpp"

namespace pwm
{

constexpr auto BTN = pwm::string_view{ "Btn" };

constexpr auto TEXTURE = pwm::string_view{ "texture" };
constexpr auto SKILL_NUM = pwm::string_view{ "skill_num" };
constexpr auto SKILL_GROUP = pwm::string_view{ "skill_group" };

constexpr auto TOGGLED = pwm::string_view{ "toggled" };

namespace signals
{
constexpr auto SKILL_ACTIVATED = pwm::string_view{ "skill_activated" };
}

// @export var skill_num : int = 0
// @export var skill_group : int = 0
// @export var texture : ImageTexture

// signal skill_activated( toggled : bool, num : int, group : int )

SkillButtonImpl::SkillButtonImpl()
    : m_texture( godot::ImageTexture() )
    , m_skill_num( 0 )
    , m_skill_group( 0 )
{

}

SkillButtonImpl::~SkillButtonImpl()
{
}

void SkillButtonImpl::_bind_methods()
{
    // TODO: godot::ImageTexture is not in Variant type
    // PwmProperty<godot::ImageTexture>::bind<SkillButtonImpl>( TEXTURE,
    //                                       &SkillButtonImpl::get_texture,
    //                                       &SkillButtonImpl::set_texture );
    PwmProperty<int>::bind<SkillButtonImpl>( SKILL_NUM,
                                          &SkillButtonImpl::get_skill_num,
                                          &SkillButtonImpl::set_skill_num );
    PwmProperty<int>::bind<SkillButtonImpl>( SKILL_GROUP,
                                          &SkillButtonImpl::get_skill_group,
                                          &SkillButtonImpl::set_skill_group );

    godot::ClassDB::add_signal( get_class_static(),
                               godot::MethodInfo{ signals::SKILL_ACTIVATED.toStd().data(),
                                                 godot::PropertyInfo{ godot::Variant::BOOL, TOGGLED },
                                                 godot::PropertyInfo{ godot::Variant::INT, SKILL_NUM },
                                                 godot::PropertyInfo{ godot::Variant::INT, SKILL_GROUP } } );
}

godot::Ref<godot::Texture2D> SkillButtonImpl::circled_texture( godot::Ref<godot::Texture2D> txtr, godot::Color color, int radius, godot::Vector2 center )
{
    auto res_img = txtr->get_image();
    godot::Vector2i size = txtr->get_size();
    for ( int y = 0; y < size.y; y ++ )
    {
        for ( int x = 0; x < size.x; x++ )
        {
            if ( ( godot::Vector2( x, y ) - center ).length() == radius )
                res_img->set_pixel( x, y, color );
        }
    }
    return godot::ImageTexture::create_from_image( res_img );
}

godot::Ref<godot::Texture2D> SkillButtonImpl::grayscaled_texture( godot::Ref<godot::Texture2D> txtr )
{
    auto res_img = txtr->get_image();
    godot::Vector2i size = txtr->get_size();
    for ( int y = 0; y < size.y; y++ )
    {
        for ( int x = 0; x < size.x; x++ )
        {
            godot::Color color = res_img->get_pixel( x, y );
            //Most popular algo for grayscailng was choosed: I=0.299R+0.587G+0.114B
            res_img->set_pixel( x, y, godot::Color( color.get_r8()*0.299, color.get_g8()*0.587, color.get_b8()*0.114 ) );
        }
    }
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
                                godot::Color( 1, 1, 0, 1 ), // Color.YELLOW
                                txtr->get_width()/2, txtr->get_size()/2 ) );
}

void SkillButtonImpl::on_btn_toggled( bool toggled_on )
{
    emit_signal( signals::SKILL_ACTIVATED, toggled_on, m_skill_num.val, m_skill_group.val );
}

godot::ImageTexture SkillButtonImpl::get_texture()
{
    return m_texture.val;
}

void SkillButtonImpl::set_texture( const godot::ImageTexture val )
{
    // TODO: change types to Ref<>
    // m_texture.val = val;
}

int SkillButtonImpl::get_skill_num()
{
    return m_skill_num.val;
}

void SkillButtonImpl::set_skill_num( const int val )
{
    m_skill_num.val = val;
}

int  SkillButtonImpl::get_skill_group()
{
    return m_skill_group.val;
}

void SkillButtonImpl::set_skill_group( const int val )
{
    m_skill_group.val = val;
}

}
