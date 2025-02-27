extends Node
class_name Genarators

################################ FREE FUNCTIONS
static func normalize( noise_val: float ) -> float:
	return ( noise_val + 0.7 ) * GLOBAL_MAP.TYPES.COUNT

static func get_tile_type_from_noise( noise_val: float ) -> int:
	#min_noise = minf( min_noise, noise_val )
	#max_noise = maxf( max_noise, noise_val )
	noise_val = normalize( noise_val )
	if ( noise_val < GLOBAL_MAP.TYPES.WATER ):
		return GLOBAL_MAP.TYPES.DEEP_WATER
	elif ( noise_val >= GLOBAL_MAP.TYPES.WATER && noise_val < GLOBAL_MAP.TYPES.SNOW ):
		return GLOBAL_MAP.TYPES.WATER
	elif ( noise_val >= GLOBAL_MAP.TYPES.SNOW && noise_val < GLOBAL_MAP.TYPES.TUNDRA ):
		return GLOBAL_MAP.TYPES.SNOW
	elif ( noise_val >= GLOBAL_MAP.TYPES.TUNDRA && noise_val < GLOBAL_MAP.TYPES.STEPPEN ):
		return GLOBAL_MAP.TYPES.TUNDRA
	elif ( noise_val >= GLOBAL_MAP.TYPES.STEPPEN && noise_val < GLOBAL_MAP.TYPES.GRASS ):
		return GLOBAL_MAP.TYPES.STEPPEN
	elif ( noise_val >= GLOBAL_MAP.TYPES.GRASS && noise_val < GLOBAL_MAP.TYPES.SAND ):
		return GLOBAL_MAP.TYPES.GRASS
	elif ( noise_val >= GLOBAL_MAP.TYPES.SAND && noise_val < GLOBAL_MAP.TYPES.MOUNTAINE ):
		return GLOBAL_MAP.TYPES.SAND
	else:
		return GLOBAL_MAP.TYPES.MOUNTAINE

static func get_prepared_noise() -> FastNoiseLite:
	var noise = FastNoiseLite.new()
	noise.seed = randi()
	noise.set_noise_type( FastNoiseLite.NoiseType.TYPE_SIMPLEX )
	noise.set_frequency( 0.01 )
	noise.set_fractal_lacunarity( 2 )
	noise.set_fractal_gain( 0.5 )
	noise.set_fractal_type( FastNoiseLite.FractalType.FRACTAL_FBM )
	return noise

################################
class ScenesInfo:
	var global_tset_source: TileSetScenesCollectionSource
	var local_maps: Dictionary # Maps (x, y) -> tile_id for global_tset_source
	
class WorldInfo:
	var global_tiles_values: Array[Array] # Array[Array[int]] actually
	var loc_scenes_info: ScenesInfo

class WorldGenerator:
	static func _generate_global_tiles_types( noise : FastNoiseLite ) -> Array[Array]:
		var tiles_types : Array[Array]
		var w : int = GLOBAL_MAP.GLOBAL_MAP_WIDTH
		var h : int = GLOBAL_MAP.GLOBAL_MAP_HEIGHT
		for y in range( h ):
			var arr : Array[int]
			for x in range( w ):
				arr.push_back( Genarators.get_tile_type_from_noise( noise.get_noise_2d( x, y ) ) )
			tiles_types.push_back( arr )
		return tiles_types

	static func _get_neighbours( glob_tiles_vals : Array[Array], i : int, j : int ) -> Array[int]:		
		var neighbours : Array[int]
		var rows = glob_tiles_vals.size()
		var cols = glob_tiles_vals.front().size()
		# Define the possible relative positions for neighbours
		var directions : Array[Vector2i] = [
			Vector2i(-1,-1), Vector2i(-1, 0), Vector2i(-1,1), # Top-left,    Top   , Top-right
			Vector2i( 0,-1),                  Vector2i( 0,1), # Left,          	   , Right
			Vector2i( 1,-1), Vector2i( 1, 0), Vector2i( 1,1)  # Bottom-left, Bottom, Bottom-right
		];
		# Check each direction for valid neighbours
		for dir in directions:
			var new_row : int = i + dir.x;
			var new_col : int = j + dir.y;
			# Check if the new position is within bounds
			if new_row >= 0 && new_row < rows && new_col >= 0 && new_col < cols:
				neighbours.push_back( glob_tiles_vals[new_row][new_col] )
		return neighbours

	static func _generate_local_maps( global_tiles_vals : Array[Array] ) -> ScenesInfo:
		var loc_scenes_info : ScenesInfo = ScenesInfo.new()
		var tset_source : TileSetScenesCollectionSource = TileSetScenesCollectionSource.new()
		var w : int = GLOBAL_MAP.GLOBAL_MAP_WIDTH
		var h : int = GLOBAL_MAP.GLOBAL_MAP_HEIGHT
		for y in range(h):
			for x in range(w):
				var loc_map_scene : PackedScene = preload( "res://scenes/maps/local_map.tscn" )
				var loc_map : LocalMap = loc_map_scene.instantiate()
				loc_map.init_by_params( global_tiles_vals[x][y], _get_neighbours( global_tiles_vals, x, y ) )
				loc_scenes_info.local_maps[ Vector2i(x,y) ] = tset_source.create_scene_tile( loc_map_scene )
		loc_scenes_info.global_tset_source = tset_source
		return loc_scenes_info

	static func generate() -> WorldInfo:
		var winfo : WorldInfo = WorldInfo.new()
		var noise : FastNoiseLite = Genarators.get_prepared_noise()
		var global_tiles_vals = _generate_global_tiles_types( noise )
		winfo.global_tiles_values = global_tiles_vals
		winfo.loc_scenes_info = _generate_local_maps( global_tiles_vals )
		print( "Dict:", winfo.loc_scenes_info.local_maps )
		return winfo
