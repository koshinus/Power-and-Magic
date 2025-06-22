#pragma once

#include <godot_cpp/classes/node.hpp>

namespace pwm
{

class HeroItemsImpl: public godot::Node
{
    GDCLASS( HeroItemsImpl, godot::Node )
private:
protected:
    static void _bind_methods();
public:
    HeroItemsImpl();
    ~HeroItemsImpl();
};

}
