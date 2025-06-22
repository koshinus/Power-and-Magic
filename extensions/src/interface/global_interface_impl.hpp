#pragma once

#include <godot_cpp/classes/node.hpp>

namespace pwm
{

class GlobalInterfaceImpl: public godot::Node
{
    GDCLASS( GlobalInterfaceImpl, godot::Node )
private:
protected:
    static void _bind_methods();
public:
    GlobalInterfaceImpl();
    ~GlobalInterfaceImpl();
};

}
