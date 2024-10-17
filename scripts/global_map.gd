extends Node2D

@export var noise_height_text: NoiseTexture2D
var noise : Noise

var width : int = 100
var height : int = 100

@onready var tile_map_layer = $TileMapLayer
var src_id = 0
var water_atlas = Vector2i(0,1)
var land_atlas = Vector2i(0,0)


func _ready() -> void:
		noise = noise_height_text.noise
		generate_world()

func generate_world() -> void:
	for x in range(width):
		for y in range(height):
			var noise_val : float = noise.get_noise_2d(x, y)
			#print(noise_val)
			if noise_val >= 0.0:
				tile_map_layer.set_cell(Vector2(x,y), src_id, land_atlas)
			elif noise_val < 0.0:
				tile_map_layer.set_cell(Vector2(x,y), src_id, water_atlas)
