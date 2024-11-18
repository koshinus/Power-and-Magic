extends Node2D

var w = 32
var h = 32

func _ready() -> void:
	for x in range( w ):
		for y in range( h ):
			
			$TileMapLayer.set_cell( Vector2i( x, y ), 0, Vector2i( randi() % 10, 0 ) )
	#print( "Generation result: ", stat_dict, " ", min_noise, " ", max_noise )


#extends Node2D
#
#func _ready():
	## Create a new TileSet
	#var tile_set = TileSet.new()
#
	## Define tile size
	#const TILE_SIZE = Vector2(32, 32)
#
	## Create a few tiles with different properties
	#for i in range(4):
		#var tile_id = i
		#
		## Create a rectangle shape for the tile
		#var shape = RectangleShape2D.new()
		#shape.extents = TILE_SIZE / 2  # Set extents (half the size)
#
		## Add the tile to the TileSet
		#tile_set.add_tile(tile_id, shape)
#
		## Optionally, set a collision shape for the tile
		#tile_set.tile_set_shape(tile_id, 0, shape)  # Using shape ID 0 for the first shape
		#
		## You can also define other properties like navigation, occluder shapes, etc.
#
	## Assign the TileSet to a TileMap or any other node that uses it
	#var tile_map = TileMap.new()
	#tile_map.set_tileset(tile_set)
	#
	## Set the position of the TileMap
	#tile_map.position = Vector2(0, 0)
	#
	## Add the TileMap to the scene
	#add_child(tile_map)
	#
	## Optionally, set some tiles in the TileMap
	#for x in range(10):
		#for y in range(10):
			#tile_map.set_cellv(Vector2(x, y), randi() % 4)  # Randomly assign one of the 4 tiles

##################### UNUSED CODE #####################

# Called when the node enters the scene tree for the first time.
#func _ready() -> void:
	#var tml = $TileMapLayer
	#tml.tile_set = TileSet.new()
	##tml.tile_set = create_tile_set()
	#var src_id = tml.tile_set.add_source( create_tile_set_source() )
	#for x in range(w):
		#for y in range(h):
			#tml.set_cell( Vector2i( x, y ), src_id )
#func create_tile_set_source() -> TileSetAtlasSource:
	#var tss = TileSetAtlasSource.new()
	#var txtr = Texture2D.new()
	#var plh = txtr.create_placeholder()
	#plh.set_size( Vector2i( w*64, h*64 ) )
	#tss.texture = txtr
	#for x in range(w):
		#for y in range(h):
			#tss.create_tile( Vector2i( x, y ), Vector2i( 64, 64 ) )
	#return tss
	#
#func create_tile_set() -> TileSet:
	#var tile_set = TileSet.new()
	## Define tile size
	#const TILE_SIZE = Vector2(32, 32)
	## Create a few tiles with different properties
	#for i in range(4):
		#var tile_id = i
		## Create a rectangle shape for the tile
		#var shape = RectangleShape2D.new()
		#shape.extents = TILE_SIZE / 2  # Set extents (half the size)
		## Add the tile to the TileSet
		#tile_set.add_tile(tile_id, shape)
		## Optionally, set a collision shape for the tile
		#tile_set.tile_set_shape(tile_id, 0, shape)  # Using shape ID 0 for the first shape
	#return tile_set
	
# For tilemap using astargrid

#var astar_grid : AStarGrid2D
#var glob_map : TileMapLayer
#var cur_id_path : Array[ Vector2i ]

#func _create_astar_grid( rect_region : Rect2i, tile_size : int ) -> AStarGrid2D:
	#var astar = AStarGrid2D.new()
	#astar.region = rect_region
	#astar.cell_size = Vector2i( tile_size, tile_size )
	#astar.diagonal_mode = AStarGrid2D.DIAGONAL_MODE_NEVER
	#astar.update()
	#
	#for x in rect_region.size.x:
		#for y in rect_region.size.y:
			#var tile_pos = Vector2i( x + rect_region.position.x, y + rect_region.position.y )
			#var tile_data = glob_map.get_cell_tile_data( tile_pos )
			#if tile_data == null or !tile_data.get_custom_data( "walkable" ):
				#astar.set_point_solid( tile_pos, true )
	#return astar
#
#func _input( event: InputEvent ) -> void:
	##if !event.is_action_pressed( "move" ):
	#if !event.is_action_pressed( "left_click" ):
		#return
		#
	#var start_from_pos : int = 1
	#var id_path = astar_grid.get_id_path(
		#glob_map.local_to_map( global_position ),
		#glob_map.local_to_map( get_global_mouse_position() )
	#).slice( start_from_pos )
	#
	#print(id_path)
	#
	#if !id_path.is_empty():
		#cur_id_path = id_path
#
#func _physics_process(delta: float) -> void:
	#if cur_id_path.is_empty():
		#return
	#
	#print("We are here")
	#var target_pos = glob_map.local_to_map( cur_id_path.front() )
	#global_position = global_position.move_toward( target_pos, 1 )
	#if global_position == Vector2(target_pos):
		#cur_id_path.pop_front()

#func _ready() -> void:
	#glob_map = $GlobalMapSurface
	#astar_grid = _create_astar_grid( glob_map.get_used_rect(), px_tile_size )
	#print( astar_grid )
