extends CharacterBody2D

var speed : int = 300
var click_pos = Vector2i()
var target_pos = Vector2i()
var DISTANSE_TO_START_MOVE : int = 3

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	click_pos = position

## Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta: float) -> void:
	#pass

#func _enter_tree() -> void:
	#self.global_position = Vector2i( 50, 50 )

func _physics_process( delta: float ) -> void:
	#print(delta)
	if Input.is_action_just_pressed( "left_click" ):
		click_pos = get_global_mouse_position()
	if position.distance_to( click_pos ) > DISTANSE_TO_START_MOVE:
		target_pos = (click_pos - position).normalized()
		velocity = target_pos * speed
		move_and_slide()
