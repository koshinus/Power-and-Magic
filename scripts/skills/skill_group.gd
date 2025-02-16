@tool
extends Node

class SkillLevel:
	var buttons: Array[SkillButton]
	func activate_lvl( enable : bool ) -> void:
		for b in buttons:
			b.enable_button( enable )

var beginers_lvl: SkillLevel
var advanced_lvl: SkillLevel
var expert_lvl: SkillLevel
var _activated_num : int = 0

@export var group_num: int = 0
@export var advanced_threshold: int = 2
@export var expert_threshold: int = 4

func setup_group( beginer: SkillLevel, advanced: SkillLevel,
				  expert : SkillLevel, skills_dict: Dictionary ) -> void:
	beginers_lvl = beginer
	for b in beginers_lvl.buttons:
		b.skill_activated.connect( on_skill_activated )
	advanced_lvl = advanced
	for b in advanced_lvl.buttons:
		b.skill_activated.connect( on_skill_activated )
	expert_lvl = expert
	for b in expert_lvl.buttons:
		b.skill_activated.connect( on_skill_activated )
	var group_skills = skills_dict.get( group_num )
	if group_skills == null:
		return
	_activated_num = group_skills.values().reduce( func( accum, number ): return accum + number, 0 )

func _recal_lvl_state( lvl: SkillLevel, before : int, after: int, threshold : int ) -> void:
	if ( before >= threshold and after >= threshold ) or\
		( before < threshold and after < threshold ):
		return
	if before >= threshold and after < threshold:
		lvl.activate_lvl( false )
		return
	if before < threshold and after >= threshold:
		lvl.activate_lvl( true )
		return

## We should activate level just after achieving some threshold
func _recalculate_lvls_state( before : int, after: int ) -> void:
	_recal_lvl_state( beginers_lvl, before, after, 0 )
	_recal_lvl_state( advanced_lvl, before, after, advanced_threshold )
	_recal_lvl_state( expert_lvl, before, after, expert_threshold )

func on_skill_activated( toggled : bool, num : int, group : int ) -> void:
	var new_activated : int = _activated_num
	if toggled:
		new_activated = new_activated + 1
	else:
		new_activated = max( new_activated - 1, 0 )
	_recalculate_lvls_state( _activated_num, new_activated )
	_activated_num = new_activated
