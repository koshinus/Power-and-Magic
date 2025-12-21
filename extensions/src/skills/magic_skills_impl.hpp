#pragma once

#include <godot_cpp/classes/control.hpp>

namespace pwm
{

class MagicSkillsImpl: public godot::Control
{
    GDCLASS( MagicSkillsImpl, godot::Control )
private:
protected:
    static void _bind_methods();
public:
    MagicSkillsImpl();
    ~MagicSkillsImpl() override;
};

}
