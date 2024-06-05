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
    ClassDB::bind_method(D_METHOD("get_formationCollumns"), &InvadersController::get_formationCollumns);
    ClassDB::bind_method(D_METHOD("set_formationCollumns", "p_formationCollumns"), &InvadersController::set_formationCollumns);
    ClassDB::add_property("InvadersController", PropertyInfo(Variant::INT, "width of the formation"), "set_formationCollumns", "get_formationCollumns");

    ClassDB::bind_method(D_METHOD("get_formationRows"), &InvadersController::get_formationRows);
    ClassDB::bind_method(D_METHOD("set_formationRows", "p_formationRows"), &InvadersController::set_formationRows);
    ClassDB::add_property("InvadersController", PropertyInfo(Variant::INT, "Height of the formation"), "set_formationRows", "get_formationRows");
}

InvadersController::InvadersController()
{
    if (Engine::get_singleton()->is_editor_hint())
    {
        set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
    }

    invadersScenePaths[0] = "res://Scenes/Invader1.tscn";
    invadersScenePaths[1] = "res://Scenes/Invader2.tscn";
    invadersScenePaths[2] = "res://Scenes/Invader3.tscn";
}

void InvadersController::_ready()
{

}

void InvadersController::_process(double delta)
{
    // updates every frame
    if(Input::get_singleton()->is_action_just_pressed("StartFormation")){
        buildFormation();
    }
}

void InvadersController::buildFormation()
{
    for (int row = 1; row <= formationRows; ++row)
    {
        for (int column = 1; column <= formationCollumns; ++column)
        {
            int invaderIndex = 1;
            if(row > 1 && row <= 3){
                invaderIndex = 2;
            }else if(row > 3){
                invaderIndex = 0;
            }
            
            invadersScenes[invaderIndex] = ResourceLoader::get_singleton()->load(invadersScenePaths[invaderIndex]);
            Node *invaderInstance = invadersScenes[invaderIndex]->instantiate();
            Node2D *node2dInstanceReference = Object::cast_to<Node2D>(invaderInstance);
            invadersAnimatedSpritesMatrix[column][row] = node2dInstanceReference->get_node<AnimatedSprite2D>("AnimatedSprite2D");
            // todo: positionate using its index
            Vector2 invaderPos = Vector2(column * -80, row * 40);
            node2dInstanceReference->set_position(invaderPos);
            add_child(invaderInstance);
        }
    }
}

// getters and setters  --------------

void InvadersController::set_formationCollumns(int p_formationCollumns)
{
    formationCollumns = p_formationCollumns;
}

int InvadersController::get_formationCollumns()
{
    return formationCollumns;
}

void InvadersController::set_formationRows(int p_formationRows)
{
    formationRows = p_formationRows;
}

int InvadersController::get_formationRows()
{
    return formationRows;
}