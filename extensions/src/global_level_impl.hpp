#pragma once

#include <godot_cpp/classes/node.hpp>

namespace pwm
{

class GlobalLevelImpl: public godot::Node
{
    GDCLASS( GlobalLevelImpl, godot::Node )
private:
protected:
    static void _bind_methods();
public:
    GlobalLevelImpl();
    ~GlobalLevelImpl();
};

}
