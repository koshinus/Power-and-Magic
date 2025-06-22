#pragma once

#include <godot_cpp/classes/node.hpp>

namespace pwm
{

class TestNodeImpl: public godot::Node
{
    GDCLASS( TestNodeImpl, godot::Node )
private:
protected:
    static void _bind_methods();
public:
    TestNodeImpl();
    ~TestNodeImpl();
};

}
