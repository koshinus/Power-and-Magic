#pragma once

#include <godot_cpp/classes/node.hpp>

namespace pwm
{

class Grid2dNodeImpl: public godot::Node
{
    GDCLASS( Grid2dNodeImpl, godot::Node )
private:
protected:
    static void _bind_methods();
public:
    Grid2dNodeImpl();
    ~Grid2dNodeImpl();
};

}
