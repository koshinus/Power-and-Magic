#pragma once

#include <godot_cpp/classes/node2d.hpp>

namespace godot
{
class TileMapLayer;
}

namespace pwm
{

class WorldInfo;
class GlobalMapImpl: public godot::Node2D
{
    GDCLASS( GlobalMapImpl, godot::Node2D )
public:
    GlobalMapImpl();
    ~GlobalMapImpl() override;

    int get_px_tile_size() const { return m_px_tile_size; }
    void set_px_tile_size( const int val ) { m_px_tile_size = val; }
    int get_layer_width() const { return m_layer_width; }
    void set_layer_width( const int val ) { m_layer_width = val; }
    int get_layer_height() const { return m_layer_height; }
    void set_layer_height( const int val ) { m_layer_height = val; }

    void set_based_on_generated( const WorldInfo& world_info );
    godot::TileMapLayer* get_surface();
protected:
    static void _bind_methods();
private:
    int m_px_tile_size;
    int m_layer_width;
    int m_layer_height;

};

}
