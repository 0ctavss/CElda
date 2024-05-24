extends CharacterBody2D

var chestOpen = false

func _ready():
	$AnimatedSprite2D.play("close")

func _on_area_2d_body_entered(body:Node2D):
	if body.has_method("player"):
		if chestOpen:
			pass
		else:
			$AnimatedSprite2D.play("open")
			global.currentChestOpen += 1
			global.currentPoints += 1000 
			chestOpen = true
