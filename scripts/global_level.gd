extends Node

var world_info : Genarators.WorldInfo

func _ready() -> void:
	world_info = Genarators.WorldGenerator.generate()
	$GlobalMap.set_based_on_generated( world_info.global_tset_source )

func _process( delta: float ) -> void:
	pass
	#if Input.is_action_just_pressed( "left_click" ):
		#var click_pos = get_viewport().get_mouse_position()
		#print("Clicked pos: ", click_pos)
		#for node in get_children():
			##print("Child of a type ", node.get_class())
			#if node is Control and node.get_global_rect().has_point( click_pos ):
				#print("Clicked node: ", node )
				#break


func _on_hero_hero_selected( info: HeroProperties.HeroInfo ) -> void:
	print("Info: ", info.a)
