#include <godot_cpp/classes/a_star_grid2d.hpp>
#include <godot_cpp/classes/tile_map_layer.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/camera2d.hpp>

#include "../utils/world_constants.hpp"
#include "../utils/grid_movement_impl.hpp"
#include "../utils/pwm_properties.hpp"

#include "hero_scene_impl.hpp"

namespace pwm
{

const godot::Vector2 VECTOR_MINUS_ONE = godot::Vector2( -1,-1 );
constexpr const double speed = 300.0;
constexpr const int DISTANSE_TO_START_MOVE = 3;

constexpr auto START_POS = pwm::string_view{ "start_pos" };
constexpr auto HERO_INFO = pwm::string_view{ "info" };
constexpr auto SELECTED = pwm::string_view{ "selection_flag" };
constexpr auto HERO_CAM = pwm::string_view{ "HeroCam" };

namespace signals
{
constexpr auto HERO_SELECTED = pwm::string_view{ "hero_selected" };
}

HeroSceneImpl::HeroSceneImpl()
    : m_start_pos( GLOBAL_TILE_SIZE_IN_PIXELS/2 )
    , m_is_selected( false )
    , m_astar_grid_2d( nullptr )
    , m_astar_path( godot::TypedArray<godot::Vector2i>() )
    , m_tml_ref( nullptr )
{
}

HeroSceneImpl::~HeroSceneImpl()
{
}

void HeroSceneImpl::_bind_methods()
{
    BindHelper::property<HeroSceneImpl>( START_POS,
                                          &HeroSceneImpl::get_start_pos,
                                          &HeroSceneImpl::set_start_pos );
    godot::ClassDB::add_signal( get_class_static(),
                                godot::MethodInfo{ signals::HERO_SELECTED,
                                                   godot::PropertyInfo{ godot::Variant::BOOL, SELECTED } } );
}

void HeroSceneImpl::_ready()
{
    set_position( godot::Vector2i( m_start_pos, m_start_pos ) );
    m_click_pos = get_position();
}

void HeroSceneImpl::_physics_process( double delta )
{
    if ( !m_is_selected )
    {
        return;
    }
    auto target_pos = VECTOR_MINUS_ONE;
    auto position = get_position();
    if ( m_astar_grid_2d == nullptr )
    {
        target_pos = process_row( position );
    }
    else
    {
        target_pos = process_astar( position );
        if ( target_pos == VECTOR_MINUS_ONE )
        {
            return;
        }
        set_velocity( target_pos * speed );
        move_and_slide();
    }
}

void HeroSceneImpl::set_tilemap_layer( godot::TileMapLayer* tml, const GlobalTypesMap& global_tiles_vals )
{
    m_tml_ref = tml;
    auto tsize = godot::Vector2i( 1, 1 ) * GLOBAL_TILE_SIZE_IN_PIXELS;
    m_astar_grid_2d = GridMovement::create_astar( tml, global_tiles_vals, HeroInfo{}, tsize );
}

godot::Vector2 HeroSceneImpl::process_row( godot::Vector2 cur_pos )
{
    auto tsize = godot::Vector2i( 1, 1 ) * GLOBAL_TILE_SIZE_IN_PIXELS;
    auto pos_grid = GridMovement::calculate_grid( cur_pos, tsize );
    auto click_grid = GridMovement::calculate_grid( m_click_pos, tsize );
    if ( godot::Input::get_singleton()->is_action_just_pressed( "left_click" ) )
    {
        m_click_pos = GridMovement::calculate_grid_coords( get_global_mouse_position(), tsize );
        click_grid = GridMovement::calculate_grid( m_click_pos, tsize );
        godot::print_line( "Click grid: ", click_grid, " pos grid: ", pos_grid);
        if ( click_grid == pos_grid )
            return VECTOR_MINUS_ONE;
    }
    if ( cur_pos.distance_to( m_click_pos ) <= DISTANSE_TO_START_MOVE )
        return VECTOR_MINUS_ONE;
    return ( godot::Vector2( m_click_pos ) - cur_pos ).normalized();
}

godot::Vector2 HeroSceneImpl::process_astar( godot::Vector2 cur_pos )
{
    auto tsize = godot::Vector2i(1, 1)*GLOBAL_TILE_SIZE_IN_PIXELS;
    auto pos_grid = GridMovement::calculate_grid( cur_pos, tsize );
    bool is_left_click_pressed = godot::Input::get_singleton()->is_action_just_pressed( "left_click" );
    if ( is_left_click_pressed )
    {
        if ( !m_astar_path.is_empty() )
        {
            // ignoring left click while moving to the target position
            // TODO: in the future, there can be some more specific reaction
            // for example, stop current movement and recalculate path
            return VECTOR_MINUS_ONE;
        }
        m_click_pos = GridMovement::calculate_grid_coords( get_global_mouse_position(), tsize );
        auto click_grid = GridMovement::calculate_grid( m_click_pos, tsize );
        if ( click_grid == pos_grid )
        {
            return VECTOR_MINUS_ONE;
        }
        m_astar_path = GridMovement::get_grid_path( m_astar_grid_2d, pos_grid, click_grid );
        godot::print_line( "Result path: ", m_astar_path, " clicked grid ", click_grid );
    }
    if ( m_astar_path.is_empty() )
    {
        return VECTOR_MINUS_ONE;
    }
    auto next_grid_center = GridMovement::calculate_grid_coords( godot::Vector2i( m_astar_path.front() )*tsize, tsize );
    if ( cur_pos.distance_to( next_grid_center ) <= DISTANSE_TO_START_MOVE )
    {
        m_astar_path.pop_front();
        return VECTOR_MINUS_ONE;
    }
    return ( godot::Vector2( next_grid_center ) - cur_pos ).normalized();
}

void HeroSceneImpl::on_hero_selected( bool selection_flag )
{
    m_is_selected = selection_flag;
    get_node<godot::Camera2D>( HERO_CAM )->set_enabled( selection_flag );
    if ( !m_is_selected )
    {
        m_click_pos = get_position();
        // TODO: it should be null actually!
        // emit_signal( signals::HERO_SELECTED, HeroInfo{} );
        return;
    }
    // emit_signal( signals::HERO_SELECTED, HeroInfo{} );
}

}
