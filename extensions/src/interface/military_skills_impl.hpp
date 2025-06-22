#pragma once

#include <godot_cpp/classes/node.hpp>

namespace pwm
{

class MilitarySkillsImpl: public godot::Node
{
    GDCLASS( MilitarySkillsImpl, godot::Node )
private:
protected:
    static void _bind_methods();
public:
    MilitarySkillsImpl();
    ~MilitarySkillsImpl();
};

}
