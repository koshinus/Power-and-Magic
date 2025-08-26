#pragma once

#include <godot_cpp/classes/camera2d.hpp>

namespace pwm
{

class HeroCameraImpl: public godot::Camera2D
{
    GDCLASS( HeroCameraImpl, godot::Camera2D )
public:
    HeroCameraImpl();
    ~HeroCameraImpl();
    void _ready() override;

    int get_px_tile_size() const { return m_px_tile_size; }
    void set_px_tile_size( const int val ) { m_px_tile_size = val; }
    int get_layer_width() const { return m_layer_width; }
    void set_layer_width( const int val ) { m_layer_width = val; }
    int get_layer_height() const { return m_layer_height; }
    void set_layer_height( const int val ) { m_layer_height = val; }
protected:
    static void _bind_methods();
private:
    int m_px_tile_size;
    int m_layer_width;
    int m_layer_height;
};

}
