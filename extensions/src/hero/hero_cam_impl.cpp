#include "../utils/world_constants.hpp"

#include "hero_cam_impl.hpp"
//extends Camera2D

namespace pwm
{

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

}

void HeroCameraImpl::set_px_tile_size( const int val )
{
    m_px_tile_size.val = val;
}

void HeroCameraImpl::set_layer_width( const int val )
{
    m_layer_width.val = val;
}

void HeroCameraImpl::set_layer_height( const int val )
{
    m_layer_height.val = val;
}

int HeroCameraImpl::get_px_tile_size()
{
    return m_px_tile_size.val;
}

int HeroCameraImpl::get_layer_width()
{
    return m_layer_width.val;
}

int HeroCameraImpl::get_layer_height()
{
    return m_layer_height.val;
}

// Called when the node enters the scene tree for the first time.
void HeroCameraImpl::_ready()
{
    set_limit( godot::SIDE_LEFT, 0 );
    set_limit( godot::SIDE_TOP, 0 );
    set_limit( godot::SIDE_RIGHT, m_layer_width.val * m_px_tile_size.val );
    set_limit( godot::SIDE_BOTTOM, m_layer_height.val * m_px_tile_size.val );
}

}
