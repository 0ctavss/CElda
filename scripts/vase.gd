extends CharacterBody2D


var playerInAttackZone = false

func _physics_process(delta):
	destroy()

func _on_area_2d_body_entered(body:Node2D):
	if body.has_method("player"):
		playerInAttackZone = true


func _on_area_2d_body_exited(body:Node2D):
	if body.has_method("player"):
		playerInAttackZone = false

func destroy():
	if playerInAttackZone and global.playerCurrentAttack == true:
		self.queue_free()
		global.currentPoints += 10
		if global.playerCurrentHealth < 5:
			global.playerCurrentHealth += 1
		else:
			pass