#pragma once

#include <godot_cpp/classes/node.hpp>

namespace pwm
{

class ResourcesInfoImpl: public godot::Node
{
    GDCLASS( ResourcesInfoImpl, godot::Node )
private:
protected:
    static void _bind_methods();
public:
    ResourcesInfoImpl();
    ~ResourcesInfoImpl();
};

}
