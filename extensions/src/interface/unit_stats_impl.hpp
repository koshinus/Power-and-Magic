#pragma once

#include <godot_cpp/classes/control.hpp>

namespace pwm
{

class UnitStatsImpl: public godot::Control
{
    GDCLASS( UnitStatsImpl, godot::Control )
public:
    UnitStatsImpl();
    ~UnitStatsImpl() override;
protected:
    static void _bind_methods();
private:
};

}
