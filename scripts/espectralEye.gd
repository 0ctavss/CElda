extends CharacterBody2D

var playerChase = false
var enemyAlive = true
var playerInAttackZone = false
var enemyName = "EspectralEye"

func _ready():
	$AnimatedSprite2D.play("stand")
	global.tpX = position.x
	global.tpY = position.y
	
func _physics_process(delta):

	dealDamage()
	if enemyAlive:
		pass
	else:
		global.currentPoints += 3
		$AnimatedSprite2D.play("stand")
		await get_tree().create_timer(0.25).timeout
		$AnimatedSprite2D.play("alert")
		await get_tree().create_timer(0.25).timeout
		$AnimatedSprite2D.play("stand")
		await get_tree().create_timer(0.25).timeout
		$AnimatedSprite2D.play("alert")
		await get_tree().create_timer(0.25).timeout
		self.queue_free()

func _on_hitbox_body_entered(body:Node2D):
	if body.has_method("player"):
		playerInAttackZone = true


func _on_hitbox_body_exited(body:Node2D):
	if body.has_method("player"):
		playerInAttackZone = false


func _on_detection_area_body_entered(body:Node2D):
	$AnimatedSprite2D.play("alert")
	if body.has_method("player"):
		global.alertEnemy = true
		playerChase = true
		await get_tree().create_timer(1.0).timeout
		global.alertEnemy = false


func _on_detection_area_body_exited(body:Node2D):
	$AnimatedSprite2D.play("stand")
	if body.has_method("player"):
		global.alertEnemy = false
		playerChase = false

func dealDamage():
	if global.safeZone:
		playerChase = false
	if global.safeZone == false:
		playerChase = true
	if playerInAttackZone and global.playerCurrentAttack == true:
		enemyAlive = false