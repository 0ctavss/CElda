extends CharacterBody2D


var speed = 30
var playerChase = false
var enemyAlive = true
var player = null
var playerInAttackZone = false
var enemyName = "Espectre"



func _physics_process(delta):

	dealDamage()

	if playerChase and enemyAlive == true:
		position += (player.position - position)/speed
		$AnimatedSprite2D.play("walk_front")

		#if (player.position.x - position.x) < 4 or (player.position.y - position.y) < 4:
			#$AnimatedSprite2D.play("attack")
			#await get_tree().create_timer(1.0).timeout

		if(player.position.x - position.x) < 0:
			$AnimatedSprite2D.flip_h = true
		else:
			$AnimatedSprite2D.flip_h = false

	else:
		if enemyAlive == false:
			$AnimatedSprite2D.play("die")
			global.currentPoints += 4
			await get_tree().create_timer(1.0).timeout
			self.queue_free()
		else:
			$AnimatedSprite2D.play("stand")


func _on_detection_area_body_entered(body:Node2D):
	player = body
	playerChase = true


func _on_detection_area_body_exited(body:Node2D):
	player = null
	playerChase = false


func _on_hitbox_body_entered(body:Node2D):
	if body.has_method("player"):
		playerInAttackZone = true


func _on_hitbox_body_exited(body:Node2D):
	if body.has_method("player"):
		playerInAttackZone = false

func enemy():
	pass

func dealDamage():
	if global.safeZone:
		playerChase = false
	if global.safeZone == false:
		if player != null:
			playerChase = true


	if playerInAttackZone and global.playerCurrentAttack == true:
		enemyAlive = false
