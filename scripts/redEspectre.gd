extends CharacterBody2D

@export var bullet_scene: PackedScene

var speed = 30
var playerChase = false
var enemyAlive = true
var player = null
var playerInAttackZone = false
var enemyName = "Espectre"
var canShoot = false


func _physics_process(delta):

	dealDamage()
	if canShoot:
		shoot()

	if playerChase and enemyAlive == true:
		position += (player.position - position)/speed
		$AnimatedSprite2D.play("walk_front")

		#if (player.position.x - position.x) < 1000 or (player.position.y - position.y) < 1000:
			#$AnimatedSprite2D.play("attack")
			#await get_tree().create_timer(1.0).timeout

		if(player.position.x - position.x) < 200 and (player.position.x - position.x) > -200:
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
	if body.has_method("enemy"):
		if body.enemyName == "Rat":
			$AnimatedSprite2D.play("scared")
			speed = 0
			print("un ratón")
	elif body.has_method("player"):
		canShoot = true
		player = body
		playerChase = true
		print("vi algo")


func _on_detection_area_body_exited(body:Node2D):
	if body.has_method("enemy"):
		if body.enemyName == "Rat":
			$AnimatedSprite2D.play("stand")
			speed = 30
	elif body.has_method("player"):
		canShoot = false
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

func shoot():
	var bullet_instance = bullet_scene.instantiate()
	get_parent().add_child(bullet_instance)
    
	global.iniX = position.x
	global.iniY = position.y