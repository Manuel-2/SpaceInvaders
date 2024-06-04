#include "Bullet.h"

#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>

#include "PlayerController.h"

using namespace godot;

void Bullet::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_speed"), &Bullet::get_speed);
    ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &Bullet::set_speed);
    ClassDB::add_property("Bullet", PropertyInfo(Variant::FLOAT, "bullet speed"), "set_speed", "get_speed");

    ClassDB::bind_method(D_METHOD("_on_body_entered"), &Bullet::_on_body_entered);
}

Bullet::Bullet() {
    if(Engine::get_singleton()->is_editor_hint()){
        set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
    }

    connect("body_entered",Callable(this,"_on_body_entered"));

    speed = 300;
    yDirection = 1;
}

void Bullet::_on_body_entered(Variant body){
    Node2D *colidedNode = cast_to<Node2D>(body);
    if(colidedNode->is_class("PlayerController")){
        PlayerController *player = cast_to<PlayerController>(colidedNode);
        player->takeDamage();
    }else{
        // todo:
        // Invader invader = cast_to<Invader>(colidedNode);
        // invader->takeDamage();
    }

    // todo: call a particle efect
    queue_free();
}

void Bullet::_process(double delta){
    // updates every frame
    float y = get_position().y + speed * yDirection * delta;
    set_position(Vector2(0,y));
}

// custom --------------------------

// // 1 goes up, -1 goes down
void setDirection(float pYDirection){
    pYDirection = pYDirection;
}


// getters and setters  --------------

void Bullet::set_speed(float p_speed){
    speed = p_speed;
}

float Bullet::get_speed(){
    return speed;
}