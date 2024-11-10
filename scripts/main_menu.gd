extends Control

@export var global_map_scene: PackedScene = preload("res://scenes/global_map.tscn")
@export var player_sc: PackedScene = preload("res://scenes/player_scene.tscn")

#-------------------Play button logic-------------------
func _on_play_pressed() -> void:
	var player_node = player_sc.instantiate()
	get_tree().root.add_child( player_node )
	#print( get_tree().root.get_children(), " ", global_map_scene )
	#print("Going to change scene")
	get_tree().root.add_child( global_map_scene.instantiate() )

#-------------------Quit button logic-------------------
func form_quit_dialog() -> ConfirmationDialog:
	var d = ConfirmationDialog.new()
	d.set_title("")
	d.set_text("Are you really want to quit?")
	
	# Connect the signals for OK and Cancel buttons
	d.get_ok_button().pressed.connect( _on_confirmed )
	d.get_cancel_button().pressed.connect( _on_canceled )
	
	return d

func _on_quit_pressed() -> void:
	var dialog = form_quit_dialog()
	get_tree().current_scene.add_child(dialog)  # Add dialog to the current scene
	dialog.popup_centered()  # Show the dialog centered on the screen

# This function will be called when OK is pressed
func _on_confirmed() -> void:
	get_tree().quit()  # This will close the game

# This function will be called when Cancel is pressed
func _on_canceled() -> void:
	pass  # Do nothing, just close the dialog
