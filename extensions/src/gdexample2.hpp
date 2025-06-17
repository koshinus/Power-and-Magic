#pragma once

#include <godot_cpp/classes/node.hpp>

namespace godot
{

class GDExample2: public Node
{
    GDCLASS( GDExample2, Node )
protected:
    static void _bind_methods();
public:
    GDExample2();
    ~GDExample2();
    void _process( double delta ) override;
};

}
