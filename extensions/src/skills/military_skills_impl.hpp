#pragma once

#include <godot_cpp/classes/control.hpp>

namespace pwm
{

class MilitarySkillsImpl: public godot::Control
{
    GDCLASS( MilitarySkillsImpl, godot::Control )
private:
protected:
    static void _bind_methods();
public:
    MilitarySkillsImpl();
    ~MilitarySkillsImpl();
};

}
