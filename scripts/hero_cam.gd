extends Camera2D

@export var px_tile_size : int = WorldConstants.GLOBAL_TILE_SIZE_IN_PIXELS

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	self.limit_left = 0
	self.limit_top = 0
	self.limit_right = 100 * px_tile_size
	self.limit_bottom = 100 * px_tile_size

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass
