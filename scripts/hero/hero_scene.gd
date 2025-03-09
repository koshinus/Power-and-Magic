extends CharacterBody2D

var is_selected : bool = false

const VECTOR_MINUS_ONE : Vector2 = Vector2( -1,-1 )
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

func process_row( cur_pos: Vector2 ) -> Vector2:
    var tsize = Vector2i.ONE*GLOBAL_MAP.GLOBAL_TILE_SIZE_IN_PIXELS
    var pos_grid = GridMovement.calculate_grid_stat( cur_pos, tsize )
    var click_grid = GridMovement.calculate_grid_stat( click_pos, tsize )
    if Input.is_action_just_pressed( "left_click" ):
        click_pos = GridMovement.calculate_grid_coords_stat( get_global_mouse_position(), tsize )
        click_grid = GridMovement.calculate_grid_stat( click_pos, tsize )
        print("Click grid: ", click_grid, " pos grid: ", pos_grid)
        if click_grid == pos_grid:
            return VECTOR_MINUS_ONE
    if cur_pos.distance_to( click_pos ) <= DISTANSE_TO_START_MOVE:
        return VECTOR_MINUS_ONE
    return (Vector2(click_pos) - cur_pos).normalized()

func process_astar( cur_pos: Vector2 ) -> Vector2:
    var tsize = Vector2i.ONE*GLOBAL_MAP.GLOBAL_TILE_SIZE_IN_PIXELS
    var pos_grid = GridMovement.calculate_grid_stat( cur_pos, tsize )
    var is_left_click_pressed : bool = Input.is_action_just_pressed( "left_click" )
    var path_is_empty: bool = astar_path.is_empty()
    if is_left_click_pressed:
        if not path_is_empty:
            # ignoring left click while moving to the target position
            # TODO: in the future, there can be some more specific reaction
            # for example, stop current movement and recalculate path
            return VECTOR_MINUS_ONE
        click_pos = GridMovement.calculate_grid_coords_stat( get_global_mouse_position(), tsize )
        var click_grid = GridMovement.calculate_grid_stat( click_pos, tsize )
        if click_grid == pos_grid:
            return VECTOR_MINUS_ONE
        astar_path = GridMovement.get_grid_path( astar_grid_2d, pos_grid, click_grid )
        print("Result path: ", astar_path, " clicked grid ", click_grid)
    if astar_path.is_empty():
        return VECTOR_MINUS_ONE
    var next_grid_center = GridMovement.calculate_grid_coords_stat( astar_path.front()*tsize, tsize )
    if cur_pos.distance_to( next_grid_center ) <= DISTANSE_TO_START_MOVE:
        astar_path.pop_front()
        return VECTOR_MINUS_ONE
    return (Vector2(next_grid_center) - cur_pos).normalized()


func _physics_process( delta: float ) -> void:
    if not is_selected:
        return
    var target_pos : Vector2 = VECTOR_MINUS_ONE
    if astar_grid_2d == null:
        target_pos = process_row( position )
    else:
        target_pos = process_astar( position )
    if target_pos == VECTOR_MINUS_ONE:
        return
    velocity = target_pos * speed
    move_and_slide()

signal hero_selected( info: HeroProperties.HeroInfo )
func _on_hero_selected(selection_flag: bool) -> void:
    is_selected = selection_flag
    $HeroCam.enabled = selection_flag
    if not is_selected:
        click_pos = position
        hero_selected.emit( null )
        return
    hero_selected.emit( HeroProperties.HeroInfo.new() )
