#pragma once

#include <godot_cpp/classes/node.hpp>

namespace pwm
{

class UnitStatsImpl: public godot::Node
{
    GDCLASS( UnitStatsImpl, godot::Node )
private:
protected:
    static void _bind_methods();
public:
    UnitStatsImpl();
    ~UnitStatsImpl();
};

}
