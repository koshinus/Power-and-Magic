#include "test_node_impl.hpp"

namespace pwm
{

TestNodeImpl::TestNodeImpl()
{
    godot::print_line( "TestNodeImpl" );
}

TestNodeImpl::~TestNodeImpl()
{
    godot::print_line( "~TestNodeImpl" );
}

void TestNodeImpl::_bind_methods()
{
}

void TestNodeImpl::_ready()
{
    godot::print_line( "TestNodeImpl::_ready" );
}

}
