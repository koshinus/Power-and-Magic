#include <string>

#include <godot_cpp/classes/texture_button.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/label.hpp>

#include "utils/pwm_string_view.hpp"
#include "numbered_texture_impl.hpp"

namespace pwm
{

constexpr auto BTN_WITH_TEXTURE = pwm::string_view{ "VBoxContainer/BtnWithTexture" };
constexpr auto AMOUNT = pwm::string_view{ "VBoxContainer/Amount" };

constexpr auto BTN_IS_ACTIVE = pwm::string_view{ "button_is_active" };
constexpr auto HIDE_ON_ZERO = pwm::string_view{ "hide_on_zero" };
constexpr auto BTN_TEXTURE = pwm::string_view{ "button_texture" };


namespace signals
{
constexpr auto TEXTURE_ACTIVATED = pwm::string_view{ "texture_activated" };
}

NumberedTextureImpl::NumberedTextureImpl()
    : m_button_texture( godot::Texture2D() )
    , m_hide_on_zero( false )
    , m_button_is_active( true )
{
}

NumberedTextureImpl::~NumberedTextureImpl()
{
}

void NumberedTextureImpl::_bind_methods()
{
    // TODO: godot::ImageTexture is not in Variant type
    // PwmProperty<godot::Texture2D>::bind<NumberedTextureImpl>( BTN_TEXTURE,
    //                                       &NumberedTextureImpl::get_button_texture,
    //                                       &NumberedTextureImpl::set_button_texture );

    BindHelper::property<NumberedTextureImpl>( BTN_IS_ACTIVE,
                                          &NumberedTextureImpl::get_btn_is_active,
                                          &NumberedTextureImpl::set_btn_is_active );

    BindHelper::property<NumberedTextureImpl>( HIDE_ON_ZERO,
                                          &NumberedTextureImpl::get_hide_on_zero,
                                          &NumberedTextureImpl::set_hide_on_zero );

    godot::ClassDB::add_signal( get_class_static(), godot::MethodInfo{ signals::TEXTURE_ACTIVATED } );
}

void NumberedTextureImpl::_ready()
{
    auto btn = get_node<godot::TextureButton>( BTN_WITH_TEXTURE );
    btn->set_disabled( !m_button_is_active );
    btn->set_texture_normal( godot::Ref( &m_button_texture ) );
}

void NumberedTextureImpl::set_amount( int new_amount )
{
    auto label = get_node<godot::Label>( AMOUNT );
    label->set_text( std::to_string( new_amount ).data() );
    if ( m_hide_on_zero && new_amount == 0 )
    {
        hide();
    }
}

void NumberedTextureImpl::on_btn_pressed()
{
    emit_signal( signals::TEXTURE_ACTIVATED );
}

}
