extends Node2D

@export var px_tile_size : int = GLOBAL_MAP.GLOBAL_TILE_SIZE_IN_PIXELS
@export var layer_width : int = GLOBAL_MAP.GLOBAL_MAP_WIDTH
@export var layer_height : int = GLOBAL_MAP.GLOBAL_MAP_HEIGHT

@onready var local_tset : TileSet = preload( "res://data/global_map_tileset.tres" )

func _setup_limit( limit_side : CollisionShape2D, limit_size : Vector2i, limit_pos : Vector2i ) -> void:
	var cur_limits : RectangleShape2D = RectangleShape2D.new()
	cur_limits.set_size( limit_size )
	limit_side.shape = cur_limits
	limit_side.position = limit_pos

func _ready() -> void:
	#_setup_limit( $Limits/TopLimit, Vector2i( layer_width * px_tile_size, 1 ),
					#Vector2i( ( layer_width * px_tile_size )/2, 0 ) )
	#
	#_setup_limit( $Limits/BottomLimit, Vector2i( layer_width * px_tile_size, 1 ),
					#Vector2i( ( layer_width * px_tile_size )/2, layer_height * px_tile_size ) )
	#
	#_setup_limit( $Limits/LeftLimit, Vector2i( 1, layer_height * px_tile_size ),
					#Vector2i( 0, ( layer_height * px_tile_size )/2 ) )
	#
	#_setup_limit( $Limits/RightLimit, Vector2i( 1, layer_height * px_tile_size ),
					#Vector2i( layer_width * px_tile_size, ( layer_height * px_tile_size )/2 ) )
	
	print( local_tset, " ", local_tset.get_source_count(),
						" ", local_tset.get_source( local_tset.get_source_id( 0 ) ) )
	#var map_info = WorldGenerator.MapGenerator.generate( local_tset, layer_width, layer_height )
	#map_info._global_tiles
	var tsource = TileSetAtlasSource.new()
	#tsource.margins
	var dynamic_tset_id = $GlobalMapSurface.tile_set.add_source( tsource )
	for x in range( layer_width ):
		for y in range( layer_height ):
			$GlobalMapSurface.set_cell( Vector2i( x, y ), dynamic_tset_id )
