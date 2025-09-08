#pragma once

#include <vector>
#include <map>

#include <godot_cpp/classes/node.hpp>

#include "skill_button_impl.hpp"

namespace pwm
{

struct SkillLevel
{
    std::vector<SkillButtonImpl*> buttons;

    void activate_lvl( bool enable )
    {
        for ( auto b : buttons )
            b->enable_button( enable );
    }
};


class SkillGroupImpl: public godot::Node
{
    GDCLASS( SkillGroupImpl, godot::Node )
public:
    SkillGroupImpl();
    ~SkillGroupImpl();
    void on_skill_activated( godot::Variant toggled, godot::Variant num, godot::Variant group );
    void setup_group( SkillLevel* beginer, SkillLevel* advanced, SkillLevel* expert,
                     const std::map<int, bool>& skills_dict );

    int get_group_num() const { return m_group_num; }
    void set_group_num( const int val ) { m_group_num = val; }
    int get_advanced_threshold() const { return m_advanced_threshold; }
    void set_advanced_threshold( const int val ) { m_advanced_threshold = val; }
    int get_expert_threshold() const { return m_expert_threshold; }
    void set_expert_threshold( const int val ) { m_expert_threshold = val; }
protected:
    static void _bind_methods();
private:
    void recalculate_lvls_state( int before, int after );
    void recal_lvl_state( SkillLevel* lvl, int before, int after, int threshold );

    SkillLevel* beginers_lvl;
    SkillLevel* advanced_lvl;
    SkillLevel* expert_lvl;

    int m_activated_num;

    int m_group_num;
    int m_advanced_threshold;
    int m_expert_threshold;
};

}
