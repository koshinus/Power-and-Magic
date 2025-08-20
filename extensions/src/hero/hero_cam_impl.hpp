#pragma once

#include <godot_cpp/classes/camera2d.hpp>

#include "../utils/pwm_properties.hpp"

namespace pwm
{

class HeroCameraImpl: public godot::Camera2D
{
    GDCLASS( HeroCameraImpl, godot::Camera2D )
private:
    PwmProperty<int> m_px_tile_size;
    PwmProperty<int> m_layer_width;
    PwmProperty<int> m_layer_height;
protected:
    static void _bind_methods();
public:
    HeroCameraImpl();
    ~HeroCameraImpl();
    void _ready() override;

    void set_px_tile_size( const int val );
    void set_layer_width( const int val );
    void set_layer_height( const int val );

    int get_px_tile_size();
    int get_layer_width();
    int get_layer_height();
};

}
