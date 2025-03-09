extends Control
class_name SkillButton

@export var skill_num : int = 0
@export var skill_group : int = 0
@export var texture : ImageTexture

signal skill_activated( toggled : bool, num : int, group : int )
func _on_btn_toggled( toggled_on: bool ) -> void:
    skill_activated.emit( toggled_on, skill_num, skill_group )

func _circled_texture( txtr : ImageTexture, color : Color, radius : int, center : Vector2 ) -> ImageTexture:
    var res_img : Image = txtr.get_image()
    var size : Vector2i = txtr.get_size()
    for y in range( size.y ):
        for x in range( size.x ):
            if ( Vector2(x, y) - center ).length() == radius:
                res_img.set_pixel( x, y, color )
    return ImageTexture.create_from_image( res_img )
    
func _grayscaled_texture( txtr : ImageTexture ) -> ImageTexture:
    var res_img : Image = txtr.get_image()
    var size : Vector2i = txtr.get_size()
    for y in range( size.y ):
        for x in range( size.x ):
            var color : Color = res_img.get_pixel( x, y )
            #Most popular algo for grayscailng was choosed: I=0.299R+0.587G+0.114B
            res_img.set_pixel( x, y, Color( color.r8*0.299, color.g8*0.587, color.b8*0.114 ) )
    return ImageTexture.create_from_image( res_img )
    
func enable_button( enable : bool ) -> void:
    $Btn.disabled = not enable

func setup_textures( txtr : ImageTexture ) -> void:
    $Btn.texture_normal = txtr
    #$Btn.texture_disabled = txtr
    #$Btn.texture_pressed = txtr
    $Btn.texture_disabled = _grayscaled_texture( txtr )
    $Btn.texture_pressed = _circled_texture( $Btn.texture_disabled, Color.YELLOW,
                                txtr.get_width()/2, txtr.get_size()/2 )

func _ready() -> void:
    pass
