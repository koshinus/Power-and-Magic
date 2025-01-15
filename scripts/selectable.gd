extends Control
class_name Selectable

signal selected( selection_flag : bool )

@export var exclusive = true
@export var group_name : String

var is_selected : bool = false : set = set_selected

func set_selected( selection_flag : bool ):
	print("Setting selected to ", selection_flag, " for node ", self)
	if selection_flag:
		_make_exclusive()
		add_to_group( group_name )
	else:
		$Button.release_focus()
		remove_from_group( group_name )
	is_selected = selection_flag
	selected.emit( is_selected )

func _make_exclusive():
	if exclusive:
		get_tree().call_group( group_name, "set_selected", false )

func _on_button_pressed() -> void:
	set_selected( not is_selected )
