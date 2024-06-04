#ifndef BULLET_H
#define BULLET_H

#include <godot_cpp/classes/area2d.hpp>

#include <godot_cpp/classes/physics_body2d.hpp>

using namespace godot;

class Bullet : public Area2D
{
GDCLASS(Bullet,Area2D)

private:
    // 1 is down -1 is up
    float speed;
    float yDirection;

protected:
    static void _bind_methods();

public:
    Bullet();
    //~Bullet();

    void _process(double delta);

    void _on_body_entered(Variant body);
    //void _on_body_entered(Variant::);

    void set_speed(float p_speed);
    float get_speed();
};

#endif