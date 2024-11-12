extends Node2D

@export var px_tile_size : int = WorldConstants.GLOBAL_TILE_SIZE_IN_PIXELS
var layer_width = 100
var layer_height = 100

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	var top = $StaticBody2D/TopLimit
	var top_limits : RectangleShape2D = RectangleShape2D.new()
	top_limits.set_size( Vector2i( layer_width * px_tile_size * 2, 1 ) )
	top.shape = top_limits
	top.position = Vector2i( 0, 0 )
	
	var bottom = $StaticBody2D/BottomLimit
	var bot_limits : RectangleShape2D = RectangleShape2D.new()
	bot_limits.set_size( Vector2i( layer_width * px_tile_size * 2, 1 ) )
	bottom.shape = bot_limits
	bottom.position = Vector2i( 0, layer_height * px_tile_size )
	
	var left = $StaticBody2D/LeftLimit
	var left_limits : RectangleShape2D = RectangleShape2D.new()
	left_limits.set_size( Vector2i( 1, layer_height * px_tile_size * 2 ) )
	left.shape = left_limits
	left.position = Vector2i( 0, 0 )
	
	var right = $StaticBody2D/RightLimit
	var right_limits : RectangleShape2D = RectangleShape2D.new()
	right_limits.set_size( Vector2i( 1, layer_height * px_tile_size * 2 ) )
	right.shape = right_limits
	right.position = Vector2i( layer_width * px_tile_size, layer_height * px_tile_size )
	
	
# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass
