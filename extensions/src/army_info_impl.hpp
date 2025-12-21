#pragma once

#include <godot_cpp/classes/control.hpp>

namespace pwm
{

class ArmyInfoImpl: public godot::Control
{
    GDCLASS( ArmyInfoImpl, godot::Control )
private:
protected:
    static void _bind_methods();
public:
    ArmyInfoImpl();
    ~ArmyInfoImpl() override;
};

}
