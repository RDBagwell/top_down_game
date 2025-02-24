#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeigt) : windowWidth(winWidth),
                                                   windowHeight(winHeigt)
{
    width = texture.width / maxFrames;
    height = texture.height;
};

void Character::tick(float deltaTime)
{
    if (!getAlive())
        return;
    // Move Character
    if (IsKeyDown(KEY_A))
        velocity.x -= 1.f;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.f;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.f;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.f;

    BaseCharacter::tick(deltaTime);

    Vector2 origin{};
    Vector2 offset{};
    float rotation{};

    if (rightLeft > 0.f)
    {
        origin = {0.f, weapon.height * scale};
        offset = {35.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale};

        IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? rotation = 35.f : 0.f;
    }
    else
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {25.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x - weapon.width * scale,
            getScreenPos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale};

        IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? rotation = -35.f : 0.f;
    }

    // darw the sword
    Rectangle source{
        0.f,
        0.f,
        static_cast<float>(weapon.width) * rightLeft,
        static_cast<float>(weapon.height)};

    Rectangle dest{
        getScreenPos().x + offset.x,
        getScreenPos().y + offset.y,
        scale * weapon.width,
        scale * weapon.height};

    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

    // DrawRectangleLines(weaponCollisionRec.x,
    //                    weaponCollisionRec.y,
    //                    weaponCollisionRec.width,
    //                    weaponCollisionRec.height,
    //                    RED);
}

Vector2 Character::getScreenPos()
{
    return Vector2{
        static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * static_cast<float>(width)),
        static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * static_cast<float>(height))};
}

void Character::takeDamage(float damage)
{
    health -= damage;
    if (health <= 0.f)
    {
        setAlive(false);
    }
}