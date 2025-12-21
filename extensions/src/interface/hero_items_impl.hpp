#pragma once

#include <godot_cpp/classes/control.hpp>

namespace pwm
{

class HeroItemsImpl: public godot::Control
{
    GDCLASS( HeroItemsImpl, godot::Control )
private:
protected:
    static void _bind_methods();
public:
    HeroItemsImpl();
    ~HeroItemsImpl() override;
};

}
