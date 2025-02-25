extends CanvasLayer

func show_hero_depending_parts( info: HeroProperties.HeroInfo ) -> void:
	print( "Info is ", info )
	if info == null:
		$HBoxArmy.hide()
		$HeroPanel.hide()
		$HBoxAdditionalButtons.hide()
	else:
		$HBoxArmy.show()
		$HeroPanel.show()
		$HBoxAdditionalButtons.show()

func _ready() -> void:
	$HBoxArmy.hide()
	$HeroPanel.hide()
	$HBoxAdditionalButtons.hide()
	
