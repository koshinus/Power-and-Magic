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
class WorldInfo:
	var global_tiles_values: Array[Array] # Array[Array[int]] actually
	var global_tset_source: TileSetAtlasSource
	var local_maps: Array[Array] # Array[Array[LocalMap]] actually

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
	
	static func _create_image_from_local( local_maps : Array[Array] ) -> Image:
		if local_maps.size() == 0 or local_maps.front().size() == 0:
			return null
		var w : int = GLOBAL_MAP.GLOBAL_MAP_WIDTH
		var h : int = GLOBAL_MAP.GLOBAL_MAP_HEIGHT
		var px_size : int = GLOBAL_MAP.GLOBAL_TILE_SIZE_IN_PIXELS
		#TileMapLayer
		var img = Image.create_empty( w*px_size, h*px_size, false, local_maps[0][0].get_map_image_format() )
		print( "Global texture info: ", img.get_size() )
		for y in range( h ):
			for x in range( w ):
				var loc_img : Image = local_maps[x][y].get_map_image()
				loc_img.resize( px_size, px_size, Image.INTERPOLATE_BILINEAR )
				#print("Image info after resize ", loc_img.get_size(), " for tile at", Vector2i(x*w,y*h) )
				img.blit_rect( loc_img, Rect2i(0, 0, px_size, px_size), Vector2i( x*px_size, y*px_size ) )
		return img

	static func _get_neighbours( glob_tiles_vals : Array[Array], i : int, j : int ) -> Array[int]:		
		var neighbours : Array[int]
		var rows = glob_tiles_vals.size()
		var cols = glob_tiles_vals.front().size()
		# Define the possible relative positions for neighbours
		var directions : Array[Vector2i] = [
			Vector2i(-1,-1), Vector2i(-1, 0), Vector2i(-1,1), # Top-left,   Top	   , Top-right
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

	static func _generate_local_maps( global_tiles_vals : Array[Array] ) -> Array[Array]:
		var loc_maps : Array[Array]
		var w : int = GLOBAL_MAP.GLOBAL_MAP_WIDTH
		var h : int = GLOBAL_MAP.GLOBAL_MAP_HEIGHT
		for y in range(h):
			var map_row : Array[LocalMap]
			for x in range(w):
				#print(x, ",", y)
				#var loc_map = LocalMap.new()
				var loc_map = load("res://scenes/local_map.tscn").instantiate()
				loc_map.init_by_params( global_tiles_vals[x][y], _get_neighbours( global_tiles_vals, x, y ) )
				#if x == 0 and y == 0:
					#loc_map.init_by_params( global_tiles_vals[x][y], _get_neighbours( global_tiles_vals, x, y ) )
					#var file_temp = "C:/Users/Vadim/Desktop/test/some_{0}_{1}.png"
					#loc_map.get_map_image().save_png( file_temp.format([0, 0]) )
				map_row.push_back( loc_map )
			loc_maps.push_back( map_row )
		return loc_maps

	static func _generate_global_tileset( local_tsets : Array[Array] ) -> TileSetAtlasSource:
		var txtr = ImageTexture.create_from_image( _create_image_from_local( local_tsets ) )
		var px_size : int = GLOBAL_MAP.GLOBAL_TILE_SIZE_IN_PIXELS
		var source = TileSetAtlasSource.new()
		source.texture = txtr
		source.texture_region_size = Vector2i( px_size, px_size )
		for y in range( GLOBAL_MAP.GLOBAL_MAP_HEIGHT ):
			for x in range( GLOBAL_MAP.GLOBAL_MAP_WIDTH ):
				source.create_tile( Vector2i( x, y ) )
		return source

	static func generate() -> WorldInfo:
		#ViewportTexture
		var winfo : WorldInfo = WorldInfo.new()
		var noise : FastNoiseLite = Genarators.get_prepared_noise()
		var global_tiles_vals = _generate_global_tiles_types( noise )
		winfo.global_tiles_values = global_tiles_vals
		var loc_maps : Array[Array] = _generate_local_maps( global_tiles_vals )
		winfo.local_maps = loc_maps
		winfo.global_tset_source = _generate_global_tileset( loc_maps )
		return winfo
