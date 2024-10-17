extends Control

var global_map_scene = preload("res://scenes/global_map.tscn").instantiate()

#-------------------Play button logic-------------------
func _on_play_pressed() -> void:
	#var dialog = AcceptDialog.new()
	#dialog.set_title("")
	#dialog.set_text("You clicked play!")
	#get_tree().current_scene.add_child(dialog)  # Add dialog to the current scene
	#dialog.popup_centered()  # Show the dialog centered on the screen
	#get_tree().change_scene_to_file()
	get_tree().root.add_child(global_map_scene)

#-------------------Quit button logic-------------------
func form_quit_dialog() -> ConfirmationDialog:
	var d = ConfirmationDialog.new()
	d.set_title("")
	d.set_text("Are you really want to quit?")
	
	# Connect the signals for OK and Cancel buttons
	d.get_ok_button().pressed.connect(_on_confirmed)
	d.get_cancel_button().pressed.connect(_on_canceled)
	
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
