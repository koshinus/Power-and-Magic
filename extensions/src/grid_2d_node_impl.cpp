// This script draw grid on tilemap/tilemaplayer
// To use it you should lead following struct:
// -RootNode
// --LayerNode
// --Grid2DNode

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
    // ADD_PROPERTY(godot::PropertyInfo(godot::Variant::INT, "map_width"), "set_map_width", "get_map_width");
    // ADD_PROPERTY(godot::PropertyInfo(godot::Variant::INT, "map_height"), "set_map_height", "get_map_height");
    // ADD_PROPERTY(godot::PropertyInfo(godot::Variant::VECTOR2I, "tile_size"), "set_tile_size", "get_tile_size");
    // ADD_PROPERTY(godot::PropertyInfo(godot::Variant::COLOR, "grid_color"), "set_grid_color", "get_grid_color");

    PwmProperty<int>::bind<Grid2dNodeImpl>( MAP_WIDTH, &Grid2dNodeImpl::get_map_width,
                                           &Grid2dNodeImpl::set_map_width );
    PwmProperty<int>::bind<Grid2dNodeImpl>( MAP_HEIGHT, &Grid2dNodeImpl::get_map_height,
                                           &Grid2dNodeImpl::set_map_height );
    PwmProperty<godot::Vector2i>::bind<Grid2dNodeImpl>( PX_TILE_SIZE, &Grid2dNodeImpl::get_tile_size,
                                           &Grid2dNodeImpl::set_tile_size );
    PwmProperty<godot::Color>::bind<Grid2dNodeImpl>( GRID_COLOR, &Grid2dNodeImpl::get_grid_color,
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
    for ( int y = 0; y < m_map_height.val+1; y++ )
    {
        draw_line( godot::Vector2( 0, y * m_tile_size.val.y ),
                   godot::Vector2( m_map_width.val * m_tile_size.val.x, y * m_tile_size.val.y ),
                   m_grid_color.val );
    }
    for ( int x = 0; x < m_map_width.val+1; x++ )
    {
        draw_line( godot::Vector2( x * m_tile_size.val.x, 0 ),
                   godot::Vector2( x * m_tile_size.val.x, m_map_height.val * m_tile_size.val.y ),
                   m_grid_color.val );
    }
}

int Grid2dNodeImpl::get_map_width()
{
    return m_map_width.val;
}

int Grid2dNodeImpl::get_map_height()
{
    return m_map_height.val;
}

godot::Vector2i Grid2dNodeImpl::get_tile_size()
{
    return m_tile_size.val;
}

godot::Color Grid2dNodeImpl::get_grid_color()
{
    return m_grid_color.val;
}

void Grid2dNodeImpl::set_map_width( const int val )
{
    m_map_width.val = val;
}

void Grid2dNodeImpl::set_map_height( const int val )
{
    m_map_height.val = val;
}

void Grid2dNodeImpl::set_tile_size( const godot::Vector2i val )
{
    m_tile_size.val = val;
}

void Grid2dNodeImpl::set_grid_color( const godot::Color val )
{
    m_grid_color.val = val;
}

}
