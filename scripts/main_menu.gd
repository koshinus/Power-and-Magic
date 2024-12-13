extends Control

@export var global_map_scene: PackedScene = preload("res://scenes/global_map.tscn")
@export var player_sc: PackedScene = preload("res://scenes/player_scene.tscn")

@export var test_sc: PackedScene = preload("res://scenes/test_node.tscn")

@export var px_tile_size : int = GLOBAL_MAP.GLOBAL_TILE_SIZE_IN_PIXELS

#-------------------Play button logic-------------------
func _test_pressed() -> void:
	get_tree().root.add_child( test_sc.instantiate() )

func _normal_pressed() -> void:
	var local_tset_texture : CompressedTexture2D = load( "res://resources/tilesets/tileset_local_1600.png" )
	var world_info : Genarators.WorldInfo = Genarators.WorldGenerator.generate( local_tset_texture.get_image() )
	
	var player_node = player_sc.instantiate()
	get_tree().root.add_child( player_node )
	var map_node = global_map_scene.instantiate()
	map_node.set_based_on_generated( world_info.global_tset_source )
	get_tree().root.add_child( map_node )

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
