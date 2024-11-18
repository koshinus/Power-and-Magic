extends Node

#@export var glob_tile_size : int = WorldConstants.GLOBAL_TILE_SIZE_IN_PIXELS
#@export var loc_tile_size : int = WorldConstants.LOCAL_TILE_SIZE_IN_PIXELS
	
#class AbstractTileInfo:
class TileGenerator:
	@export var glob_tile_size : int = WorldConstants.GLOBAL_TILE_SIZE_IN_PIXELS
	@export var loc_tile_size : int = WorldConstants.LOCAL_TILE_SIZE_IN_PIXELS

const LOCAL_TILES_IN_GLOBAL_TILE : int = 32;

class LocalTileInfo:
	var _type : int
	var _tile_data : TileData
	
class GlobalTileInfo:
	#TODO: change this instead of typeless Array
	class GlobalTileRow:
		var _row : Array[ LocalTileInfo ]

	var _img_texture : ImageTexture
	var _local_tiles : Array[ Array ]
	var _type : int
	
class MapInfo:
	var _global_tiles: Array[ Array ]
	var width : int
	var height : int
	
class LocalTileGenerator extends TileGenerator:
	static func _generate_local_type_by_global_type( glob_t : int ) -> int:
		return randi() % 10

	static func _generate_tile_data( loc_type : int ) -> TileData:
		return TileData.new()
	
	static func generate( t : int ) -> LocalTileInfo:
		var loc_tile = LocalTileInfo.new()
		loc_tile._type = LocalTileGenerator._generate_local_type_by_global_type( t )
		loc_tile._tile_data = LocalTileGenerator._generate_tile_data( loc_tile._type )
		return loc_tile

class GlobalTileGenerator extends TileGenerator:
	func _generate_image_for_texture( local_tile_set : TileSet, local_tiles : Array[ Array ], glob_type : int ) -> Image:
		var tsource : TileSetAtlasSource = local_tile_set.get_source( local_tile_set.get_source_id( 0 ) )
		var tiles_image : Image = tsource.texture.get_image()
		var px_line_size : int = LOCAL_TILES_IN_GLOBAL_TILE * loc_tile_size
		var img : Image = Image.create_empty( px_line_size, px_line_size, false, tiles_image.get_format() )
		for x in range( LOCAL_TILES_IN_GLOBAL_TILE ):
			for y in range( LOCAL_TILES_IN_GLOBAL_TILE ):
				var tile_info : LocalTileInfo = local_tiles[ x ][ y ]
				var cur_tile_rect : Rect2i = Rect2i( tile_info._type, glob_type, 
													loc_tile_size, loc_tile_size )
				img.blit_rect( tiles_image, cur_tile_rect, Vector2i( x, y ) )
		return img
		
	func _generate_gb_texture( local_tile_set : TileSet, local_tiles : Array[ Array ], glob_type : int ) -> ImageTexture:
		var texture : ImageTexture = ImageTexture.create_from_image( 
							_generate_image_for_texture( local_tile_set, local_tiles, glob_type ) )
		texture.set_size_override( Vector2i( glob_tile_size, glob_tile_size ) )
		return texture
		
	static func generate( local_tile_set : TileSet, t : int ) -> GlobalTileInfo:
		var gb_tile = GlobalTileInfo.new()
		gb_tile._type = t
		for x in range( LOCAL_TILES_IN_GLOBAL_TILE ):
			var tiles_row : Array[ LocalTileInfo ]
			tiles_row.resize( LOCAL_TILES_IN_GLOBAL_TILE )
			for y in range( LOCAL_TILES_IN_GLOBAL_TILE ):
				tiles_row[ y ] = LocalTileGenerator.generate( t )
			gb_tile._local_tiles.push_back( tiles_row )
		gb_tile._img_texture = gb_tile._generate_gb_texture( local_tile_set, gb_tile._local_tiles, gb_tile._type )
		return gb_tile

class MapGenerator extends TileGenerator:
	class StatHolder:
		@export var terrain_type = WorldConstants.GLOBAL_MAP_TERRAIN
		var min_noise : float = 2.0
		var max_noise : float = -2.0
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
		func print_stat() -> void:
			print( "Generation result: ", stat_dict, " ", min_noise, " ", max_noise )
			
		func _normalize( noise_val: float ) -> float:
			return ( noise_val + 0.7 ) * terrain_type.COUNT
	
		func  generate_terrain_type( noise_val: float ) -> int:
			min_noise = minf( min_noise, noise_val )
			max_noise = maxf( max_noise, noise_val )
			noise_val = _normalize( noise_val )
			if ( noise_val < terrain_type.WATER ):
				return terrain_type.DEEP_WATER
			elif ( noise_val >= terrain_type.WATER && noise_val < terrain_type.SWAMP ):
				return terrain_type.WATER
			elif ( noise_val >= terrain_type.SWAMP && noise_val < terrain_type.GRASS ):
				return terrain_type.SWAMP
			elif ( noise_val >= terrain_type.GRASS && noise_val < terrain_type.SNOW ):
				return terrain_type.GRASS
			elif ( noise_val >= terrain_type.SNOW && noise_val < terrain_type.FROZEN_LAVA ):
				return terrain_type.SNOW
			elif ( noise_val >= terrain_type.FROZEN_LAVA && noise_val < terrain_type.DIRT ):
				return terrain_type.FROZEN_LAVA
			elif ( noise_val >= terrain_type.DIRT && noise_val < terrain_type.SAND ):
				return terrain_type.DIRT
			elif ( noise_val >= terrain_type.SAND && noise_val < terrain_type.ROUGH ):
				return terrain_type.SAND
			elif ( noise_val >= terrain_type.ROUGH && noise_val < terrain_type.WASTELAND ):
				return terrain_type.ROUGH
			elif ( noise_val >= terrain_type.WASTELAND && noise_val < terrain_type.MOUNTAINE ):
				return terrain_type.WASTELAND
			else:
				return terrain_type.MOUNTAINE
	
	static func _get_prepared_noise() -> FastNoiseLite:
		var noise = FastNoiseLite.new()
		noise.seed = randi()  # Установите случайное значение для генерации
		noise.set_noise_type( FastNoiseLite.NoiseType.TYPE_SIMPLEX )
		noise.set_frequency( 0.01 )
		noise.set_fractal_lacunarity( 2 )
		noise.set_fractal_gain( 0.5 )
		# this setting
		noise.set_fractal_type( FastNoiseLite.FractalType.FRACTAL_FBM )
		return noise

	static func generate( local_tile_set : TileSet, global_map_width : int, global_map_height : int ) -> MapInfo:
		var map_info : MapInfo = MapInfo.new()
		map_info.width = global_map_width
		map_info.height = global_map_height
		var noise : FastNoiseLite = _get_prepared_noise()
		var stat_holder : StatHolder = StatHolder.new()
		for x in range( global_map_width ):
			var tiles_row : Array[ GlobalTileInfo ]
			tiles_row.resize( global_map_height )
			for y in range( global_map_height ):
				var noise_val : float = noise.get_noise_2d( x, y )
				tiles_row[ y ] = GlobalTileGenerator.generate( local_tile_set,
						MapGenerator._generate_tile_type( noise_val, stat_holder ) )
			map_info._global_tiles.push_back( tiles_row )
		stat_holder.print_stat()
		return map_info
	
	static func _generate_tile_type( noise_val: float, st_holder : StatHolder ) -> int:
		return st_holder.generate_terrain_type( noise_val )
		#if ( noise_val < terrain_type.WATER ):
			#return terrain_type.DEEP_WATER
		#elif ( noise_val >= terrain_type.WATER && noise_val < terrain_type.SWAMP ):
			#return terrain_type.WATER
		#elif ( noise_val >= terrain_type.SWAMP && noise_val < terrain_type.GRASS ):
			#return terrain_type.SWAMP
		#elif ( noise_val >= terrain_type.GRASS && noise_val < terrain_type.SNOW ):
			#return terrain_type.GRASS
		#elif ( noise_val >= terrain_type.SNOW && noise_val < terrain_type.FROZEN_LAVA ):
			#return terrain_type.SNOW
		#elif ( noise_val >= terrain_type.FROZEN_LAVA && noise_val < terrain_type.DIRT ):
			#return terrain_type.FROZEN_LAVA
		#elif ( noise_val >= terrain_type.DIRT && noise_val < terrain_type.SAND ):
			#return terrain_type.DIRT
		#elif ( noise_val >= terrain_type.SAND && noise_val < terrain_type.ROUGH ):
			#return terrain_type.SAND
		#elif ( noise_val >= terrain_type.ROUGH && noise_val < terrain_type.WASTELAND ):
			#return terrain_type.ROUGH
		#elif ( noise_val >= terrain_type.WASTELAND && noise_val < terrain_type.MOUNTAINE ):
			#return terrain_type.WASTELAND
		#else:
			#return terrain_type.MOUNTAINE

	#func _generate_tile( id: int, idx_in_tileset: int, atlas : Vector2i ) -> GbTileInfo:
		#stat_dict[idx_in_tileset] = stat_dict[idx_in_tileset]+1
		#var tile_info = GbTileInfo.new()
		#tile_info.tile_id = id
		#tile_info.atlas = atlas
		#return tile_info
		
	#func get_tile_info_from_noise( noise_val: float ) -> GbTileInfo:
		#min_noise = minf( min_noise, noise_val )
		#max_noise = maxf( max_noise, noise_val )
		#noise_val = _normalize( noise_val )
		#if ( noise_val < terrain_type.WATER ):
			#return _generate_tile( 0, terrain_type.DEEP_WATER, Vector2i( 0,0 ) )
		#elif ( noise_val >= terrain_type.WATER && noise_val < terrain_type.SWAMP ):
			#return _generate_tile( 0, terrain_type.WATER, Vector2i( 1,0 ) )
		#elif ( noise_val >= terrain_type.SWAMP && noise_val < terrain_type.GRASS ):
			#return _generate_tile( 0, terrain_type.SWAMP, Vector2i( 2,0 ) )
		#elif ( noise_val >= terrain_type.GRASS && noise_val < terrain_type.SNOW ):
			#return _generate_tile( 0, terrain_type.GRASS, Vector2i( 3,0 ) )
		#elif ( noise_val >= terrain_type.SNOW && noise_val < terrain_type.FROZEN_LAVA ):
			#return _generate_tile( 0, terrain_type.SNOW, Vector2i( 4,0 ) )
		#elif ( noise_val >= terrain_type.FROZEN_LAVA && noise_val < terrain_type.DIRT ):
			#return _generate_tile( 0, terrain_type.FROZEN_LAVA, Vector2i( 5,0 ) )
		#elif ( noise_val >= terrain_type.DIRT && noise_val < terrain_type.SAND ):
			#return _generate_tile( 0, terrain_type.DIRT, Vector2i( 6,0 ) )
		#elif ( noise_val >= terrain_type.SAND && noise_val < terrain_type.ROUGH ):
			#return _generate_tile( 0, terrain_type.SAND, Vector2i( 7,0 ) )
		#elif ( noise_val >= terrain_type.ROUGH && noise_val < terrain_type.WASTELAND ):
			#return _generate_tile( 0, terrain_type.ROUGH, Vector2i( 8,0 ) )
		#elif ( noise_val >= terrain_type.WASTELAND && noise_val < terrain_type.MOUNTAINE ):
			#return _generate_tile( 0, terrain_type.WASTELAND, Vector2i( 9,0 ) )
		#else:
			#return _generate_tile( 0, terrain_type.MOUNTAINE, Vector2i( 10,0 ) )
		
	## Called when the node enters the scene tree for the first time.
	#func _ready() -> void:
		#var noise = get_prepared_noise()
		#for x in range( layer_width ):
			#for y in range( layer_height ):
				## Функция для получения ID тайла на основе значения шума
				#var tile_info = get_tile_info_from_noise( noise.get_noise_2d( x, y ) )
				#self.set_cell( Vector2i( x, y ), tile_info.tile_id, tile_info.atlas )
		#print( "Generation result: ", stat_dict, " ", min_noise, " ", max_noise )
