// Tool for setting border limitations of the map

#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/rectangle_shape2d.hpp>

#include "../utils/pwm_bindings.hpp"
#include "../utils/pwm_constants.hpp"

#include "map_limitations_impl.hpp"

namespace pwm
{

constinit auto TOP_LIMIT = pwm::string_view{ "top_limit" };
constinit auto BOTTOM_LIMIT = pwm::string_view{ "bottom_limit" };
constinit auto LEFT_LIMIT = pwm::string_view{ "left_limit" };
constinit auto RIGHT_LIMIT = pwm::string_view{ "right_limit" };

constinit auto MAP_SIZE = pwm::string_view{ "map_size" };
constinit auto PX_TILE_SIZE = pwm::string_view{ "tile_size" };

MapLimitationsImpl::MapLimitationsImpl()
    : m_tile_size( vec::ZERO )
    , m_map_size( vec::ZERO )
{
}

MapLimitationsImpl::~MapLimitationsImpl()
{
}

void MapLimitationsImpl::_bind_methods()
{
    using bh = BindHelper<MapLimitationsImpl>;
    bh::property<godot::Vector2i>( MAP_SIZE, &MapLimitationsImpl::get_map_size,
                                             &MapLimitationsImpl::set_map_size );
    bh::property<godot::Vector2i>( PX_TILE_SIZE, &MapLimitationsImpl::get_tile_size,
                                                 &MapLimitationsImpl::set_tile_size );
}

void MapLimitationsImpl::setup_limits( godot::CollisionShape2D* limit_side,
                                       godot::Vector2i limit_size, godot::Vector2i limit_pos )
{
    // TODO: check if it neccessary to remove it manually
    auto cur_limits = memnew( godot::RectangleShape2D );
    cur_limits->set_size( limit_size );
    limit_side->set_shape( cur_limits );
    limit_side->set_position( limit_pos );
}

void MapLimitationsImpl::_ready()
{
    setup_limits( get_node<godot::CollisionShape2D>( TOP_LIMIT ),
                godot::Vector2i( m_map_size.width * m_tile_size.x, 1 ),
                godot::Vector2i( ( m_map_size.width * m_tile_size.x )/2, 0 ) );
    setup_limits( get_node<godot::CollisionShape2D>( BOTTOM_LIMIT ),
                godot::Vector2i( m_map_size.width * m_tile_size.x, 1 ),
                godot::Vector2i( ( m_map_size.width * m_tile_size.x )/2, m_map_size.height * m_tile_size.y ) );
    setup_limits( get_node<godot::CollisionShape2D>( LEFT_LIMIT ),
                godot::Vector2i( 1, m_map_size.height * m_tile_size.y ),
                godot::Vector2i( 0, ( m_map_size.height * m_tile_size.y )/2 ) );
    setup_limits( get_node<godot::CollisionShape2D>( RIGHT_LIMIT ),
                godot::Vector2i( 1, m_map_size.height * m_tile_size.y ),
                godot::Vector2i( m_map_size.width * m_tile_size.x, ( m_map_size.height * m_tile_size.y )/2 ) );
}

}
