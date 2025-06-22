#pragma once

#include <godot_cpp/classes/node.hpp>

namespace pwm
{

class LocalMapImpl: public godot::Node
{
    GDCLASS( LocalMapImpl, godot::Node )
private:
protected:
    static void _bind_methods();
public:
    LocalMapImpl();
    ~LocalMapImpl();
};

}
