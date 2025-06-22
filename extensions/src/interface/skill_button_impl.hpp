#pragma once

#include <godot_cpp/classes/node.hpp>

namespace pwm
{

class SkillButtonImpl: public godot::Node
{
    GDCLASS( SkillButtonImpl, godot::Node )
private:
protected:
    static void _bind_methods();
public:
    SkillButtonImpl();
    ~SkillButtonImpl();
};

}
