#pragma once

#include <godot_cpp/classes/control.hpp>

namespace pwm
{

class TestNodeImpl: public godot::Control
{
    GDCLASS( TestNodeImpl, godot::Control )
private:
protected:
    static void _bind_methods();
public:
    void _ready() override;
    TestNodeImpl();
    ~TestNodeImpl();
};

}
