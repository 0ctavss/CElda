extends Node2D




func _on_level_complete_body_exited(body:Node2D):
	pass # Replace with function body.

func _on_level_complete_body_entered(body:Node2D):
	if body.has_method("player"):
		global.currentFloor += 1
		global.changeFloor = true
