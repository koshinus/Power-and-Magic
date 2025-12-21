#pragma once

#include <godot_cpp/classes/control.hpp>

namespace pwm
{

class CombatInterfaceImpl: public godot::Control
{
    GDCLASS( CombatInterfaceImpl, godot::Control )
private:
protected:
    static void _bind_methods();
public:
    CombatInterfaceImpl();
    ~CombatInterfaceImpl() override;
};

}
