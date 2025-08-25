#include "../utils/pwm_properties.hpp"

#include "skill_group_impl.hpp"

namespace pwm
{

constexpr auto GROUP_NUM = pwm::string_view{ "group_num" };
constexpr auto ADVANCED_THRESHOLD = pwm::string_view{ "advanced_threshold" };
constexpr auto EXPERT_THRESHOLD = pwm::string_view{ "expert_threshold" };

constexpr auto SKILL_ACTIVATED = pwm::string_view{ "skill_activated" };

// var beginers_lvl: SkillLevel
// var advanced_lvl: SkillLevel
// var expert_lvl: SkillLevel
// var _activated_num : int = 0

SkillGroupImpl::SkillGroupImpl()
    : m_group_num( 0 )
    , m_advanced_threshold( 2 )
    , m_expert_threshold( 4 )
{
}

SkillGroupImpl::~SkillGroupImpl()
{
}

void SkillGroupImpl::_bind_methods()
{
    // BindHelper::property<SkillGroupImpl>( GROUP_NUM,
    //                                        &SkillGroupImpl::get_group_num,
    //                                        &SkillGroupImpl::set_group_num );
    // BindHelper::property<SkillGroupImpl>( ADVANCED_THRESHOLD,
    //                                        &SkillGroupImpl::get_advanced_threshold,
    //                                        &SkillGroupImpl::set_advanced_threshold );
    // BindHelper::property<SkillGroupImpl>( EXPERT_THRESHOLD,
    //                                        &SkillGroupImpl::get_expert_threshold,
    //                                        &SkillGroupImpl::set_expert_threshold );
}

void SkillGroupImpl::setup_group( SkillLevel* beginer, SkillLevel* advanced,
                SkillLevel* expert, const std::map<int, bool>& skills_dict )
{
    // TODO: FIND A WAY TO CREATE godot::Callable from methods!
    beginers_lvl = beginer;
    // for ( auto b : beginers_lvl->buttons ) b->connect( SKILL_ACTIVATED, &SkillGroupImpl::on_skill_activated );
    advanced_lvl = advanced;
    // for ( auto b : advanced_lvl->buttons ) b->connect( SKILL_ACTIVATED, &SkillGroupImpl::on_skill_activated );
    expert_lvl = expert;
    // for ( auto b : expert_lvl->buttons ) b->connect( SKILL_ACTIVATED, &SkillGroupImpl::on_skill_activated );
    // TODO: WTF is going on here????
 //    auto group_skills = skills_dict.get( group_num )
    // if group_skills == null:
    // 	return
 //    activated_num = group_skills.values().reduce( func( accum, number ): return accum + number, 0 );
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

void SkillGroupImpl::on_skill_activated( bool toggled, int num, int group )
{
    int new_activated = activated_num;
    if ( toggled ) { new_activated = new_activated + 1; }
    else { new_activated = std::max( new_activated - 1, 0 ); }
    recalculate_lvls_state( activated_num, new_activated );
    activated_num = new_activated;
}

}
