extends CharacterBody2D

var is_selected : bool = false

const speed : float = 300.0
var click_pos : Vector2i = Vector2i.ZERO
var DISTANSE_TO_START_MOVE : int = 3

@export var start_pos : int = GLOBAL_MAP.GLOBAL_TILE_SIZE_IN_PIXELS/2

func _ready() -> void:
	position = Vector2i( start_pos, start_pos )
	click_pos = position

func _physics_process( delta: float ) -> void:
	if not is_selected:
		return
	var pos_grid = $GridMovement.calculate_grid( position )
	var click_grid = $GridMovement.calculate_grid( click_pos )
	if Input.is_action_just_pressed( "left_click" ):
		click_pos = $GridMovement.calculate_grid_coords( get_global_mouse_position() )
		click_grid = $GridMovement.calculate_grid( click_pos )
		print("Click grid: ", click_grid, " pos grid: ", pos_grid)
		if click_grid == pos_grid:
			return
	if position.distance_to( click_pos ) > DISTANSE_TO_START_MOVE:
		var target_pos = (Vector2(click_pos) - position).normalized()
		velocity = target_pos * speed
		move_and_slide()

signal hero_selected( info: HeroProperties.HeroInfo )
func _on_hero_selected(selection_flag: bool) -> void:
	is_selected = selection_flag
	$HeroCam.enabled = selection_flag
	if not is_selected:
		click_pos = position
		return
	hero_selected.emit( HeroProperties.HeroInfo.new() )
