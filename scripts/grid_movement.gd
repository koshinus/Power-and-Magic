extends Node
class_name GridMovement

@export var tile_size : Vector2i = Vector2i.ONE

func calculate_grid_coords_( mouse_coords : Vector2i,
							body_coords : Vector2i ) -> Vector2i:
	var body_grid : Vector2i = body_coords/tile_size
	var mouse_grid : Vector2i = mouse_coords/tile_size
	if body_grid == mouse_grid:
		return Vector2i.ZERO
	else:
		return mouse_grid*tile_size + tile_size/2

func calculate_grid_coords( coords : Vector2i ) -> Vector2i:
	var grid_coords : Vector2i = coords/tile_size
	return grid_coords*tile_size + tile_size/2

func calculate_grid( coords : Vector2i ) -> Vector2i:
	return coords/tile_size
