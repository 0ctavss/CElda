extends CharacterBody2D
var dieScene = load("res://floors/end_game_die.tscn")
var floor_1 = load("res://floors/floor_1.tscn")
var floor_2 = load("res://floors/floor_2.tscn")
var floor_3 = load("res://floors/floor_3.tscn")
var floor_4 = load("res://floors/floor_4.tscn")
var boss_floor = load("res://floors/boss_floor.tscn")
var enemyInAttackRange = false
var enemyAttackCoolDown = true
@export var maxHealth = 5
@onready var health = global.playerCurrentHealth
@onready var heartsContainer = $heartsContainer
@onready var pointsLabel: Label = $points/currentPoints
@onready var chestsLabel: Label = $chest/currentChests

var attack = false
var currentEnemy = "none"
var current_dir = "none"
var current_act = "afk"
var difficulty = 1
var speed = 400.0

func _ready():
	$AnimatedSprite2D.play("afk")
	heartsContainer.setMaxHearts(maxHealth)
	heartsContainer.updateHearts(health)

func _physics_process(delta):
	playerMovement(delta)
	enemyAttack()
	pointsLabel.text = str(global.currentPoints)
	chestsLabel.text = str(global.currentChestOpen)
	if global.currentFloor == 2:
		$light.set_enabled(true)
	else:
		$light.set_enabled(false)

	if health <= 0:
		global.currentPoints = global.pointsFloor
		global.currentChestOpen = global.chestFloorOpen
		if difficulty == 0:
			global.playerCurrentHealth = maxHealth
		else:
			global.playerCurrentHealth = global.healthFloor
		global.changeFloor = true
		global.safeZone = false
	if global.changeFloor:
		global.changeFloor = false
		toFloor(global.currentFloor)

func playerMovement(delta):
	if Input.is_action_pressed("hurry_move"):
		speed = 1000.0
	if Input.is_action_pressed("ui_up") or Input.is_action_pressed("up_move"):
		current_dir = "up"
		linsak_anim(1)
		velocity.y = -speed
		if Input.is_action_pressed("ui_right") or Input.is_action_pressed("R_move"):
			velocity.x = speed
		elif Input.is_action_pressed("ui_left") or Input.is_action_pressed("L_move"):
			velocity.x = -speed
		else:
			velocity.x = 0
	elif Input.is_action_pressed("ui_down") or Input.is_action_pressed("down_move"):
		current_dir = "down"
		linsak_anim(1)
		velocity.y = speed
		if Input.is_action_pressed("ui_right") or Input.is_action_pressed("R_move"):
			velocity.x = speed
		elif Input.is_action_pressed("ui_left") or Input.is_action_pressed("L_move"):
			velocity.x = -speed
		else:
			velocity.x = 0
	elif Input.is_action_pressed("ui_right") or Input.is_action_pressed("R_move"):
		current_dir = "rigth"
		linsak_anim(1)
		velocity.x = speed
		velocity.y = 0
	elif Input.is_action_pressed("ui_left") or Input.is_action_pressed("L_move"):
		current_dir = "left"
		linsak_anim(1)
		velocity.x = -speed
		velocity.y = 0
	elif Input.is_action_pressed("attack_move"):
		current_act = "attack"
		linsak_anim(0)
	elif Input.is_action_pressed("cover_move"):
		current_act = "cover"
		linsak_anim(0)
	elif Input.is_action_pressed("ui_select"):
		if global.currentChestOpen == 12:
			current_act = "RUPIAS"
			linsak_anim(0)
		else:
			print("Rupias insuficientes")
	else:
		current_act = "afk"
		linsak_anim(0)
		velocity.x = 0
		velocity.y = 0
		speed = 400.0

	move_and_slide()

func linsak_anim(movement):
	var dir = current_dir
	var anim = $AnimatedSprite2D

	if movement == 1:
		current_act = "move"
		if dir == "rigth":
			anim.flip_h = false
			anim.play("walk_side")
		if dir == "left":
			anim.flip_h = true
			anim.play("walk_side")
		if dir == "up":
			anim.flip_h = false
			anim.play("walk_back")
		if dir == "down":
			anim.flip_h = false
			anim.play("walk_front")
	elif movement == 0:
		if current_act == "afk":
			anim.play("afk")
		elif current_act == "RUPIAS":
			anim.play("hold")
		elif current_act == "attack":
			global.playerCurrentAttack = true
			attack = true
			$attackEnemyCooldown.start()
			if dir == "rigth": 
				anim.flip_h = false
				anim.play("attack_side")
			if dir == "left": 
				anim.flip_h = true
				anim.play("attack_side")
			if dir == "up": 
				anim.flip_h = false
				anim.play("attack_back")
			if dir == "down": 
				anim.flip_h = false
				anim.play("attack_front")
		elif current_act == "cover":
			if dir == "rigth": 
				anim.flip_h = false
				anim.play("cover_side")
			if dir == "left": 
				anim.flip_h = true
				anim.play("cover_side")
			if dir == "up": 
				anim.flip_h = false
				anim.play("cover_back")
			if dir == "down": 
				anim.flip_h = false
				anim.play("cover_front")
			
		elif current_act == "die":
			anim.play("death")
			await get_tree().create_timer(1.0).timeout
			

func player():
	pass

func _on_hitbox_body_exited(body:Node2D):
	if body.has_method("enemy"):
		currentEnemy = "none"
		enemyInAttackRange = false

func _on_hitbox_body_entered(body:Node2D):
	if body.has_method("enemy") or body.has_method("enemyShoot"):
		currentEnemy = body.enemyName
		enemyInAttackRange = true

func enemyAttack():
	if enemyInAttackRange and enemyAttackCoolDown == true:
		if currentEnemy == "Slime":
			health -= 1
		if currentEnemy == "Rat":
			health -= 1
		if currentEnemy == "Flame":
			currentEnemy = "none" #si quito esto hace daño de quemado
			enemyInAttackRange = false #si quito esto hace daño de quemado
			if current_act == "cover":
				pass
			else:
				health -= 1
		if currentEnemy == "Espectre":
			health = 0
		if currentEnemy == "Boss":
			if health == 1:
				health -= 1
			else:
				health = 1
			
		global.playerCurrentHealth = health
		enemyAttackCoolDown = false
		$attackCooldown.start()
	health = global.playerCurrentHealth
	heartsContainer.updateHearts(health)

func _on_attack_cooldown_timeout():
	enemyAttackCoolDown = true

func _on_attack_enemy_cooldown_timeout():
	$attackEnemyCooldown.stop()
	global.playerCurrentAttack = false
	attack = false

func toFloor(floor: int):
	if floor == 1:
		get_tree().change_scene_to_packed(floor_1)
	if floor == 2:
		get_tree().change_scene_to_packed(floor_2)
	if floor == 3:
		get_tree().change_scene_to_packed(floor_3)
	if floor == 4:
		get_tree().change_scene_to_packed(floor_4)
	if floor == 5:
		get_tree().change_scene_to_packed(boss_floor)