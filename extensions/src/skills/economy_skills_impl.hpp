#pragma once

#include <godot_cpp/classes/control.hpp>

namespace pwm
{

class EconomySkillsImpl: public godot::Control
{
    GDCLASS( EconomySkillsImpl, godot::Control )
private:
protected:
    static void _bind_methods();
public:
    EconomySkillsImpl();
    ~EconomySkillsImpl() override;
};

}
