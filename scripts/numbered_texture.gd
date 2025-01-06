extends Control
class_name NumberedTexture

@export var hide_on_zero : bool = false
@export var button_is_active : bool = true
@export var button_texture : Texture2D

#@onready var amount : int = 0

func _ready() -> void:
	$VBoxContainer/BtnWithTexture.disabled = !button_is_active
	$VBoxContainer/BtnWithTexture.texture_normal = button_texture

func set_amount( new_amount : int ) -> void:
	#amount = new_amount
	$VBoxContainer/Amount.text = str( new_amount )
	if hide_on_zero and new_amount == 0:
		hide()

signal texture_activated
func _on_btn_pressed() -> void:
	texture_activated.emit()
