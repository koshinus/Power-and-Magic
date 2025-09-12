#include "../utils/world_constants.hpp"
#include "../utils/pwm_bindings.hpp"

#include "hero_cam_impl.hpp"

namespace pwm
{

constinit auto LAYER_WIDTH = pwm::string_view{ "layer_width" };
constinit auto LAYER_HEIGHT = pwm::string_view{ "layer_height" };
constinit auto LAYER_TILE_SIZE = pwm::string_view{ "tile_size" };

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
    using bh = BindHelper<HeroCameraImpl>;
    bh::property<int>( LAYER_TILE_SIZE, &HeroCameraImpl::get_px_tile_size,
                                        &HeroCameraImpl::set_px_tile_size );
    bh::property<int>( LAYER_WIDTH, &HeroCameraImpl::get_layer_width,
                                    &HeroCameraImpl::set_layer_width );
    bh::property<int>( LAYER_HEIGHT, &HeroCameraImpl::get_layer_height,
                                     &HeroCameraImpl::set_layer_height );
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
