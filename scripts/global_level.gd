extends Node

var world_info : Genarators.WorldInfo

func _ready() -> void:
	world_info = Genarators.WorldGenerator.generate()
	$GlobalMap.set_based_on_generated( world_info.global_tset_source )
	$MilitaryHero.set_tilemap_layer( $GlobalMap/GlobalMapSurface, world_info.global_tiles_values )
	$EconomicHero.set_tilemap_layer( $GlobalMap/GlobalMapSurface, world_info.global_tiles_values )

func _process( delta: float ) -> void:
	pass

func _on_hero_hero_selected( info: HeroProperties.HeroInfo ) -> void:
	print("Info spec: ", info.specialization)
