extends CharacterBody2D

var speed = 15
var enemyName = "Flame"

# Called when the node enters the scene tree for the first time.
func _ready():
	$AnimatedSprite2D.play("shoot")
	position.x = global.iniX
	position.y = global.iniY + 300


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	position.y += speed
	if position.y > 9300 or position.y < 1600:
		destroy()

func _on_area_2d_body_entered(body:Node2D):
	if body.has_method("player"):
		destroy()
	elif body.has_method("enemy"):
		destroy()

func enemyShoot():
	pass

func destroy():
	self.queue_free()
	global.currentPoints += 10