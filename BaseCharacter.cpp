#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{
}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::GetCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        height * scale};
}

void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;
    
    // Update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }

    Rectangle source{
        frame * static_cast<float>(width),
        0.f,
        rightLeft * static_cast<float>(width),
        static_cast<float>(height)};

    Rectangle dest{
        getScreenPos().x,
        getScreenPos().y,
        scale * static_cast<float>(texture.width) / 6.f,
        scale * static_cast<float>(height)};

    if (Vector2Length(velocity) != 0.f)
    {
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};

    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}