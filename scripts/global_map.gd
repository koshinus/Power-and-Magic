extends Node2D

@export var px_tile_size : int = GLOBAL_MAP.GLOBAL_TILE_SIZE_IN_PIXELS
@export var layer_width : int = GLOBAL_MAP.GLOBAL_MAP_WIDTH
@export var layer_height : int = GLOBAL_MAP.GLOBAL_MAP_HEIGHT

func _ready() -> void:
	pass
	#var map_info = WorldGenerator.MapGenerator.generate( local_tset, layer_width, layer_height )
	#map_info._global_tiles
	#var tsource = TileSetAtlasSource.new()
	##tsource.margins
	#var dynamic_tset_id = $GlobalMapSurface.tile_set.add_source( tsource )
	#for x in range( layer_width ):
		#for y in range( layer_height ):
			#$GlobalMapSurface.set_cell( Vector2i( x, y ), dynamic_tset_id )

func set_based_on_generated( global_tsource : TileSetAtlasSource ) -> void:
	var src_id = $GlobalMapSurface.tile_set.add_source( global_tsource )
	print( src_id )
	for x in range( layer_width ):
		for y in range( layer_height ):
			$GlobalMapSurface.set_cell( Vector2i( x, y ), src_id, Vector2i( x, y ) )
	
