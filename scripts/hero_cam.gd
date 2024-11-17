extends Camera2D

@export var px_tile_size : int = WorldConstants.GLOBAL_TILE_SIZE_IN_PIXELS
@export var layer_width : int = WorldConstants.GLOBAL_MAP_WIDTH
@export var layer_height : int = WorldConstants.GLOBAL_MAP_HEIGHT

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	self.limit_left = 0
	self.limit_top = 0
	self.limit_right = layer_width * px_tile_size
	self.limit_bottom = layer_height * px_tile_size

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass
