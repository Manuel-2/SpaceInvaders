#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/animation_tree.hpp>
#include <godot_cpp/classes/animation_node_state_machine_playback.hpp>

#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/ref.hpp>

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

		Ref<PackedScene> bulletScene;

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
		void shootProyectile();

		// getters and setters
		void set_movementSpeed(const float p_movementSpeed);
		float get_movementSpeed() const;
	};
}
#endif