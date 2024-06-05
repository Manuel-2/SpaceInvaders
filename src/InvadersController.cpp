#include "InvadersController.h"

#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>

#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/input.hpp>

#include <vector>

using namespace godot;

void InvadersController::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_speed"), &InvadersController::get_speed);
    ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &InvadersController::set_speed);
    ClassDB::add_property("InvadersController", PropertyInfo(Variant::FLOAT, "speed of the formation"), "set_speed", "get_speed");

    ClassDB::bind_method(D_METHOD("get_delayBetweenInvaderInFormationMove"), &InvadersController::get_delayBetweenInvaderInFormationMove);
    ClassDB::bind_method(D_METHOD("set_delayBetweenInvaderInFormationMove", "p_delayBetweenInvaderInFormationMove"), &InvadersController::set_delayBetweenInvaderInFormationMove);
    ClassDB::add_property("InvadersController", PropertyInfo(Variant::FLOAT, "delay between moving one invader and other in sequence"), "set_delayBetweenInvaderInFormationMove", "get_delayBetweenInvaderInFormationMove");
}

InvadersController::InvadersController()
{
    if (Engine::get_singleton()->is_editor_hint())
    {
        set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
    }
    speed = 50;
    delayBetweenInvaderInFormationMove = 20;
    direction = 0;

    invadersScenePaths[0] = "res://Scenes/Invader1.tscn";
    invadersScenePaths[1] = "res://Scenes/Invader2.tscn";
    invadersScenePaths[2] = "res://Scenes/Invader3.tscn";

    lastInvaderMovedInFormation[0] = 0;
    lastInvaderMovedInFormation[1] = 4;
}

void InvadersController::_ready()
{
}

void InvadersController::_process(double delta)
{
    // updates every frame
    if (Input::get_singleton()->is_action_just_pressed("StartFormation"))
    {
        buildFormation();
        if (formationMoveTimer > delayBetweenInvaderInFormationMove)
        {
            if(direction == 0){
                direction = 1;
            }
            //moveInvaderInFormation(delta);
        }
    }

    formationMoveTimer += delta;
}

void InvadersController::moveInvaderInFormation(double delta)
{
    int column = lastInvaderMovedInFormation[0];
    int row = lastInvaderMovedInFormation[1];

    Node *Invader = invadersAnimatedSpritesMatrix[column][row]->get_parent();
    Node2D *Invader2dNode = Object::cast_to<Node2D>(Invader);
    Vector2 invaderPos = Invader2dNode->get_global_position() + Vector2(speed * direction * delta, 0);
    Invader2dNode->set_global_position(invaderPos);

    lastInvaderMovedInFormation[0] += 1;

    // start form the left of the top line
    if(lastInvaderMovedInFormation[0] == 11){
        lastInvaderMovedInFormation[0] = 0;
        lastInvaderMovedInFormation[1] -= 1;
    }

    // restart
    if(lastInvaderMovedInFormation[0] == 11 && lastInvaderMovedInFormation[1] == 0){
        lastInvaderMovedInFormation[0] = 0;
        lastInvaderMovedInFormation[1] = 4;
    }
    formationMoveTimer = 0;
}

void InvadersController::buildFormation()
{
    for (int row = 1; row <= 5; row++)
    {
        for (int column = 1; column <= 12; column++)
        {
            int invaderIndex = 1;
            if (row > 1 && row <= 3)
            {
                invaderIndex = 2;
            }
            else if (row > 3)
            {
                invaderIndex = 0;
            }

            invadersScenes[invaderIndex] = ResourceLoader::get_singleton()->load(invadersScenePaths[invaderIndex]);
            Node *invaderInstance = invadersScenes[invaderIndex]->instantiate();
            Node2D *node2dInstanceReference = Object::cast_to<Node2D>(invaderInstance);
            invadersAnimatedSpritesMatrix[column][row] = node2dInstanceReference->get_node<AnimatedSprite2D>("AnimatedSprite2D");
            Vector2 invaderPos = Vector2(column * -80, row * 40);
            node2dInstanceReference->set_position(invaderPos);
            add_child(invaderInstance);
        }
    }
    // lastInvaderMovedInFormation[0] = 0;
    // lastInvaderMovedInFormation[1] = 4;
    formationMoveTimer = 0;
}

// getters and setters  --------------

void InvadersController::set_speed(const float p_speed){
    speed = p_speed;
}

float InvadersController::get_speed()const{
    return speed;
}

void InvadersController::set_delayBetweenInvaderInFormationMove( const float p_delayBetweenInvaderInFormationMove){
    delayBetweenInvaderInFormationMove = p_delayBetweenInvaderInFormationMove;
}

float InvadersController::get_delayBetweenInvaderInFormationMove() const{
    return delayBetweenInvaderInFormationMove;
}