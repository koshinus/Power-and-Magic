// This script draw grid on tilemap/tilemaplayer
// To use it you should lead following struct:
// -RootNode
// --LayerNode
// --Grid2DNode

#include "utils/pwm_constants.hpp"
#include "utils/pwm_bindings.hpp"

#include "grid_2d_node_impl.hpp"

namespace pwm
{

constinit auto GRID_SIZE = pwm::string_view{ "grid_size" };
constinit auto GRID_TILE_SIZE = pwm::string_view{ "grid_tile_size" };
constinit auto GRID_COLOR = pwm::string_view{ "grid_color" };

Grid2dNodeImpl::Grid2dNodeImpl()
    : m_grid_size( godot::Vector2i( 32, 32 ) )
    , m_grid_tile_size( godot::Vector2i( 32, 32 ) )
    , m_grid_color( colors::WHITE )
{
}

Grid2dNodeImpl::~Grid2dNodeImpl()
{
}

void Grid2dNodeImpl::_bind_methods()
{
    using bh = BindHelper<Grid2dNodeImpl>;
    bh::property<godot::Vector2i>( GRID_SIZE, &Grid2dNodeImpl::get_grid_size,
                                             &Grid2dNodeImpl::set_grid_size );
    bh::property<godot::Vector2i>( GRID_TILE_SIZE, &Grid2dNodeImpl::get_grid_tile_size,
                                                 &Grid2dNodeImpl::set_grid_tile_size );
    bh::property<godot::Color>( GRID_COLOR, &Grid2dNodeImpl::get_grid_color,
                                            &Grid2dNodeImpl::set_grid_color );
}

void Grid2dNodeImpl::_ready()
{
    set_process( true );
}
    
void Grid2dNodeImpl::_process( double )
{
    queue_redraw();
}

void Grid2dNodeImpl::_draw()
{
    for ( int y = 0; y < m_grid_size.height + 1; y++ )
    {
        draw_line( godot::Vector2( 0, y * m_grid_tile_size.y ),
                   godot::Vector2( m_grid_size.width * m_grid_tile_size.x, y * m_grid_tile_size.y ),
                   m_grid_color );
    }
    for ( int x = 0; x < m_grid_size.width + 1; x++ )
    {
        draw_line( godot::Vector2( x * m_grid_tile_size.x, 0 ),
                   godot::Vector2( x * m_grid_tile_size.x, m_grid_size.height * m_grid_tile_size.y ),
                   m_grid_color );
    }
}

}
