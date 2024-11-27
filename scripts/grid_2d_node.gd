@tool
extends Node2D
class_name Grid2DNode

## This script draw grid on tilemap/tilemaplayer
## To use it you should lead following struct:
## -RootNode
## --LayerNode
## --Grid2DNode

@export var map_width : int = 32
@export var map_height : int = 32
@export var tile_size : Vector2i = Vector2i( 32, 32 )
@export var grid_color : Color = Color.WHITE

func _ready() -> void:
	set_process(true)
	
func _process(delta):
	queue_redraw()
	
func _draw():
	for y in range(0, map_height+1):
		draw_line(Vector2(0, y * tile_size.y), Vector2(map_width * tile_size.x, y * tile_size.y), grid_color)
	for x in range(0, map_width+1):
		draw_line(Vector2(x * tile_size.x, 0), Vector2(x * tile_size.x, map_height * tile_size.y), grid_color)
