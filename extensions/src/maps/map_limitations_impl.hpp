#pragma once

#include <godot_cpp/classes/node.hpp>

namespace pwm
{

class MapLimitationsImpl: public godot::Node
{
    GDCLASS( MapLimitationsImpl, godot::Node )
private:
protected:
    static void _bind_methods();
public:
    MapLimitationsImpl();
    ~MapLimitationsImpl();
};

}
