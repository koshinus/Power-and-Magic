extends Node2D

@export var px_tile_size : int = GLOBAL_MAP.GLOBAL_TILE_SIZE_IN_PIXELS
@export var layer_width : int = GLOBAL_MAP.GLOBAL_MAP_WIDTH
@export var layer_height : int = GLOBAL_MAP.GLOBAL_MAP_HEIGHT

func set_based_on_generated( world_info : Genarators.WorldInfo ) -> void:
	var loc_w_px : int = GLOBAL_MAP.LOCAL_MAP_WIDTH*GLOBAL_MAP.LOCAL_TILE_SIZE_IN_PIXELS
	var loc_h_px : int = GLOBAL_MAP.LOCAL_MAP_HEIGHT*GLOBAL_MAP.LOCAL_TILE_SIZE_IN_PIXELS
	var loc_scenes = world_info.loc_scenes_info
	var src_id = $GlobalMapSurface.tile_set.add_source( loc_scenes.global_tset_source )
	var scale_vec : Vector2 = Vector2.ONE/Vector2( loc_w_px/px_tile_size, loc_h_px/px_tile_size )
	print( "New source id is ", src_id, " scale ", scale_vec )
	for y in range( layer_height ):
		for x in range( layer_width ):
			var scene_tile_id: int = loc_scenes.local_maps[ Vector2i( x, y ) ]
			var loc_map_scene: LocalMap = loc_scenes.global_tset_source.get_scene_tile_scene( scene_tile_id )
			loc_map_scene.scale = scale_vec
			$GlobalMapSurface.set_cell( Vector2i( x, y ), src_id, Vector2i.ZERO, scene_tile_id )
	#for y in range( layer_height ):
		#for x in range( layer_width ):
			#print( "[x,y]=", x,y, " tile id: ", $GlobalMapSurface.get_cell_alternative_tile( Vector2i(x,y) ) )
