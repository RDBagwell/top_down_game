#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    width = texture.width / maxFrames;
    height = texture.height;
    speed = 3.5f;
}

void Enemy::tick(float deltaTime)
{
    if (!getAlive())
        return;
    // Get toTarget
    velocity = Vector2Subtract(taget->getScreenPos(), getScreenPos());
    if (Vector2Length(velocity) < radius)
        velocity = {};
    BaseCharacter::tick(deltaTime);
    if (CheckCollisionRecs(taget->GetCollisionRec(), GetCollisionRec()))
    {
        taget->takeDamage(damagePreSec * deltaTime);
    }
}

void Enemy::setTarget(Character *character)
{
    taget = character;
};

Vector2 Enemy::getScreenPos()
{
    return Vector2{
        Vector2Subtract(worldPos, taget->getWorldPos())};
}