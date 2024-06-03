#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <godot_cpp/classes/character_body2d.hpp>

namespace godot
{

	class PlayerController : public CharacterBody2D
	{
		GDCLASS(PlayerController, CharacterBody2D)

	private:
		float movementSpeed;
		Vector2 movementDirection;

	protected:
		static void _bind_methods();

	public:
		PlayerController();
		//~PlayerController();

		void _process(double delta);
		void _physics_process(double delta);

		void set_movementSpeed(const float p_movementSpeed);
		float get_movementSpeed() const;
	};
}
#endif