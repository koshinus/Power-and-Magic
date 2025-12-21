#pragma once

#include <godot_cpp/classes/window.hpp>

namespace pwm
{

class LocalLevelImpl: public godot::Window
{
    GDCLASS( LocalLevelImpl, godot::Window )
public:
    LocalLevelImpl();
    ~LocalLevelImpl() override;
protected:
    static void _bind_methods();
private:
};

}
