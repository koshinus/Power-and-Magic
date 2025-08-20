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
    // SkillGroupImpl( int _group_num, int _advanced_threshold, int _expert_threshold );
    void on_skill_activated( bool toggled, int num, int group );
    void setup_group( SkillLevel* beginer, SkillLevel* advanced, SkillLevel* expert,
                     const std::map<int, bool>& skills_dict );

    int get_group_num();
    void set_group_num( const int val );
    int get_advanced_threshold();
    void set_advanced_threshold( const int val );
    int get_expert_threshold();
    void set_expert_threshold( const int val );
protected:
    static void _bind_methods();
private:
    void recalculate_lvls_state( int before, int after );
    void recal_lvl_state( SkillLevel* lvl, int before, int after, int threshold );

    SkillLevel* beginers_lvl;
    SkillLevel* advanced_lvl;
    SkillLevel* expert_lvl;

    int activated_num;

    PwmProperty<int> m_group_num;
    PwmProperty<int> m_advanced_threshold;
    PwmProperty<int> m_expert_threshold;
    // const int group_num = 0;
    // const int advanced_threshold = 2;
    // const int expert_threshold = 4;
};

}
