@tool
extends StaticBody2D
class_name MapLimitations

## Tool for setting border limitations of the map

@export var map_width : int = 0
@export var map_height : int = 0
@export var tile_size : Vector2i = Vector2i( 0, 0 )

func _setup_limit( limit_side : CollisionShape2D, limit_size : Vector2i, limit_pos : Vector2i ) -> void:
	var cur_limits : RectangleShape2D = RectangleShape2D.new()
	cur_limits.set_size( limit_size )
	limit_side.shape = cur_limits
	limit_side.position = limit_pos

func _ready() -> void:
	_setup_limit( $TopLimit, Vector2i( map_width * tile_size.x, 1 ),
					Vector2i( ( map_width * tile_size.x )/2, 0 ) )
	_setup_limit( $BottomLimit, Vector2i( map_width * tile_size.x, 1 ),
					Vector2i( ( map_width * tile_size.x )/2, map_height * tile_size.y ) )
	_setup_limit( $LeftLimit, Vector2i( 1, map_height * tile_size.y ),
					Vector2i( 0, ( map_height * tile_size.y )/2 ) )
	_setup_limit( $RightLimit, Vector2i( 1, map_height * tile_size.y ),
					Vector2i( map_width * tile_size.x, ( map_height * tile_size.y )/2 ) )
