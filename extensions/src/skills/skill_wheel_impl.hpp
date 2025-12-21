#pragma once

#include <godot_cpp/classes/control.hpp>

namespace pwm
{

class SkillWheelImpl: public godot::Control
{
    GDCLASS( SkillWheelImpl, godot::Control )
public:
    SkillWheelImpl();
    ~SkillWheelImpl() override;
protected:
    static void _bind_methods();
private:
};

}
