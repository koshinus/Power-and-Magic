extends CharacterBody2D

var is_selected : bool = false

const speed : float = 300.0
var click_pos : Vector2i = Vector2i.ZERO
var DISTANSE_TO_START_MOVE : int = 3

## Path calculation can be different from hero to hero:
## for example one hero uses "Fly" spell, while th other don't.
## To avoid recalculating AStarGrid2D on each hero switch, we need
## to store it hero, despite they share one TileMapLayer
var astar_grid_2d : AStarGrid2D = null
var astar_path : Array[Vector2i]
## For read purpose only and setup astar grid!!
var tml_ref : TileMapLayer

@export var start_pos : int = GLOBAL_MAP.GLOBAL_TILE_SIZE_IN_PIXELS/2

func set_tilemap_layer( tml : TileMapLayer, global_tiles_vals : Array[Array] ) -> void:
	tml_ref = tml
	var tsize = Vector2i.ONE*GLOBAL_MAP.GLOBAL_TILE_SIZE_IN_PIXELS
	astar_grid_2d = GridMovement.create_astar_stat( tml, global_tiles_vals, HeroProperties.HeroInfo.new(), tsize )

func _ready() -> void:
	position = Vector2i( start_pos, start_pos )
	click_pos = position

func process_row() -> void:
	var tsize = Vector2i.ONE*GLOBAL_MAP.GLOBAL_TILE_SIZE_IN_PIXELS
	var pos_grid = GridMovement.calculate_grid_stat( position, tsize )
	var click_grid = GridMovement.calculate_grid_stat( click_pos, tsize )
	if Input.is_action_just_pressed( "left_click" ):
		click_pos = GridMovement.calculate_grid_coords_stat( get_global_mouse_position(), tsize )
		click_grid = GridMovement.calculate_grid_stat( click_pos, tsize )
		print("Click grid: ", click_grid, " pos grid: ", pos_grid)
		if click_grid == pos_grid:
			return
	if position.distance_to( click_pos ) > DISTANSE_TO_START_MOVE:
		var target_pos = (Vector2(click_pos) - position).normalized()
		velocity = target_pos * speed
		move_and_slide()

func process_astar() -> void:
	var tsize = Vector2i.ONE*GLOBAL_MAP.GLOBAL_TILE_SIZE_IN_PIXELS
	var pos_grid = GridMovement.calculate_grid_stat( position, tsize )
	var is_left_click_pressed : bool = Input.is_action_just_pressed( "left_click" )
	var path_is_empty: bool = astar_path.is_empty()
	if is_left_click_pressed:
		if not path_is_empty:
			# ignoring left click while moving to the target position
			# TODO: in the future, there can be some more specific reaction
			# for example, stop current movement and recalculate path
			return
		click_pos = GridMovement.calculate_grid_coords_stat( get_global_mouse_position(), tsize )
		var click_grid = GridMovement.calculate_grid_stat( click_pos, tsize )
		if click_grid == pos_grid:
			return
		astar_path = GridMovement.get_grid_path( astar_grid_2d, pos_grid, click_grid )
		print("Result path: ", astar_path, " clicked grid ", click_grid)
	if astar_path.is_empty():
		return
	var next_grid_center = GridMovement.calculate_grid_coords_stat( astar_path.front()*tsize, tsize )
	if position.distance_to( next_grid_center ) <= DISTANSE_TO_START_MOVE:
		astar_path.pop_front()
		return
	var target_pos = (Vector2(next_grid_center) - position).normalized()
	velocity = target_pos * speed
	move_and_slide()

func _physics_process( delta: float ) -> void:
	if not is_selected:
		return
	if astar_grid_2d == null:
		process_row()
	else:
		process_astar()

signal hero_selected( info: HeroProperties.HeroInfo )
func _on_hero_selected(selection_flag: bool) -> void:
	is_selected = selection_flag
	$HeroCam.enabled = selection_flag
	if not is_selected:
		click_pos = position
		hero_selected.emit( null )
		return
	hero_selected.emit( HeroProperties.HeroInfo.new() )
