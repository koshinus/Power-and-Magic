extends Node2D
class_name LocalMap

@onready var map_image : Image = Image.create_empty(
						GLOBAL_MAP.LOCAL_MAP_WIDTH*GLOBAL_MAP.LOCAL_TILE_SIZE_IN_PIXELS,
						GLOBAL_MAP.LOCAL_MAP_HEIGHT*GLOBAL_MAP.LOCAL_TILE_SIZE_IN_PIXELS,
						false,
						$LocalMapSurface.tile_set.get_source( 0 ).texture.get_image().get_format()
						)

## Generating tile type for local adventure map:
## >=50% - should be of type that big_tile_type have
## other part depends on the big tile neighbours
## for example, if tile is grass, other 4 tiles are also grass
## but also there are 2 steppens and 2 deserts then:
## 50 + 6.25*4 - grass local tile chance
## 6.25*2 - steppen and desert chances for each
func _get_local_tile_type_by_neighbours( big_tile_type : int, neighbours : Array[ int ] ) -> int:
	neighbours.sort()
	var tiles_arr : Array[int]
	tiles_arr.resize( neighbours.size() )
	tiles_arr.fill( big_tile_type )
	var idx = neighbours.find( big_tile_type )
	if idx == -1:
		neighbours.append_array( tiles_arr )
	else:
		for i in tiles_arr:
			neighbours.insert( idx, i )
	return neighbours[ randi() % neighbours.size() ]
	
func _get_tile_offset_by_coords( x : int, y : int ) -> int:
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

func get_tilemap_layer_data() -> PackedByteArray:
	return $LocalMapSurface.tile_map_data

func get_map_image() -> Image:
	return map_image

func get_map_image_format() -> Image.Format:
	return map_image.get_format()

func init_by_params( global_tile_type : int, neighbours : Array[int] ) -> void:
	var w : int = GLOBAL_MAP.LOCAL_MAP_WIDTH
	var h : int = GLOBAL_MAP.LOCAL_MAP_HEIGHT
	var tsize : int  = GLOBAL_MAP.TILE_SIZE_IN_TILESET
	var src_image : Image = $LocalMapSurface.tile_set.get_source( 0 ).texture.get_image()
	map_image = Image.create_empty(
						GLOBAL_MAP.LOCAL_MAP_WIDTH*GLOBAL_MAP.LOCAL_TILE_SIZE_IN_PIXELS,
						GLOBAL_MAP.LOCAL_MAP_HEIGHT*GLOBAL_MAP.LOCAL_TILE_SIZE_IN_PIXELS,
						false, src_image.get_format() )
	#print("Start initialization. Size is ", neighbours.size())
	for y in range( h ):
		for x in range( w ):
			var tile_x_offset = _get_tile_offset_by_coords( x, y )
			var tile_y_offset = _get_local_tile_type_by_neighbours( global_tile_type, neighbours.duplicate() )
			var tileset_offset : Vector2i = Vector2i( tile_x_offset, tile_y_offset )
			var tileset_offset_36 : Vector2i = Vector2i ( tile_x_offset*36, tile_y_offset*36 )
			map_image.blit_rect( src_image, Rect2i( tileset_offset_36, Vector2i( tsize, tsize ) ),
								Vector2i(x*w, y*h) )
			$LocalMapSurface.set_cell( Vector2i( x, y ), 0, tileset_offset )
	#map_image.resize( 64, 64, Image.INTERPOLATE_BILINEAR )
