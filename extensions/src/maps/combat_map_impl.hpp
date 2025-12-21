#pragma once

#include <godot_cpp/classes/node2d.hpp>

namespace pwm
{

class CombatMapImpl: public godot::Node2D
{
    GDCLASS( CombatMapImpl, godot::Node2D )
public:
    CombatMapImpl();
    ~CombatMapImpl() override;
protected:
    static void _bind_methods();
private:
};

}
