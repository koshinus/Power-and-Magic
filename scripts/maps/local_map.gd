extends Node2D
class_name LocalMap

## Generating tile type for local adventure map:
## >=50% - should be of type that big_tile_type have
## other part depends on the big tile neighbours
## for example, if tile is grass, other 4 tiles are also grass
## but also there are 2 steppens and 2 deserts then:
## 50 + 6.25*4 - grass local tile chance
## 6.25*2 - steppen and desert chances for each
func _get_local_tile_type_by_neighbours( big_tile_type : int, neighbours : Array[ int ] ) -> int:
    neighbours.sort()
    var tiles_arr : Array[int]
    tiles_arr.resize( neighbours.size() )
    tiles_arr.fill( big_tile_type )
    var idx = neighbours.find( big_tile_type )
    if idx == -1:
        neighbours.append_array( tiles_arr )
    else:
        for i in tiles_arr:
            neighbours.insert( idx, i )
    return neighbours[ randi() % neighbours.size() ]
    
func _get_tile_offset_by_coords( x : int, y : int ) -> int:
    var w : int = GLOBAL_MAP.LOCAL_MAP_WIDTH
    var h : int = GLOBAL_MAP.LOCAL_MAP_HEIGHT
    var rule_dict = {
        Vector2i(0, 0) : GLOBAL_MAP.LOCAL_TILES.TOP_LEFT,
        Vector2i(w-1, 0) : GLOBAL_MAP.LOCAL_TILES.TOP_RIGHT,
        Vector2i(0, h-1) : GLOBAL_MAP.LOCAL_TILES.BOTTOM_LEFT,
        Vector2i(w-1, h-1) : GLOBAL_MAP.LOCAL_TILES.BOTTOM_RIGHT
    }
    var dict_val = rule_dict.get( Vector2i( x, y ) )
    if dict_val != null: return int(dict_val)
    if y == 0: return GLOBAL_MAP.LOCAL_TILES.TOP
    elif y == h-1: return GLOBAL_MAP.LOCAL_TILES.BOTTOM
    elif x == 0:
        if y % 2 == 1: return GLOBAL_MAP.LOCAL_TILES.LEFT_ODD
        else: return GLOBAL_MAP.LOCAL_TILES.LEFT_EVEN
    elif x == w-1:
        if y % 2 == 1: return GLOBAL_MAP.LOCAL_TILES.RIGHT_ODD
        else: return GLOBAL_MAP.LOCAL_TILES.RIGHT_EVEN
    elif y % 2 == 1: return GLOBAL_MAP.LOCAL_TILES.MIDDLE_ODD
    else: return GLOBAL_MAP.LOCAL_TILES.MIDDLE_EVEN

func init_by_params( global_tile_type : int, neighbours : Array[int] ) -> void:
    var w : int = GLOBAL_MAP.LOCAL_MAP_WIDTH
    var h : int = GLOBAL_MAP.LOCAL_MAP_HEIGHT
    for y in range( h ):
        for x in range( w ):
            var tile_x_offset = _get_tile_offset_by_coords( x, y )
            var tile_y_offset = _get_local_tile_type_by_neighbours( global_tile_type, neighbours.duplicate() )
            var tileset_offset : Vector2i = Vector2i( tile_x_offset, tile_y_offset )
            $LocalMapSurface.set_cell( Vector2i( x, y ), 0, tileset_offset )

static func _get_neighbours( glob_tiles_vals : Array[Array], i : int, j : int ) -> Array[int]:		
    var neighbours : Array[int]
    var rows = glob_tiles_vals.size()
    var cols = glob_tiles_vals.front().size()
    # Define the possible relative positions for neighbours
    var directions : Array[Vector2i] = [
        Vector2i(-1,-1), Vector2i(-1, 0), Vector2i(-1,1), # Top-left,    Top   , Top-right
        Vector2i( 0,-1),                  Vector2i( 0,1), # Left,          	   , Right
        Vector2i( 1,-1), Vector2i( 1, 0), Vector2i( 1,1)  # Bottom-left, Bottom, Bottom-right
    ];
    # Check each direction for valid neighbours
    for dir in directions:
        var new_row : int = i + dir.x;
        var new_col : int = j + dir.y;
        # Check if the new position is within bounds
        if new_row >= 0 && new_row < rows && new_col >= 0 && new_col < cols:
            neighbours.push_back( glob_tiles_vals[new_row][new_col] )
    return neighbours

static func create_from_packed_scene( loc_map_scene : PackedScene,
                                        global_tiles_values : Array[Array],
                                        grid_pos : Vector2i, orig_size: Vector2,
                                        show_grid : bool ) -> LocalMap:
    var loc_map = loc_map_scene.instantiate()
    if not( loc_map is LocalMap ):
        return null
    var x = grid_pos.x
    var y = grid_pos.y
    loc_map.init_by_params( global_tiles_values[x][y],
                _get_neighbours( global_tiles_values, x, y ) )                
    var loc_w_px : int = GLOBAL_MAP.LOCAL_MAP_WIDTH*GLOBAL_MAP.LOCAL_TILE_SIZE_IN_PIXELS
    var loc_h_px : int = GLOBAL_MAP.LOCAL_MAP_HEIGHT*GLOBAL_MAP.LOCAL_TILE_SIZE_IN_PIXELS
    var scale_vec : Vector2 = orig_size/Vector2( loc_w_px, loc_h_px )
    loc_map.scale = scale_vec
    loc_map.position = Vector2i( x,y )*Vector2i( orig_size )
    loc_map.get_node( "Grid2DNode" ).visible = show_grid
    return loc_map
