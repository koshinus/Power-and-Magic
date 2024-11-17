extends Node2D

@export var px_tile_size : int = WorldConstants.GLOBAL_TILE_SIZE_IN_PIXELS
@export var layer_width : int = WorldConstants.GLOBAL_MAP_WIDTH
@export var layer_height : int = WorldConstants.GLOBAL_MAP_HEIGHT

@onready var local_tset : TileSet = preload( "res://data/global_map_tileset.tres" )


func _setup_limit( limit_side : CollisionShape2D, limit_size : Vector2i, limit_pos : Vector2i ) -> void:
	var cur_limits : RectangleShape2D = RectangleShape2D.new()
	cur_limits.set_size( limit_size )
	limit_side.shape = cur_limits
	limit_side.position = limit_pos

func _ready() -> void:
	_setup_limit( $Limits/TopLimit, Vector2i( layer_width * px_tile_size, 1 ),
					Vector2i( ( layer_width * px_tile_size )/2, 0 ) )
	
	_setup_limit( $Limits/BottomLimit, Vector2i( layer_width * px_tile_size, 1 ),
					Vector2i( ( layer_width * px_tile_size )/2, layer_height * px_tile_size ) )
	
	_setup_limit( $Limits/LeftLimit, Vector2i( 1, layer_height * px_tile_size ),
					Vector2i( 0, ( layer_height * px_tile_size )/2 ) )
	
	_setup_limit( $Limits/RightLimit, Vector2i( 1, layer_height * px_tile_size ),
					Vector2i( layer_width * px_tile_size, ( layer_height * px_tile_size )/2 ) )
	
	print( local_tset, " ", local_tset.get_source_count(),
						" ", local_tset.get_source( local_tset.get_source_id( 0 ) ) )
	var w_generator = WorldGenerator.MapGenerator.generate( local_tset, layer_width, layer_height )
	#var top = $Limits/TopLimit
	#var top_limits : RectangleShape2D = RectangleShape2D.new()
	#top_limits.set_size( Vector2i( layer_width * px_tile_size, 1 ) )
	#top.shape = top_limits
	#top.position = Vector2i( ( layer_width * px_tile_size )/2, 0 )
	
	#var bottom = $Limits/BottomLimit
	#var bot_limits : RectangleShape2D = RectangleShape2D.new()
	#bot_limits.set_size( Vector2i( layer_width * px_tile_size, 1 ) )
	#bottom.shape = bot_limits
	#bottom.position = Vector2i( ( layer_width * px_tile_size )/2, layer_height * px_tile_size )
	
	#var left = $Limits/LeftLimit
	#var left_limits : RectangleShape2D = RectangleShape2D.new()
	#left_limits.set_size( Vector2i( 1, layer_height * px_tile_size ) )
	#left.shape = left_limits
	#left.position = Vector2i( 0, ( layer_height * px_tile_size )/2 )
	
	#var right = $Limits/RightLimit
	#var right_limits : RectangleShape2D = RectangleShape2D.new()
	#right_limits.set_size( Vector2i( 1, layer_height * px_tile_size ) )
	#right.shape = right_limits
	#right.position = Vector2i( layer_width * px_tile_size, ( layer_height * px_tile_size )/2 )
	
