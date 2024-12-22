extends CharacterBody2D

var speed : float = 300.0
var click_pos = Vector2i()
var target_pos = Vector2i()
var DISTANSE_TO_START_MOVE : int = 3
var px_start_pos = 64


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	position = Vector2i( px_start_pos, px_start_pos )
	click_pos = position

func _physics_process( delta: float ) -> void:
	#pass
	if Input.is_action_just_pressed( "left_click" ):
		click_pos = get_global_mouse_position()
	if position.distance_to( click_pos ) > DISTANSE_TO_START_MOVE:
		target_pos = (click_pos - position).normalized()
		velocity = target_pos * speed
		move_and_slide()
