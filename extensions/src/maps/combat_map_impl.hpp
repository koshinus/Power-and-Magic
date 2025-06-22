#pragma once

#include <godot_cpp/classes/node.hpp>

namespace pwm
{

class CombatMapImpl: public godot::Node
{
    GDCLASS( CombatMapImpl, godot::Node )
private:
protected:
    static void _bind_methods();
public:
    CombatMapImpl();
    ~CombatMapImpl();
};

}
