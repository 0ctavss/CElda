extends CharacterBody2D

var playerInAttackZone = false

func _physics_process(delta):
	destroy()

func _on_area_2d_body_entered(body:Node2D):
	if body.has_method("player"):
		playerInAttackZone = true

func destroy():
	if playerInAttackZone:
		self.queue_free()
		global.playerCurrentHealth -= 1
	else:
		pass