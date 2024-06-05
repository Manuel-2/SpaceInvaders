#ifndef INVADERSCONTROLLER_H
#define INVADERSCONTROLLER_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/ray_cast2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

using namespace godot;

class InvadersController : public Node2D
{
	GDCLASS(InvadersController, Node2D)

private:
    float direction;
    float speed;
    float formationMoveTimer;
    float delayBetweenInvaderInFormationMove;
    // index 0 is X, index 1 is y
    int lastInvaderMovedInFormation[2];

    //index  0 is left, 1 is right
    RayCast2D *leftRayCast;
    RayCast2D *rightRayCast;

    // formation
    String invadersScenePaths[3];
	Ref<PackedScene> invadersScenes[3];
    AnimatedSprite2D  *invadersAnimatedSpritesMatrix[12][5];

    //matrix thing

protected:
    static void _bind_methods();

public:
    InvadersController();
    
    void _process(double delta);
    void _ready();

    void buildFormation();
    void moveInvaderInFormation(double delta);

    void set_speed(const float p_speed);
    float get_speed()const;

    void set_delayBetweenInvaderInFormationMove( const float p_delayBetweenInvaderInFormationMove);
    float get_delayBetweenInvaderInFormationMove() const;
};

#endif