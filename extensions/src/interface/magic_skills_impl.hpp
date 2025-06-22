#pragma once

#include <godot_cpp/classes/node.hpp>

namespace pwm
{

class MagicSkillsImpl: public godot::Node
{
    GDCLASS( MagicSkillsImpl, godot::Node )
private:
protected:
    static void _bind_methods();
public:
    MagicSkillsImpl();
    ~MagicSkillsImpl();
};

}
