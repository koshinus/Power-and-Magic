// Tool for setting border limitations of the map

#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/rectangle_shape2d.hpp>

#include "map_limitations_impl.hpp"

namespace pwm
{

constexpr auto TOP_LIMIT = pwm::string_view{ "top_limit" };
constexpr auto BOTTOM_LIMIT = pwm::string_view{ "bottom_limit" };
constexpr auto LEFT_LIMIT = pwm::string_view{ "left_limit" };
constexpr auto RIGHT_LIMIT = pwm::string_view{ "right_limit" };

void MapLimitationsImpl::_bind_methods()
{
}

MapLimitationsImpl::MapLimitationsImpl()
    : m_tile_size( godot::Vector2i( 0, 0 ) )
    , m_map_width( 0 )
    , m_map_height( 0 )
{
}

MapLimitationsImpl::~MapLimitationsImpl()
{
}

void MapLimitationsImpl::setup_limits( godot::CollisionShape2D* limit_side,
                                       godot::Vector2i limit_size, godot::Vector2i limit_pos )
{
    auto cur_limits = memnew( godot::RectangleShape2D );
    cur_limits->set_size( limit_size );
    limit_side->set_shape( cur_limits );
    limit_side->set_position( limit_pos );
}

void MapLimitationsImpl::_ready()
{
    setup_limits( get_node<godot::CollisionShape2D>( TOP_LIMIT ),
                godot::Vector2i( m_map_width.val * m_tile_size.val.x, 1 ),
                godot::Vector2i( ( m_map_width.val * m_tile_size.val.x )/2, 0 ) );
    setup_limits( get_node<godot::CollisionShape2D>( BOTTOM_LIMIT ),
                godot::Vector2i( m_map_width.val * m_tile_size.val.x, 1 ),
                godot::Vector2i( ( m_map_width.val * m_tile_size.val.x )/2, m_map_height.val * m_tile_size.val.y ) );
    setup_limits( get_node<godot::CollisionShape2D>( LEFT_LIMIT ),
                godot::Vector2i( 1, m_map_height.val * m_tile_size.val.y ),
                godot::Vector2i( 0, ( m_map_height.val * m_tile_size.val.y )/2 ) );
    setup_limits( get_node<godot::CollisionShape2D>( RIGHT_LIMIT ),
                godot::Vector2i( 1, m_map_height.val * m_tile_size.val.y ),
                godot::Vector2i( m_map_width.val * m_tile_size.val.x, ( m_map_height.val * m_tile_size.val.y )/2 ) );
}

}
