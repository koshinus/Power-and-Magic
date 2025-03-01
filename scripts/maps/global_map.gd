extends Node2D

@export var px_tile_size : int = GLOBAL_MAP.GLOBAL_TILE_SIZE_IN_PIXELS
@export var layer_width : int = GLOBAL_MAP.GLOBAL_MAP_WIDTH
@export var layer_height : int = GLOBAL_MAP.GLOBAL_MAP_HEIGHT

func set_based_on_generated( world_info : Genarators.WorldInfo ) -> void:
    var loc_scenes = world_info.loc_scenes_info
    var src_id = $GlobalMapSurface.tile_set.add_source( loc_scenes.global_tset_source )
    for y in range( layer_height ):
        for x in range( layer_width ):
            var grid_pos : Vector2i = Vector2i( x, y )
            var scene_tile_id: int = loc_scenes.local_maps[ grid_pos ]
            $GlobalMapSurface.set_cell( grid_pos, src_id, Vector2i.ZERO, scene_tile_id )
            var loc_map_scene: PackedScene = $GlobalMapSurface.tile_set\
                                                .get_source( src_id )\
                                                .get_scene_tile_scene( scene_tile_id )
            add_child( LocalMap.create_from_packed_scene( loc_map_scene,
                            world_info.global_tiles_values, grid_pos,
                            Vector2( px_tile_size, px_tile_size ), false ) )
    print("Scenes total: ", get_child_count())
