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
    
signal view_changed
func _on_btn_change_view_pressed() -> void:
    view_changed.emit()

signal magic_book_clicked
func _on_btn_magic_book_pressed() -> void:
    magic_book_clicked.emit()
