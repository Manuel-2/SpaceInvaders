#include "PlayerController.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>

#include <godot_cpp/classes/input.hpp>

#include <godot_cpp/classes/animation_tree.hpp>
#include <godot_cpp/classes/animation_node_state_machine_playback.hpp>

#include "Bullet.h"
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

using namespace godot;

void PlayerController::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_movementSpeed"), &PlayerController::get_movementSpeed);
	ClassDB::bind_method(D_METHOD("set_movementSpeed", "p_movementSpeed"), &PlayerController::set_movementSpeed);
	ClassDB::add_property("PlayerController", PropertyInfo(Variant::FLOAT, "movement speed"), "set_movementSpeed", "get_movementSpeed");
}

PlayerController::PlayerController() {
	if(Engine::get_singleton()->is_editor_hint()){
		set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
	}
	movementSpeed = 500;
}

void PlayerController::_ready(){
	animTree = get_node<AnimationTree>("AnimationTree");
	playback = cast_to<AnimationNodeStateMachinePlayback>(animTree->get("parameters/playback"));
	playback->travel("Idle");

	bulletScene = ResourceLoader::get_singleton()->load("res://Scenes/Bullet.tscn");
}

void PlayerController::_process(double delta){
	Input& InputSingleton = *Input::get_singleton();
	movementDirection = Vector2(0.0f,0.0f);
	
	if(InputSingleton.is_action_pressed("Right")){
		movementDirection.x = 1;
		playback->travel("Moving");
	}else if(InputSingleton.is_action_pressed("Left")){
		movementDirection.x = -1;
		playback->travel("Moving");
	}else if(InputSingleton.is_action_just_released("Right") || InputSingleton.is_action_just_released("Left")){
		playback->travel("Idle");
	}

	if(InputSingleton.is_action_just_pressed("Fire")){
		shootProyectile();
	}
}

void PlayerController::_physics_process(double delta){
	set_velocity(movementDirection * movementSpeed);
	move_and_slide();
}

// custom
void PlayerController::takeDamage(){
	queue_free();
}

void PlayerController::shootProyectile(){
	Node *instance = bulletScene->instantiate();
	Node *playerParent = get_parent();

	Vector2 newBulletPosition = Vector2(0.0f,0.0f);
	// "y" values is negative goin up
	newBulletPosition.y = get_position().y - 30;
	newBulletPosition.x = get_position().x;
	Bullet *bullet2dNodeInstance = Object::cast_to<Bullet>(instance);
	bullet2dNodeInstance->set_global_position(newBulletPosition);
	bullet2dNodeInstance->setDirection(-1);
	playerParent->add_child(instance);
}

void PlayerController::set_movementSpeed(const float p_movementSpeed){
	movementSpeed = p_movementSpeed;
}

float PlayerController::get_movementSpeed() const{
	return movementSpeed;
}