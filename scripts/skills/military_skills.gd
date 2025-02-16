extends Control
class_name MilitarySkills

func _ready() -> void:
	$TextureRect/Offense11.setup_textures(
		ImageTexture.create_from_image( Image.load_from_file( "res://resources/samples/sword.png" ) ) )
