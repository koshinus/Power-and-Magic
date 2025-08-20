#pragma once

#include <godot_cpp/classes/node.hpp>

namespace pwm
{

class EconomySkillsImpl: public godot::Node
{
    GDCLASS( EconomySkillsImpl, godot::Node )
private:
protected:
    static void _bind_methods();
public:
    EconomySkillsImpl();
    ~EconomySkillsImpl();
};

}
