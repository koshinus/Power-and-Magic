extends Node2D

## This script draw grid on tilemap/tilemaplayer
## To use it you should lead following struct:
## -RootNode
## --LayerNode
## --GridNode

var color = Color.WHITE
var w = 32
var h = 32
var px_size : int = 32

func _ready() -> void:
	set_process(true)
	
func _process(delta):
	queue_redraw()
	
func _draw():
	var size_x : int = 32
	var size_y : int = 32
	for y in range(0, size_y+1):
		draw_line(Vector2(0, y * px_size), Vector2(size_x * px_size, y * px_size), color)
	for x in range(0, size_x+1):
		draw_line(Vector2(x * px_size, 0), Vector2(x * px_size, size_y * px_size), color)
