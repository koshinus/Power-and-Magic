extends CharacterBody2D

var is_selected : bool = false

var speed : float = 300.0
var click_pos = Vector2i()
var target_pos = Vector2i()
var DISTANSE_TO_START_MOVE : int = 3
#var px_start_pos : int = ( GLOBAL_MAP.GLOBAL_TILE_SIZE_IN_PIXELS/2 +
						   #GLOBAL_MAP.GLOBAL_TILE_SIZE_IN_PIXELS*2 )
@export var start_pos : int = GLOBAL_MAP.GLOBAL_TILE_SIZE_IN_PIXELS/2

func _ready() -> void:
	position = Vector2i( start_pos, start_pos )
	click_pos = position

func _physics_process( delta: float ) -> void:
	if not is_selected:
		return
	if Input.is_action_just_pressed( "left_click" ):
		click_pos = get_global_mouse_position()
	if position.distance_to( click_pos ) > DISTANSE_TO_START_MOVE:
		target_pos = (click_pos - position).normalized()
		velocity = target_pos * speed
		move_and_slide()

signal hero_selected( info: HeroProperties.HeroInfo )
func _on_hero_selected(selection_flag: bool) -> void:
	is_selected = selection_flag
	$HeroCam.enabled = selection_flag
	if not is_selected:
		return
	var hero_info = HeroProperties.HeroInfo.new()
	hero_info.a = 87
	hero_selected.emit( hero_info )
