#pragma once

#include <godot_cpp/classes/node.hpp>

namespace pwm
{

class NumberedTextureImpl: public godot::Node
{
    GDCLASS( NumberedTextureImpl, godot::Node )
private:
protected:
    static void _bind_methods();
public:
    NumberedTextureImpl();
    ~NumberedTextureImpl();
};

}
