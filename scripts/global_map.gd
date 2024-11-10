extends TileMapLayer

@export var terrain_type = WorldConstants.GLOBAL_MAP_TERRAIN

class GlobalTileInfo:
	var atlas: Vector2i
	var tile_id: int

var layer_width = 100
var layer_height = 100

var stat_dict = {
	terrain_type.DEEP_WATER: 0,
	terrain_type.WATER: 0,
	terrain_type.SWAMP: 0,
	terrain_type.GRASS: 0,
	terrain_type.SNOW: 0,
	terrain_type.FROZEN_LAVA: 0,
	terrain_type.MOUNTAINE: 0,
}

func _generate_tile( id: int, atlas : Vector2i ) -> GlobalTileInfo:
	var tile_info = GlobalTileInfo.new()
	tile_info.tile_id = id
	tile_info.atlas = atlas
	return tile_info

func get_tile_info_from_noise( noise_val: float ) -> GlobalTileInfo:
	# Normalize noise value to fit into GLOBAL_MAP_TERRAIN enum
	#noise_val = noise_val + GLOBAL_MAP_TERRAIN.COUNT
	#if noise_val < GLOBAL_MAP_TERRAIN.COAST:
		#print("Noise val is ", noise_val)
	if ( noise_val >= terrain_type.DEEP_WATER && noise_val < terrain_type.WATER ):
		stat_dict[terrain_type.DEEP_WATER] = stat_dict[terrain_type.DEEP_WATER]+1
		return _generate_tile( 1, Vector2i( 0,0 ) )
	elif ( noise_val >= terrain_type.WATER && noise_val < terrain_type.SWAMP ):
		stat_dict[terrain_type.WATER] = stat_dict[terrain_type.WATER]+1
		return _generate_tile( 1, Vector2i( 4,0 ) )
	#elif ( noise_val >= terrain_type.COAST && noise_val < terrain_type.SWAMP ):
		#print("Noise val is ", noise_val)
		#return terrain_type.COAST
	elif ( noise_val >= terrain_type.SWAMP && noise_val < terrain_type.GRASS ):
		stat_dict[terrain_type.SWAMP] = stat_dict[terrain_type.SWAMP]+1
		return _generate_tile( 1, Vector2i( 8,0 ) )
	elif ( noise_val >= terrain_type.GRASS && noise_val < terrain_type.SNOW ):
		stat_dict[terrain_type.SNOW] = stat_dict[terrain_type.SNOW]+1
		return _generate_tile( 1, Vector2i( 12,0 ) )
	elif ( noise_val >= terrain_type.SNOW && noise_val < terrain_type.FROZEN_LAVA ):
		stat_dict[terrain_type.SNOW] = stat_dict[terrain_type.SNOW]+1
		return _generate_tile( 1, Vector2i( 16,0 ) )
	elif ( noise_val >= terrain_type.FROZEN_LAVA && noise_val < terrain_type.MOUNTAINE ):
		stat_dict[terrain_type.FROZEN_LAVA] = stat_dict[terrain_type.FROZEN_LAVA]+1
		return _generate_tile( 1, Vector2i( 16,4 ) )
	else:
		stat_dict[terrain_type.MOUNTAINE] = stat_dict[terrain_type.MOUNTAINE]+1
		return _generate_tile( 1, Vector2i( 4,4 ) )

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
	var noise = get_prepared_noise()
	for x in range( layer_width ):
		for y in range( layer_height ):
			# Функция для получения ID тайла на основе значения шума
			var tile_info = get_tile_info_from_noise( noise.get_noise_2d( x, y ) )
			self.set_cell( Vector2i( x, y ), tile_info.tile_id, tile_info.atlas )
	print( "Generation result: ", stat_dict )
