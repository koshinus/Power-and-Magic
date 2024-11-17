extends Node

class AbstractTileInfo:
	@export var glob_tile_size : int = WorldConstants.GLOBAL_TILE_SIZE_IN_PIXELS
	@export var loc_tile_size : int = WorldConstants.LOCAL_TILE_SIZE_IN_PIXELS

class LocalTileInfo extends AbstractTileInfo:
	var _type : int
	var _tile_data : TileData
	
	static func _generate_local_type_by_global_type( glob_t : int ) -> int:
		return 0

	static func _generate_tile_data( loc_type : int ) -> TileData:
		return TileData.new()
	
	static func generate( t : int ) -> LocalTileInfo:
		var loc_tile = LocalTileInfo.new()
		loc_tile._type = LocalTileInfo._generate_local_type_by_global_type( t )
		loc_tile._tile_data = LocalTileInfo._generate_tile_data( loc_tile._type )
		return loc_tile

class GlobalTileInfo extends AbstractTileInfo:
	#TODO: change this instead of typeless Array
	class GlobalTileRow:
		var _row : Array[ LocalTileInfo ]
	
	const _LOCAL_TILES_NUMBER : int = 16
	var _img_texture : ImageTexture
	var _local_tiles : Array[ Array ]
	var _type : int

	func _generate_image_for_texture( local_tile_set : TileSet, local_tiles : Array[ Array ], glob_type : int ) -> Image:
		#var byte_arr = PackedByteArray()
		var tsource : TileSetAtlasSource = local_tile_set.get_source( local_tile_set.get_source_id( 0 ) )
		#print( tsource )
		var tiles_image : Image = tsource.texture.get_image()
		var px_line_size : int = _LOCAL_TILES_NUMBER * loc_tile_size
		var res_img : Image = Image.create_empty( px_line_size, px_line_size, false, tiles_image.get_format() )
		#for i in range( px_line_size ):
			#for j in range( px_line_size ):
				#var loc_tile_x : int = ( i / loc_tile_size )
				#var loc_tile_y : int = ( j / loc_tile_size )
				#var loc_tile : LocalTileInfo = local_tiles[ loc_tile_x ][ loc_tile_y ]
		for x in range( _LOCAL_TILES_NUMBER ):
			for y in range( _LOCAL_TILES_NUMBER ):
				var tile_info : LocalTileInfo = local_tiles[ x ][ y ]
				#var tile_atlas_coord : Vector2i = Vector2i( tile_info._type, glob_type )
				var cur_tile_rect : Rect2i = Rect2i( tile_info._type, glob_type, 
													loc_tile_size, loc_tile_size )
				res_img.blit_rect( tiles_image, cur_tile_rect, Vector2i( x, y ) )
				#var cur_tile_img : Image = tiles_image.
				#for tile_x_px in range( loc_tile_size ):
					#for tile_y_px in range( loc_tile_size ):
						#res_img.set_pixelv( Vector2i( 0, 0 ),
									#cur_tile_img.get_pixel( tile_x_px, tile_y_px ) )
		#var img = Image.create_from_data( px_line_size, px_line_size,
								#false, tiles_image.format(), byte_arr )
		#return img
		return res_img
		
	func _generate_gb_texture( local_tile_set : TileSet, local_tiles : Array[ Array ], glob_type : int ) -> ImageTexture:
		var texture : ImageTexture = ImageTexture.create_from_image( 
							_generate_image_for_texture( local_tile_set, local_tiles, glob_type ) )
		texture.set_size_override( Vector2i( glob_tile_size, glob_tile_size ) )
		return texture
		
	static func generate( local_tile_set : TileSet, t : int ) -> GlobalTileInfo:
		var gb_tile = GlobalTileInfo.new()
		gb_tile._type = t
		for x in range( _LOCAL_TILES_NUMBER ):
			var tiles_row : Array[ LocalTileInfo ]
			tiles_row.resize( _LOCAL_TILES_NUMBER )
			for y in range( _LOCAL_TILES_NUMBER ):
				tiles_row[ y ] = LocalTileInfo.generate( t )
			gb_tile._local_tiles.push_back( tiles_row )
		gb_tile._img_texture = gb_tile._generate_gb_texture( local_tile_set, gb_tile._local_tiles, gb_tile._type )
		return gb_tile
	
class MapInfo:
	var _global_tiles: Array[ Array ]
	var width : int
	var height : int

	func _generate_tile_type() -> int:
		return 0

	#func _generate_global_tile( t : int ) -> GlobalTileInfo:
		#var gb_tile = GlobalTileInfo.new()
		#gb_tile.generate( t )
		#return gb_tile

	func generate( local_tile_set : TileSet, w : int, h : int ):
		width = w
		height = h
		for x in range( width ):
			var tiles_row : Array[ GlobalTileInfo ]
			tiles_row.resize( height )
			for y in range( height ):
				tiles_row[ y ] = GlobalTileInfo.generate( local_tile_set, _generate_tile_type() )
			_global_tiles.push_back( tiles_row )

class MapGenerator:
	static func generate( local_tile_set : TileSet, global_map_width : int, global_map_height : int ) -> MapInfo:
		var map_info : MapInfo = MapInfo.new()
		#map_info.width = global_map_width
		#map_info.height = global_map_height
		map_info.generate( local_tile_set, global_map_width, global_map_height )
		#for x in range( global_map_width ):
			#for y in range( global_map_height ):
				#pass
		return map_info
	
