#pragma once

#include <godot_cpp/classes/node.hpp>

namespace pwm
{

class ArmyInfoImpl: public godot::Node
{
    GDCLASS( ArmyInfoImpl, godot::Node )
private:
protected:
    static void _bind_methods();
public:
    ArmyInfoImpl();
    ~ArmyInfoImpl();
};

}
