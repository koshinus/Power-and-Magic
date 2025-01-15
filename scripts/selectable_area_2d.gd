extends Area2D
class_name SelectableArea2D

signal selection_toggled( selection_flag : bool )

const GROUP_SELECTED : String = "selected";

@export var exclusive = true
#@export var selection_action : String = "select"
@export var selection_action : String = "left_click"
#@export var collision_shape : CollisionShape2D

var selected : bool = false : set = set_selected

func set_selected( selection_flag : bool ):
	if selection_flag:
		_make_exclusive()
		add_to_group( GROUP_SELECTED )
	else:
		remove_from_group( GROUP_SELECTED )
	selected = selection_flag
	selection_toggled.emit( selected )

func _make_exclusive():
	if exclusive:
		get_tree().call_group( GROUP_SELECTED, "set_selected", false )

func _input_event( viewport: Viewport, event: InputEvent, shape_idx: int ) -> void:
	if event.is_action_pressed( selection_action ):
		set_selected( not selected )
