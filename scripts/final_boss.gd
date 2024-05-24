extends CharacterBody2D

@export var bullet_scene: PackedScene


var speed = 90
var playerChase = false
var enemyAlive = true
var life = 200
var player = null
var playerInAttackZone = false
var enemyName = "Boss"
var canShoot = false
var is_paused = false
var detection_radius: float = 1000.0  
var attack_animation_threshold_y: float = 600.0


func _physics_process(delta):
	dealDamage()
	if is_paused:
		return
	if canShoot:
		shoot()

	if playerChase and enemyAlive == true:
		speed = 90
		position += (player.position - position)/speed
		$AnimatedSprite2D.play("walk")
		check_attack_zone()
		if player.position.x - position.x == 0:
			canShoot = true

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
			global.currentPoints += 15
			await get_tree().create_timer(1.0).timeout
			self.queue_free()
		else:
			$AnimatedSprite2D.play("afk")


func _on_detection_area_body_entered(body:Node2D):
	if body.has_method("enemy"):
		if body.enemyName == "Rat":
			$AnimatedSprite2D.play("scared")
			speed = 0
			print("un ratón")
	elif body.has_method("player"):
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
		if life == 0:
			enemyAlive = false
		else:
			$AnimatedSprite2D.play("hurt")
			life -= 1

func shoot():
	var bullet_instance = bullet_scene.instantiate()
	get_parent().add_child(bullet_instance)
	
	global.iniX = position.x
	global.iniY = position.y

func pause_movement(duration: float) -> void:
	is_paused = true
	await get_tree().create_timer(duration).timeout
	is_paused = false

func check_attack_zone():
	var distance = position.distance_to(player.position)
	if distance < detection_radius and abs(player.position.y - position.y) < attack_animation_threshold_y:
		$AnimatedSprite2D.play("attack")
		await pause_movement(2)
	else:
		pass