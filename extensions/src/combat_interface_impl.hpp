#pragma once

#include <godot_cpp/classes/node.hpp>

namespace pwm
{

class CombatInterfaceImpl: public godot::Node
{
    GDCLASS( CombatInterfaceImpl, godot::Node )
private:
protected:
    static void _bind_methods();
public:
    CombatInterfaceImpl();
    ~CombatInterfaceImpl();
};

}
