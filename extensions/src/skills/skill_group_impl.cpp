#include <algorithm>

#include "../utils/pwm_bindings.hpp"

#include "skill_group_impl.hpp"

namespace pwm
{

constinit auto GROUP_NUM = pwm::string_view{ "group_num" };
constinit auto ADVANCED_THRESHOLD = pwm::string_view{ "advanced_threshold" };
constinit auto EXPERT_THRESHOLD = pwm::string_view{ "expert_threshold" };

constinit auto SKILL_ACTIVATED = pwm::string_view{ "skill_activated" };
constinit auto ON_SKILL_ACTIVATED = pwm::string_view{ "on_skill_activated" };

SkillGroupImpl::SkillGroupImpl()
    : godot::Node()
    , m_group_num( 0 )
    , m_advanced_threshold( 2 )
    , m_expert_threshold( 4 )
{
}

SkillGroupImpl::~SkillGroupImpl()
{
}

void SkillGroupImpl::_bind_methods()
{
    using bh = BindHelper<SkillGroupImpl>;

    bh::method( ON_SKILL_ACTIVATED, &SkillGroupImpl::on_skill_activated,
                    godot::Variant(), godot::Variant(), godot::Variant() );
    
    bh::property<int>( GROUP_NUM, &SkillGroupImpl::get_group_num,
                                  &SkillGroupImpl::set_group_num );
    bh::property<int>( ADVANCED_THRESHOLD, &SkillGroupImpl::get_advanced_threshold,
                                           &SkillGroupImpl::set_advanced_threshold );
    bh::property<int>( EXPERT_THRESHOLD, &SkillGroupImpl::get_expert_threshold,
                                         &SkillGroupImpl::set_expert_threshold );
}

void SkillGroupImpl::setup_group( SkillLevel* beginer, SkillLevel* advanced,
                SkillLevel* expert, const std::map<int, bool>& skills_dict )
{
    if ( !skills_dict.contains( m_group_num ) )
    {
        return;
    }
    beginers_lvl = beginer;
    for ( auto b : beginers_lvl->buttons ) b->connect( SKILL_ACTIVATED, godot::Callable{ this, ON_SKILL_ACTIVATED } );
    advanced_lvl = advanced;
    for ( auto b : advanced_lvl->buttons ) b->connect( SKILL_ACTIVATED, godot::Callable{ this, ON_SKILL_ACTIVATED } );
    expert_lvl = expert;
    for ( auto b : expert_lvl->buttons ) b->connect( SKILL_ACTIVATED, godot::Callable{ this, ON_SKILL_ACTIVATED } );
    m_activated_num = std::count_if( skills_dict.begin(), skills_dict.end(), []( auto& relation ){ return relation.second; } );
}

void SkillGroupImpl::recal_lvl_state( SkillLevel* lvl, int before, int after, int threshold )
{
    if ( ( before >= threshold && after >= threshold ) ||
         ( before < threshold && after < threshold ) )
        return;
    if ( before >= threshold && after < threshold )
    {
        lvl->activate_lvl( false );
        return;
    }
    if ( before < threshold && after >= threshold )
    {
        lvl->activate_lvl( true );
        return;
    }
}

// We should activate level just after achieving some threshold
void SkillGroupImpl::recalculate_lvls_state( int before, int after )
{
    recal_lvl_state( beginers_lvl, before, after, 0 );
    recal_lvl_state( advanced_lvl, before, after, m_advanced_threshold );
    recal_lvl_state( expert_lvl, before, after, m_expert_threshold );
}

void SkillGroupImpl::on_skill_activated( godot::Variant toggled, godot::Variant, godot::Variant )
{
    int new_activated = m_activated_num;
    if ( toggled.booleanize() ) { new_activated = new_activated + 1; }
    else { new_activated = std::max( new_activated - 1, 0 ); }
    recalculate_lvls_state( m_activated_num, new_activated );
    m_activated_num = new_activated;
}

}
