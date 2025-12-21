#include <string>

#include <godot_cpp/classes/texture_button.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/label.hpp>

#include "utils/pwm_string_view.hpp"
#include "utils/pwm_signals.hpp"

#include "numbered_texture_impl.hpp"

namespace pwm
{

constinit auto BTN_WITH_TEXTURE = pwm::string_view{ "VBoxContainer/BtnWithTexture" };
constinit auto AMOUNT = pwm::string_view{ "VBoxContainer/Amount" };

constinit auto BTN_IS_ACTIVE = pwm::string_view{ "button_is_active" };
constinit auto HIDE_ON_ZERO = pwm::string_view{ "hide_on_zero" };
constinit auto BTN_TEXTURE = pwm::string_view{ "button_texture" };

NumberedTextureImpl::NumberedTextureImpl()
    : godot::Control()
    , m_button_texture( godot::Texture2D() )
    , m_hide_on_zero( false )
    , m_button_is_active( true )
{
}

NumberedTextureImpl::~NumberedTextureImpl()
{
}

void NumberedTextureImpl::_bind_methods()
{
    using bh = BindHelper<NumberedTextureImpl>;
    // TODO: godot::ImageTexture is not in Variant type
    // PwmProperty<godot::Texture2D>::bind<NumberedTextureImpl>( BTN_TEXTURE,
    //                                       &NumberedTextureImpl::get_button_texture,
    //                                       &NumberedTextureImpl::set_button_texture );

    bh::property<bool>( BTN_IS_ACTIVE, &NumberedTextureImpl::get_btn_is_active,
                                       &NumberedTextureImpl::set_btn_is_active );

    bh::property<bool>( HIDE_ON_ZERO, &NumberedTextureImpl::get_hide_on_zero,
                                      &NumberedTextureImpl::set_hide_on_zero );

    bh::signal( signals::TEXTURE_ACTIVATED );
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
