#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <godot_cpp/classes/character_body2d.hpp>

using namespace godot;

class PlayerController : CharacterBody2D
{
private:
	float movementSpeed;

protected:
	static void _bind_methods();

public:
	PlayerController();
	//~PlayerController();
	
	void _physics_process(double delta);

	void set_movementSpeed(float p_movementSpeed);
	float get_movementSpeed();

};

#endif