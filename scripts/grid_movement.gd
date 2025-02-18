@tool
extends Node
class_name GridMovement

@export var tile_size : Vector2i = Vector2i.ONE

static func _is_passable( tdata : TileData, glob_tile_val : int, hero_info : HeroProperties.HeroInfo ) -> bool:
	if glob_tile_val != -1:
		return glob_tile_val not in [GLOBAL_MAP.TYPES.DEEP_WATER, GLOBAL_MAP.TYPES.WATER, GLOBAL_MAP.TYPES.MOUNTAINE]
	# TODO: add checks based on race and actual effects
	var passable = tdata.get_custom_data( "terrain_t" )
	match( passable ):
		TYPE_BOOL: return passable
	return true

static func create_astar_stat( tml : TileMapLayer, glob_tiles_vals : Array[Array],
			hero_info : HeroProperties.HeroInfo, tsize : Vector2i ) -> AStarGrid2D:
	var used_rect : Rect2i = tml.get_used_rect()
	var astar_grid_2d : AStarGrid2D = AStarGrid2D.new()
	astar_grid_2d.region = used_rect
	astar_grid_2d.cell_size = tsize
	astar_grid_2d.diagonal_mode = AStarGrid2D.DIAGONAL_MODE_ALWAYS
	astar_grid_2d.update()
	reset_tiles_passability( astar_grid_2d, tml, glob_tiles_vals, hero_info )
	return astar_grid_2d

static func reset_tiles_passability( astar_grid: AStarGrid2D, tml : TileMapLayer,
			glob_tiles_vals : Array[Array], hero_info : HeroProperties.HeroInfo ) -> void:
	var used_rect : Rect2i = tml.get_used_rect()
	for y in used_rect.size.y:
		for x in used_rect.size.x:
			var tile_pos = Vector2i(x, y) + used_rect.position
			var tdata : TileData = tml.get_cell_tile_data( tile_pos )
			var glob_tile_val : int = -1
			if !glob_tiles_vals.is_empty():
				glob_tile_val = glob_tiles_vals[x][y]
			if tdata == null or not _is_passable( tdata, glob_tile_val, hero_info ):
				astar_grid.set_point_solid( tile_pos )

static func get_grid_path( astar_grid_2d : AStarGrid2D, start_point : Vector2i, end_point : Vector2i ) -> Array[Vector2i]:
	if astar_grid_2d == null:
		return []
	return astar_grid_2d.get_id_path( start_point, end_point )

static func calculate_grid_coords_stat( coords : Vector2i, tsize : Vector2i ) -> Vector2i:
	var grid_coords : Vector2i = coords/tsize
	return grid_coords*tsize + tsize/2

static func calculate_grid_stat( coords : Vector2i, tsize : Vector2i ) -> Vector2i:
	return coords/tsize

func create_astar( tml : TileMapLayer, glob_tiles_vals : Array[Array], hero_info : HeroProperties.HeroInfo ) -> AStarGrid2D:
	return create_astar_stat( tml, glob_tiles_vals, hero_info, tile_size )

func calculate_grid_coords( coords : Vector2i ) -> Vector2i:
	return calculate_grid_coords_stat( coords, tile_size )

func calculate_grid( coords : Vector2i ) -> Vector2i:
	return calculate_grid_stat( coords, tile_size )
	
