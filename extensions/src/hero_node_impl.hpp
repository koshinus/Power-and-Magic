#pragma once

#include <godot_cpp/classes/node.hpp>

namespace pwm
{

class HeroNodeImpl: public godot::Node
{
    GDCLASS( HeroNodeImpl, godot::Node )
private:
protected:
    static void _bind_methods();
public:
    HeroNodeImpl();
    ~HeroNodeImpl();
};

}
