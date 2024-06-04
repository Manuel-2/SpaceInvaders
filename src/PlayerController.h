#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/animation_tree.hpp>
#include <godot_cpp/classes/animation_node_state_machine_playback.hpp>

namespace godot
{

	class PlayerController : public CharacterBody2D
	{
		GDCLASS(PlayerController, CharacterBody2D)

	private:
		float movementSpeed;
		Vector2 movementDirection;
		AnimationTree *animTree;
		AnimationNodeStateMachinePlayback *playback;

	protected:
		static void _bind_methods();

	public:
		PlayerController();
		//~PlayerController();
		void _ready();
		void _process(double delta);
		void _physics_process(double delta);

		// custom
		void takeDamage();

		// getters and setters
		void set_movementSpeed(const float p_movementSpeed);
		float get_movementSpeed() const;
	};
}
#endif