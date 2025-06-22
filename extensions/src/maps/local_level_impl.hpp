#pragma once

#include <godot_cpp/classes/node.hpp>

namespace pwm
{

class LocalLevelImpl: public godot::Node
{
    GDCLASS( LocalLevelImpl, godot::Node )
private:
protected:
    static void _bind_methods();
public:
    LocalLevelImpl();
    ~LocalLevelImpl();
};

}
