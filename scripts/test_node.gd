extends Node2D

var img : ImageTexture = ImageTexture.create_from_image(
			Image.load_from_file( "res://resources/samples/flower_field.png" ) )

func _circled_texture( txtr : ImageTexture, color : Color, radius : int, center : Vector2 ) -> ImageTexture:
	var res_img : Image = txtr.get_image()
	var size : Vector2i = txtr.get_size()
	print("Size is", size)
	for y in range(size.y):
		for x in range(size.x):
			var dist : float = ( Vector2(x, y) - center ).length()
			# If print only equal to the radius then circle will not be seen
			if dist <= radius and dist >= radius-3:
				res_img.set_pixel( x, y, color )
	return ImageTexture.create_from_image( res_img )
	
func _grayscaled_texture( txtr : ImageTexture ) -> ImageTexture:
	var res_img : Image = txtr.get_image()
	var size : Vector2i = txtr.get_size()
	for y in range(size.y):
		for x in range(size.x):
			var color : Color = res_img.get_pixel( x, y )
			var grayed = ( color.r + color.g + color.b )/3
			res_img.set_pixel( x, y, Color( grayed, grayed, grayed ) )
	return ImageTexture.create_from_image( res_img )

func _on_normal_pressed() -> void:
	$TextureRect.texture = img

func _on_grey_pressed() -> void:
	$TextureRect.texture = _grayscaled_texture( img )

func _on_circuled_pressed() -> void:
	$TextureRect.texture = _circled_texture( img, Color.GOLD, 100, Vector2( 300, 300 ) )
