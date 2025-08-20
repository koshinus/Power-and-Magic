#pragma once

#include <godot_cpp/classes/node.hpp>

namespace pwm
{

class SkillWheelImpl: public godot::Node
{
    GDCLASS( SkillWheelImpl, godot::Node )
private:
protected:
    static void _bind_methods();
public:
    SkillWheelImpl();
    ~SkillWheelImpl();
};

}
