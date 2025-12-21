#pragma once

#include <godot_cpp/core/object.hpp>

namespace pwm
{

template<typename T>
struct ObjectWrapper: public godot::Object
{
    ObjectWrapper() : godot::Object() {}
    ObjectWrapper( T val_ ) : godot::Object() { val = val_; }
    ~ObjectWrapper() {}
    T val;
};

}
