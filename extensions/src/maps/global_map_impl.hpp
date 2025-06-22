#pragma once

#include <godot_cpp/classes/node.hpp>

namespace pwm
{

class GlobalMapImpl: public godot::Node
{
    GDCLASS( GlobalMapImpl, godot::Node )
private:
protected:
    static void _bind_methods();
public:
    GlobalMapImpl();
    ~GlobalMapImpl();
};

}
