#include "utils/pwm_properties.hpp"
#include "utils/pwm_string_view.hpp"
// #include "maps/local_level_impl.hpp"
#include "global_interface_impl.hpp"
#include "hero/hero_scene_impl.hpp"
#include "maps/global_map_impl.hpp"
#include "utils/world_generator_impl.hpp"

#include "global_level_impl.hpp"

namespace pwm
{

constexpr auto ON_HERO_SELECTED = pwm::string_view{ "on_hero_selected" };
constexpr auto ON_VIEW_CHANGED = pwm::string_view{ "on_view_changed" };

constexpr auto GLOBAL_INTERFACE = pwm::string_view{ "GlobalInterface" };
constexpr auto GLOBAL_MAP = pwm::string_view{ "GlobalMap" };
constexpr auto MILITARY_HERO = pwm::string_view{ "MilitaryHero" };
constexpr auto ECONOMIC_HERO = pwm::string_view{ "EconomicHero" };

namespace signals
{
constexpr auto HERO_SELECTED = pwm::string_view{ "hero_selected" };
constexpr auto VIEW_CHANGED = pwm::string_view{ "view_changed" };
}


GlobalLevelImpl::GlobalLevelImpl()
    : m_grid_pos( godot::Vector2i( 0, 0 ) )
{
}

GlobalLevelImpl::~GlobalLevelImpl()
{
}

void GlobalLevelImpl::_bind_methods()
{
    using bh = BindHelper<GlobalLevelImpl>;

    // TODO: find a way to add custom types to godot variant types
    // godot::ClassDB::bind_method( godot::D_METHOD( ON_HERO_SELECTED ), &GlobalLevelImpl::on_hero_selected );
    bh::method( ON_VIEW_CHANGED, &GlobalLevelImpl::on_view_changed );
}


// var lvl_window : LocalLevel

void GlobalLevelImpl::_ready()
{
//     lvl_window = preload( "res://scenes/maps/local_level.tscn" ).instantiate()
//     lvl_window.hide()
    
    auto world_info = WorldGenerator::generate();
    auto military_hero = get_node<HeroSceneImpl>( MILITARY_HERO );
    auto economic_hero = get_node<HeroSceneImpl>( ECONOMIC_HERO );
    auto global_map = get_node<GlobalMapImpl>( GLOBAL_MAP );
    global_map->set_based_on_generated( world_info );
    military_hero->set_tilemap_layer( global_map->get_surface(), world_info.global_tiles_values );
    economic_hero->set_tilemap_layer( global_map->get_surface(), world_info.global_tiles_values );
    // TODO: find a way to connect custom types to godot variant types
    // military_hero->connect( signals::HERO_SELECTED, godot::Callable{ this, ON_HERO_SELECTED } );
    // economic_hero->connect( signals::HERO_SELECTED, godot::Callable{ this, ON_HERO_SELECTED } );
    get_node<GlobalInterfaceImpl>( GLOBAL_INTERFACE )->connect( signals::VIEW_CHANGED, godot::Callable{ this, ON_VIEW_CHANGED } );
}

void GlobalLevelImpl::on_hero_selected( std::optional<HeroInfo> info )
{
    m_grid_pos = godot::Vector2i( 0, 0 );
    if ( info.has_value() )
    {
        m_grid_pos = info->grid_pos;
        godot::print_line( "Info spec: ", int( info->specialization ) );
    }
    get_node<GlobalInterfaceImpl>( GLOBAL_INTERFACE )->show_hero_depending_parts( info );
}

void GlobalLevelImpl::on_view_changed()
{
    if ( m_grid_pos == godot::Vector2i( 0, 0 ) )
        return;
//     //lvl_window.
//     //lvl_window.visible = not lvl_window.visible
}

}
