extends Control
class_name SkillButton

#@export var texture : Texture2D
@export var skill_num : int = 0
@export var skill_group : int = 0
@export var texture : Texture2D

signal skill_activated( toggled : bool, num : int, group : int )
func _on_btn_toggled( toggled_on: bool ) -> void:
	skill_activated.emit( toggled_on, skill_num, skill_group )

func _ready() -> void:
	$Btn.texture_pressed = texture
	$Btn.texture_disabled = texture
	$Btn.texture_normal = texture
