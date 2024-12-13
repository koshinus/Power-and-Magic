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
	var local_tset_sources: Array[Array] # Array[Array[TileSetAtlasSource]] actually

#print(glob_tiles_vals)
#var neighbours : Array[int]
#var row_lim = glob_tiles_vals.size()
#var column_lim = glob_tiles_vals.front().size()
#print(range( max(0, i-1), min(i+1, row_lim) ),
		#range( max(0, j-1), min(j+1, column_lim) ) )
#for x in range( max(0, i-1), min(i+1, row_lim) ):
	#for y in range( max(0, j-1), min(j+1, column_lim) ):
		#if not( x == i and y == j ):
			#print(glob_tiles_vals[x][y])
			#neighbours.push_back( glob_tiles_vals[x][y] );
#return neighbours

class LocalTilesetSources:
	static func _get_neighbours( glob_tiles_vals : Array[Array], i : int, j : int ) -> Array[int]:		
		var neighbours : Array[int]
		var rows = glob_tiles_vals.size()
		var cols = glob_tiles_vals.front().size()
		# Define the possible relative positions for neighbours
		var directions : Array[Vector2i] = [
			Vector2i(-1,-1), Vector2i(-1, 0), Vector2i(-1,1), # Top-left,   Top	   , Top-right
			Vector2i(0,-1) ,                  Vector2i(0,1) , # Left,          	   , Right
			Vector2i(1,-1) , Vector2i(1, 0),  Vector2i(1,1)   # Bottom-left, Bottom, Bottom-right
		];
		# Check each direction for valid neighbours
		for dir in directions:
			var new_row : int = i + dir.x;
			var new_col : int = j + dir.y;
			# Check if the new position is within bounds
			if new_row >= 0 && new_row < rows && new_col >= 0 && new_col < cols:
				neighbours.push_back( glob_tiles_vals[new_row][new_col] )
		return neighbours

	## Generating tile type for local adventure map:
	## >=50% - should be of type that big_tile_type have
	## other part depends on the big tile neighbours
	## for example, if tile is grass, other 4 tiles are also grass
	## but also there are 2 steppens and 2 deserts then:
	## 50 + 6.25*4 - grass local tile chance
	## 6.25*2 - steppen and desert chances for each
	static func _get_local_tile_type_by_neighbours( big_tile_type : int, neighbours : Array[ int ] ) -> int:
		#print(neighbours)
		neighbours.sort()
		var tiles_arr : Array[int]
		tiles_arr.resize( neighbours.size() )
		tiles_arr.fill( big_tile_type )
		var idx = neighbours.find( big_tile_type )
		if idx == -1:
			tiles_arr.append_array( tiles_arr )
		else:
			for i in tiles_arr:
				neighbours.insert( idx, i )
		return neighbours[ randi() % neighbours.size() ]
		
	static func _get_tile_offset_by_coords( x : int, y : int ) -> int:
		var w : int = GLOBAL_MAP.LOCAL_MAP_WIDTH
		var h : int = GLOBAL_MAP.LOCAL_MAP_HEIGHT
		var rule_dict = {
			Vector2i(0, 0) : GLOBAL_MAP.LOCAL_TILES.TOP_LEFT,
			Vector2i(w-1, 0) : GLOBAL_MAP.LOCAL_TILES.TOP_RIGHT,
			Vector2i(0, h-1) : GLOBAL_MAP.LOCAL_TILES.BOTTOM_LEFT,
			Vector2i(w-1, h-1) : GLOBAL_MAP.LOCAL_TILES.BOTTOM_RIGHT
		}
		var dict_val = rule_dict.get( Vector2i( x, y ) )
		if dict_val != null: return int(dict_val)
		if y == 0: return GLOBAL_MAP.LOCAL_TILES.TOP
		elif y == h-1: return GLOBAL_MAP.LOCAL_TILES.BOTTOM
		elif x == 0:
			if y % 2 == 1: return GLOBAL_MAP.LOCAL_TILES.LEFT_ODD
			else: return GLOBAL_MAP.LOCAL_TILES.LEFT_EVEN
		elif x == w-1:
			if y % 2 == 1: return GLOBAL_MAP.LOCAL_TILES.RIGHT_ODD
			else: return GLOBAL_MAP.LOCAL_TILES.RIGHT_EVEN
		elif y % 2 == 1: return GLOBAL_MAP.LOCAL_TILES.MIDDLE_ODD
		else: return GLOBAL_MAP.LOCAL_TILES.MIDDLE_EVEN

	static func _generate_image_for_local_map( local_tset_img : Image, glob_tile_type : int, neighbours : Array[int] ) -> Image:
		var w : int = GLOBAL_MAP.LOCAL_MAP_WIDTH
		var h : int = GLOBAL_MAP.LOCAL_MAP_HEIGHT
		var px_size : int = GLOBAL_MAP.LOCAL_TILE_SIZE_IN_PIXELS
		var tset_tile_size : int = GLOBAL_MAP.TILE_SIZE_IN_TILESET
		TileMapLayer
		var img = Image.create_empty( w*px_size, h*px_size, false, local_tset_img.get_format() )
		print(1, '->', w, ',', h)
		var start_t: int
		var end_t: int
		for x in range( w ):
			for y in range( h ):
				print(Vector2i(x,y))
				start_t = Time.get_ticks_msec()
				var tsize : = Vector2i( tset_tile_size, tset_tile_size )
				var rect_region : Rect2i = Rect2i(
						Vector2i( _get_tile_offset_by_coords( x, y ), _get_local_tile_type_by_neighbours( glob_tile_type, neighbours ) ),
						tsize )
				print(rect_region)
				var img_region : Image = local_tset_img.get_region( rect_region )
				img.blit_rect( img_region, Rect2i( Vector2i(0,0), tsize ), Vector2i(x, y) )
				end_t = Time.get_ticks_msec()
				print("Elapsed time:", (end_t-start_t)/1000.0)
		print(4)
		return img

	static func _generate_local_tset_from_global_type( local_tset_img : Image, glob_tile_type : int, neighbours : Array[int] ) -> TileSetAtlasSource:		
		var txtr = ImageTexture.create_from_image( _generate_image_for_local_map( local_tset_img, glob_tile_type, neighbours ) )
		var px_size : int = GLOBAL_MAP.LOCAL_TILE_SIZE_IN_PIXELS
		var source = TileSetAtlasSource.new()
		source.texture = txtr
		source.texture_region_size = Vector2i( px_size, px_size )
		for x in range( GLOBAL_MAP.LOCAL_MAP_WIDTH ):
			for y in range( GLOBAL_MAP.LOCAL_MAP_HEIGHT ):
				source.create_tile( Vector2i( x, y ) )
		return source
	
	static func generate( local_tset_img : Image, glob_tiles_vals : Array[Array] ) -> Array[Array]:
		var local_tset_srcs : Array[Array]
		for x in range( glob_tiles_vals.size() ):
			var arr : Array[TileSetAtlasSource]
			for y in range( glob_tiles_vals.front().size() ):
				var neighbours : Array[int] = _get_neighbours( glob_tiles_vals, x, y )
				print(neighbours)
				arr.push_back( _generate_local_tset_from_global_type( local_tset_img, glob_tiles_vals[x][y], neighbours ) )
				print(1)
			local_tset_srcs.push_back( arr )
		return local_tset_srcs

class WorldGenerator:
	static func _generate_global_tiles_types( noise : FastNoiseLite ) -> Array[Array]:
		var tiles_types : Array[Array]
		var w : int = GLOBAL_MAP.GLOBAL_MAP_WIDTH
		var h : int = GLOBAL_MAP.GLOBAL_MAP_HEIGHT
		for x in range( w ):
			var arr : Array[int]
			for y in range( h ):
				arr.push_back( Genarators.get_tile_type_from_noise( noise.get_noise_2d( x, y ) ) )
			tiles_types.push_back( arr )
		return tiles_types
	
	static func _create_image_from_local( local_tsets : Array[Array] ) -> Image:
		if local_tsets.size() == 0 or local_tsets.front().size() == 0:
			return null
		var w : int = GLOBAL_MAP.GLOBAL_MAP_WIDTH
		var h : int = GLOBAL_MAP.GLOBAL_MAP_HEIGHT
		var px_size : int = GLOBAL_MAP.GLOBAL_TILE_SIZE_IN_PIXELS
		var req_format = local_tsets[0][0].texture.image.get_format()
		var img = Image.create_empty( w*px_size, h*px_size, false, req_format )
		for x in range( w ):
			for y in range( h ):
				var loc_img : Image = local_tsets[x][y].texture.image.resize( px_size, px_size )
				## blend_rect maybe????
				img.blit_rect( loc_img, loc_img.get_used_rect(), Vector2i( x, y ) )
		return img

	static func _generate_global_tileset( local_tsets : Array[Array] ) -> TileSetAtlasSource:
		var txtr = ImageTexture.create_from_image( _create_image_from_local( local_tsets ) )
		var px_size : int = GLOBAL_MAP.GLOBAL_TILE_SIZE_IN_PIXELS
		var source = TileSetAtlasSource.new()
		source.texture = txtr
		source.texture_region_size = Vector2i( px_size, px_size )
		for x in range( GLOBAL_MAP.GLOBAL_MAP_WIDTH ):
			for y in range( GLOBAL_MAP.GLOBAL_MAP_HEIGHT ):
				source.create_tile( Vector2i( x, y ) )
		return source

	static func generate( local_tset_img : Image ) -> WorldInfo:
		var winfo : WorldInfo = WorldInfo.new()
		var noise : FastNoiseLite = Genarators.get_prepared_noise()
		var global_tiles_vals = _generate_global_tiles_types( noise )
		winfo.global_tiles_values = global_tiles_vals
		var local_tsets = LocalTilesetSources.generate( local_tset_img, global_tiles_vals )
		winfo.local_tset_sources = local_tsets
		winfo.global_tset_source = _generate_global_tileset( local_tsets )
		return winfo
