#include "PlayerController.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>

#include <godot_cpp/classes/input.hpp>

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

void PlayerController::_process(double delta){
	Input& InputSingleton = *Input::get_singleton();
	movementDirection = Vector2(0.0f,0.0f);
	
	if(InputSingleton.is_action_pressed("Right")){
		movementDirection.x = 1;
	}else if(InputSingleton.is_action_pressed("Left")){
		movementDirection.x = -1;
	}
}

void PlayerController::_physics_process(double delta){
	set_velocity(movementDirection * movementSpeed);
	move_and_slide();
}

void PlayerController::set_movementSpeed(const float p_movementSpeed){
	movementSpeed = p_movementSpeed;
}

float PlayerController::get_movementSpeed() const{
	return movementSpeed;
}