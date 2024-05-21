extends Node2D


var changeScene = load("res://floors/end_game_die.tscn")



func _on_level_complete_body_exited(body:Node2D):
	pass # Replace with function body.

func _on_level_complete_body_entered(body:Node2D):
	if body.has_method("player"):
		global.currentFloor = "die"
