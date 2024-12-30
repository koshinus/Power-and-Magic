extends Control

@export var global_map_scene: PackedScene = preload("res://scenes/global_map.tscn")
@export var player_sc: PackedScene = preload("res://scenes/player_scene.tscn")
@export var glob_interface: PackedScene = preload("res://scenes/interface/global_interface.tscn")

@export var test_sc: PackedScene = preload("res://scenes/test_node.tscn")

@export var px_tile_size : int = GLOBAL_MAP.GLOBAL_TILE_SIZE_IN_PIXELS

var world_info : Genarators.WorldInfo

#-------------------Play button logic-------------------
func _test_pressed() -> void:
	print(get_viewport(), " in main")
	var inst = test_sc.instantiate()
	var nn : Array[int] = [4,5,5,6]
	inst.init_by_params( 7, nn )
	get_tree().root.add_child( inst )

func _normal_pressed() -> void:
	world_info = Genarators.WorldGenerator.generate()
	
	var glob_node = glob_interface.instantiate()
	get_tree().root.add_child(glob_node)
	var player_node = player_sc.instantiate()
	get_tree().root.add_child( player_node )
	var map_node = global_map_scene.instantiate()
	map_node.set_based_on_generated( world_info.global_tset_source )
	get_tree().root.add_child( map_node )
	# If left buttons in the main scene player could accidentally click on them
	$MarginContainer.hide()

func _on_play_pressed() -> void:
	#_test_pressed()
	_normal_pressed()

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
