#include "../utils/world_constants.hpp"
#include "../utils/pwm_properties.hpp"

#include "hero_cam_impl.hpp"

namespace pwm
{

constexpr auto LAYER_WIDTH = pwm::string_view{ "layer_width" };
constexpr auto LAYER_HEIGHT = pwm::string_view{ "layer_height" };
constexpr auto PX_TILE_SIZE = pwm::string_view{ "tile_size" };

HeroCameraImpl::HeroCameraImpl()
    : m_px_tile_size( GLOBAL_TILE_SIZE_IN_PIXELS )
    , m_layer_width( GLOBAL_MAP_WIDTH )
    , m_layer_height( GLOBAL_MAP_HEIGHT )
{

}

HeroCameraImpl::~HeroCameraImpl()
{
}

void HeroCameraImpl::_bind_methods()
{
    // BindHelper::property<HeroCameraImpl>( PX_TILE_SIZE,
    //                                      &HeroCameraImpl::get_px_tile_size,
    //                                      &HeroCameraImpl::set_px_tile_size );
    // BindHelper::property<HeroCameraImpl>( LAYER_WIDTH,
    //                                      &HeroCameraImpl::get_layer_width,
    //                                      &HeroCameraImpl::set_layer_width );
    // BindHelper::property<HeroCameraImpl>( LAYER_HEIGHT,
    //                                      &HeroCameraImpl::get_layer_height,
    //                                      &HeroCameraImpl::set_layer_height );
}

// Called when the node enters the scene tree for the first time.
void HeroCameraImpl::_ready()
{
    set_limit( godot::SIDE_LEFT, 0 );
    set_limit( godot::SIDE_TOP, 0 );
    set_limit( godot::SIDE_RIGHT, m_layer_width * m_px_tile_size );
    set_limit( godot::SIDE_BOTTOM, m_layer_height * m_px_tile_size );
}

}
