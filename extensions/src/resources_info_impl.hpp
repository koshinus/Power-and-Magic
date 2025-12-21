#pragma once

#include <godot_cpp/classes/control.hpp>

namespace pwm
{

class ResourcesInfoImpl: public godot::Control
{
    GDCLASS( ResourcesInfoImpl, godot::Control )
public:
    ResourcesInfoImpl();
    ~ResourcesInfoImpl() override;
protected:
    static void _bind_methods();
private:
};

}
