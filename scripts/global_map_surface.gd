extends TileMapLayer

@export var terrain_type = WorldConstants.GLOBAL_MAP_TERRAIN
@export var px_tile_size : int = WorldConstants.GLOBAL_TILE_SIZE_IN_PIXELS

#var world_limits = $

class GlobalTileInfo:
	var atlas: Vector2i
	var tile_id: int

var layer_width = 100
var layer_height = 100

var min_noise = 2.0
var max_noise = -2.0

var stat_dict = {
	terrain_type.DEEP_WATER: 0,
	terrain_type.WATER: 0,
	terrain_type.SWAMP: 0,
	terrain_type.GRASS: 0,
	terrain_type.SNOW: 0,
	terrain_type.FROZEN_LAVA: 0,
	terrain_type.DIRT: 0,
	terrain_type.SAND: 0,
	terrain_type.ROUGH: 0,
	terrain_type.WASTELAND: 0,
	terrain_type.MOUNTAINE: 0
}

func _generate_tile( id: int, idx_in_tileset: int, atlas : Vector2i ) -> GlobalTileInfo:
	stat_dict[idx_in_tileset] = stat_dict[idx_in_tileset]+1
	var tile_info = GlobalTileInfo.new()
	tile_info.tile_id = id
	tile_info.atlas = atlas
	return tile_info

func _normalize( noise_val: float ) -> float:
	return ( noise_val + 0.7 ) * terrain_type.COUNT
	
func get_tile_info_from_noise( noise_val: float ) -> GlobalTileInfo:
	min_noise = minf( min_noise, noise_val )
	max_noise = maxf( max_noise, noise_val )
	noise_val = _normalize( noise_val )
	if ( noise_val < terrain_type.WATER ):
		return _generate_tile( 0, terrain_type.DEEP_WATER, Vector2i( 0,0 ) )
	elif ( noise_val >= terrain_type.WATER && noise_val < terrain_type.SWAMP ):
		return _generate_tile( 0, terrain_type.WATER, Vector2i( 1,0 ) )
	elif ( noise_val >= terrain_type.SWAMP && noise_val < terrain_type.GRASS ):
		return _generate_tile( 0, terrain_type.SWAMP, Vector2i( 2,0 ) )
	elif ( noise_val >= terrain_type.GRASS && noise_val < terrain_type.SNOW ):
		return _generate_tile( 0, terrain_type.GRASS, Vector2i( 3,0 ) )
	elif ( noise_val >= terrain_type.SNOW && noise_val < terrain_type.FROZEN_LAVA ):
		return _generate_tile( 0, terrain_type.SNOW, Vector2i( 4,0 ) )
	elif ( noise_val >= terrain_type.FROZEN_LAVA && noise_val < terrain_type.DIRT ):
		return _generate_tile( 0, terrain_type.FROZEN_LAVA, Vector2i( 5,0 ) )
	elif ( noise_val >= terrain_type.DIRT && noise_val < terrain_type.SAND ):
		return _generate_tile( 0, terrain_type.DIRT, Vector2i( 6,0 ) )
	elif ( noise_val >= terrain_type.SAND && noise_val < terrain_type.ROUGH ):
		return _generate_tile( 0, terrain_type.SAND, Vector2i( 7,0 ) )
	elif ( noise_val >= terrain_type.ROUGH && noise_val < terrain_type.WASTELAND ):
		return _generate_tile( 0, terrain_type.ROUGH, Vector2i( 8,0 ) )
	elif ( noise_val >= terrain_type.WASTELAND && noise_val < terrain_type.MOUNTAINE ):
		return _generate_tile( 0, terrain_type.WASTELAND, Vector2i( 9,0 ) )
	else:
		return _generate_tile( 0, terrain_type.MOUNTAINE, Vector2i( 10,0 ) )

func get_prepared_noise() -> FastNoiseLite:
	var noise = FastNoiseLite.new()
	noise.seed = randi()  # Установите случайное значение для генерации
	noise.set_noise_type( FastNoiseLite.NoiseType.TYPE_SIMPLEX )
	noise.set_frequency( 0.01 )
	noise.set_fractal_lacunarity( 2 )
	noise.set_fractal_gain( 0.5 )
	# this setting
	noise.set_fractal_type( FastNoiseLite.FractalType.FRACTAL_FBM )
	return noise
	
# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	#var world_limits = get_node_or_null( "./StaticBody2D/WorldLimits" )
	#if world_limits != null:
		#print(1)
		#world_limits.size = Vector2i( layer_width * px_tile_size, layer_height * px_tile_size )
	var noise = get_prepared_noise()
	for x in range( layer_width ):
		for y in range( layer_height ):
			# Функция для получения ID тайла на основе значения шума
			var tile_info = get_tile_info_from_noise( noise.get_noise_2d( x, y ) )
			self.set_cell( Vector2i( x, y ), tile_info.tile_id, tile_info.atlas )
	print( "Generation result: ", stat_dict, " ", min_noise, " ", max_noise )
