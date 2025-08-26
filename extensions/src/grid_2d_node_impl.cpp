// This script draw grid on tilemap/tilemaplayer
// To use it you should lead following struct:
// -RootNode
// --LayerNode
// --Grid2DNode

#include "utils/pwm_properties.hpp"

#include "grid_2d_node_impl.hpp"

namespace pwm
{

constexpr auto MAP_WIDTH = pwm::string_view{ "map_width" };
constexpr auto MAP_HEIGHT = pwm::string_view{ "map_height" };
constexpr auto PX_TILE_SIZE = pwm::string_view{ "tile_size" };
constexpr auto GRID_COLOR = pwm::string_view{ "grid_color" };

Grid2dNodeImpl::Grid2dNodeImpl()
    : m_map_width( 32 )
    , m_map_height( 32 )
    , m_tile_size( godot::Vector2i( 32, 32 ) )
    , m_grid_color( godot::Color::hex( 0xFFFFFFFF ) ) // white color
{
}

Grid2dNodeImpl::~Grid2dNodeImpl()
{
}

void Grid2dNodeImpl::_bind_methods()
{
    BindHelper<Grid2dNodeImpl>::property<int>( MAP_WIDTH,
                                           &Grid2dNodeImpl::get_map_width,
                                           &Grid2dNodeImpl::set_map_width );
    BindHelper<Grid2dNodeImpl>::property<int>( MAP_HEIGHT,
                                           &Grid2dNodeImpl::get_map_height,
                                           &Grid2dNodeImpl::set_map_height );
    BindHelper<Grid2dNodeImpl>::property<godot::Vector2i>( PX_TILE_SIZE,
                                           &Grid2dNodeImpl::get_tile_size,
                                           &Grid2dNodeImpl::set_tile_size );
    BindHelper<Grid2dNodeImpl>::property<godot::Color>( GRID_COLOR,
                                           &Grid2dNodeImpl::get_grid_color,
                                           &Grid2dNodeImpl::set_grid_color );
}

void Grid2dNodeImpl::_ready()
{
    set_process( true );
}
    
void Grid2dNodeImpl::_process(double)
{
    queue_redraw();
}

void Grid2dNodeImpl::_draw()
{
    for ( int y = 0; y < m_map_height+1; y++ )
    {
        draw_line( godot::Vector2( 0, y * m_tile_size.y ),
                   godot::Vector2( m_map_width * m_tile_size.x, y * m_tile_size.y ),
                   m_grid_color );
    }
    for ( int x = 0; x < m_map_width+1; x++ )
    {
        draw_line( godot::Vector2( x * m_tile_size.x, 0 ),
                   godot::Vector2( x * m_tile_size.x, m_map_height * m_tile_size.y ),
                   m_grid_color );
    }
}

}
