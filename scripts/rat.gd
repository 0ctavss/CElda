extends CharacterBody2D

var speed = 700
var enemyAlive = true
var playerInAttackZone = false
var enemyName = "Rat"
var enemyAttack = true

@export var move_interval: float = 3.0  # Intervalo de tiempo en segundos para cambiar de posición

var target_position: Vector2  # La posición objetivo actual
var rng: RandomNumberGenerator = RandomNumberGenerator.new()

func _ready():
	var timer = Timer.new()
	timer.wait_time = move_interval
	timer.one_shot = false
	timer.connect("timeout", Callable(self, "_on_Timer_timeout"))
	add_child(timer)
	timer.start()
	choose_new_target_position()

func _physics_process(delta):
	dealDamage()
	move_towards_target(delta)
	if enemyAlive == false:
		global.currentPoints += 10
		self.queue_free()


func _on_area_2d_body_entered(body:Node2D):
	if body.has_method("player"):
		playerInAttackZone = true


func _on_area_2d_body_exited(body:Node2D):
	if body.has_method("player"):
		playerInAttackZone = false

func enemy():
	pass

func dealDamage():
	if playerInAttackZone and global.playerCurrentAttack == true:
		enemyAlive = false

func _on_Timer_timeout():
	choose_new_target_position()

func choose_new_target_position():
	var random_x = rng.randf_range(-2750, 4150)
	var random_y = rng.randf_range(2000, 8900)
	target_position = Vector2(random_x, random_y)
	print("Nueva posición objetivo:", target_position)

func move_towards_target(delta: float):
	var direction = (target_position - position).normalized()
	if (target_position.x - position.x) < 0:
		$AnimatedSprite2D.play("walk_side")
		$AnimatedSprite2D.flip_h = true
	else:
		$AnimatedSprite2D.play("walk_side")
		$AnimatedSprite2D.flip_h = false
	position += direction * speed * delta

