extends Node2D




func _on_level_complete_body_exited(body:Node2D):
	pass # Replace with function body.

func _on_level_complete_body_entered(body:Node2D):
	if body.has_method("player"):
		global.currentFloor += 1
		global.healthFloor = global.playerCurrentHealth
		global.changeFloor = true



func _on_safe_zone_body_exited(body:Node2D):
	if body.has_method("player"):
		global.safeZone = false


func _on_safe_zone_body_entered(body:Node2D):
	if body.has_method("player"):
		global.safeZone = true
