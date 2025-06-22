#pragma once

#include <godot_cpp/classes/node.hpp>

namespace pwm
{

class SelectableImpl: public godot::Node
{
    GDCLASS( SelectableImpl, godot::Node )
private:
protected:
    static void _bind_methods();
public:
    SelectableImpl();
    ~SelectableImpl();
};

}
