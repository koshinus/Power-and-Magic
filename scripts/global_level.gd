extends Node

var world_info : Genarators.WorldInfo

func _ready() -> void:
	world_info = Genarators.WorldGenerator.generate()
	$GlobalMap.set_based_on_generated( world_info.global_tset_source )
	$MilitaryHero.set_tilemap_layer( $GlobalMap/GlobalMapSurface, world_info.global_tiles_values )
	$EconomicHero.set_tilemap_layer( $GlobalMap/GlobalMapSurface, world_info.global_tiles_values )
	$MilitaryHero.hero_selected.connect( _on_hero_hero_selected )
	$EconomicHero.hero_selected.connect( _on_hero_hero_selected )

func _on_hero_hero_selected( info: HeroProperties.HeroInfo ) -> void:
	if info != null:
		print("Info spec: ", info.specialization)
	$GlobalInterface.show_hero_depending_parts( info )
