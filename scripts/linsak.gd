extends CharacterBody2D
var dieScene = load("res://floors/end_game_die.tscn")
var floor_1 = load("res://floors/floor_1.tscn")
var enemyInAttackRange = false
var enemyAttackCoolDown = true
@export var maxHealth = 5
@onready var health = maxHealth
@onready var heartsContainer = $heartsContainer

var attack = false

var current_dir = "none"
var current_act = "afk"
var speed = 400.0

func _ready():
	$AnimatedSprite2D.play("afk")
	heartsContainer.setMaxHearts(maxHealth)
	heartsContainer.updateHearts(global.playerCurrentHealth)


func _physics_process(delta):
	playerMovement(delta)
	enemyAttack()

	if health <= 0:
		health = 0
		get_tree().change_scene_to_packed(dieScene)
		var current_act = "die"
		linsak_anim(0)
		

func playerMovement(delta):
	if Input.is_action_pressed("hurry_move"):
		speed = 800.0
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
			

func player():
	pass

func _on_hitbox_body_exited(body:Node2D):
	if body.has_method("enemy"):
		enemyInAttackRange = false 

func _on_hitbox_body_entered(body:Node2D):
	if body.has_method("enemy"):
		enemyInAttackRange = true

func enemyAttack():
	if enemyInAttackRange and enemyAttackCoolDown == true:
		health = health - 1
		global.playerCurrentHealth = health
		enemyAttackCoolDown = false
		$attackCooldown.start()
		heartsContainer.updateHearts(global.playerCurrentHealth)

func _on_attack_cooldown_timeout():
	enemyAttackCoolDown = true

func _on_attack_enemy_cooldown_timeout():
	$attackEnemyCooldown.stop()
	global.playerCurrentAttack = false
	attack = false
