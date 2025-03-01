extends Node

var world_info : Genarators.WorldInfo
var grid_pos : Vector2i = Vector2i.ZERO

var lvl_window : LocalLevel

func _ready() -> void:
    lvl_window = preload( "res://scenes/maps/local_level.tscn" ).instantiate()
    lvl_window.hide()
    
    world_info = Genarators.WorldGenerator.generate()
    $GlobalMap.set_based_on_generated( world_info )
    $MilitaryHero.set_tilemap_layer( $GlobalMap/GlobalMapSurface, world_info.global_tiles_values )
    $EconomicHero.set_tilemap_layer( $GlobalMap/GlobalMapSurface, world_info.global_tiles_values )
    $MilitaryHero.hero_selected.connect( _on_hero_hero_selected )
    $EconomicHero.hero_selected.connect( _on_hero_hero_selected )
    $GlobalInterface.view_changed.connect( _on_view_changed ) 

func _on_hero_hero_selected( info: HeroProperties.HeroInfo ) -> void:
    grid_pos = Vector2i.ZERO
    if info != null:
        grid_pos = info.grid_pos
        print( "Info spec: ", info.specialization )
    $GlobalInterface.show_hero_depending_parts( info )

func _on_view_changed() -> void:
    if grid_pos == Vector2i.ZERO:
        return
    #lvl_window.
    #lvl_window.visible = not lvl_window.visible
