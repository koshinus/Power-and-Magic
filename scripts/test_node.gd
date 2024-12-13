extends Node2D

@onready var tilemap_rect = $TestLayer.get_used_rect()
@onready var tilemap_cell_size = Vector2(32,32)#$TestLayer.cell_size
@onready var color = Color(0.0, 1.0, 0.0)

var local_tsets = preload("res://data/local_tileset.tres").instantiate()

var w = 32
var h = 32
var px_size : int = 32

#var colors : Array = [ Color.ALICE_BLUE, Color.AQUA, Color.GREEN, Color.BLUE, Color.YELLOW ]
var colors : Array = [ Color.GREEN, Color.BLUE, Color.YELLOW ]

func _create_image_from_rectangles() -> Image:
	var img = Image.create_empty( w*px_size, h*px_size, false, Image.FORMAT_RGBA8 )
	for x in range( w ):
		for y in range( h ):
			img.fill_rect( Rect2i( x*px_size, y*px_size, px_size, px_size ), colors[ ( randi() % colors.size() ) ] )
	#img.save_png( "C:/Power-and-Magic/resources/36/some.png" )
	return img

func _create_atlas_source() -> TileSetAtlasSource:
	var txtr = ImageTexture.create_from_image( _create_image_from_rectangles() )
	var source = TileSetAtlasSource.new()
	source.texture = txtr
	source.texture_region_size = Vector2i( px_size, px_size )
	for x in range( w ):
		for y in range( h ):
			source.create_tile( Vector2i( x, y ) )
	return source
	
func _create_from_dynamic_atlas_source() -> void:
	var src_id = $TestLayer.tile_set.add_source( _create_atlas_source() )
	#print(src_id)
	for x in range( w ):
		for y in range( h ):
			$TestLayer.set_cell( Vector2i( x, y ), src_id, Vector2i( x, y ) )
	
func _get_tile_offset_by_coords( x : int, y : int ) -> int:
	var rule_dict = {
		Vector2i(0, 0) : 5,
		Vector2i(w-1, 0) : 7,
		Vector2i(0, h-1) : 2,
		Vector2i(w-1, h-1) : 4
	}
	var dict_val = rule_dict.get( Vector2i( x, y ) )
	if dict_val != null: return int(dict_val)
	if y == 0: return 6
	elif y == h-1: return 3
	elif x == 0:
		if y % 2 == 1: return 8
		else: return 10
	elif x == w-1:
		if y % 2 == 1: return 11
		else: return 9
	elif y % 2 == 1: return 1
	else: return 0

	## Generating tile type for local adventure map:
	## >50% - should be of type that big_tile_type have
	## other part depends on the big tile neighbours
	## for example, if tile is grass, other 4 tiles are also grass
	## but also there are 2 steppens and 2 deserts then:
	## 50 + 6.25*4 - grass local tile chance
	## 6.25*2 - steppen and desert chances for each
func _get_tile_id_by_neighbours( big_tile_type : int, neighbours : Array[ int ] ) -> int:
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

func _ready() -> void:
	#set_process(true)
	for x in range( w ):
		for y in range( h ):
			var req_x = _get_tile_offset_by_coords( x, y )
			$TestLayer.set_cell( Vector2i( x, y ), 0,
						Vector2i( req_x, randi() % 7 ) )
