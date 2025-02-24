#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    // Init window
    const int windowWidth{384};
    const int windowHeight{384};
    InitWindow(windowWidth, windowHeight, "Top Down");

    // Load Map
    Texture2D worldMap = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.f};

    // init character
    Character knight(windowWidth, windowHeight);

    //  init props
    Prop props[2]{
        Prop{LoadTexture("nature_tileset/Rock.png"), Vector2{600.f, 300.f}},
        Prop{LoadTexture("nature_tileset/Log.png"), Vector2{400.f, 500.f}},
    };

    Enemy goblin{
        Vector2{800.f, 300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};

    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_runspritesheet.png")};

    Enemy *enemies[]{
        &goblin,
        &slime};

    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    // Set FPS
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // delta time (time since last frame)
        const float dt{GetFrameTime()};
        BeginDrawing();
        ClearBackground(WHITE);

        // Gmae Logic
        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);
        // Draw World Map
        DrawTextureEx(worldMap, mapPos, 0.f, mapScale, WHITE);
        knight.tick(dt);

        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        if (!knight.getAlive())
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string knightHealth = "Health: ";
            knightHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightHealth.c_str(), 55.f, 45.f, 40, WHITE);
        }

        // Map bounds
        if (
            knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > (worldMap.width * mapScale) ||
            knight.getWorldPos().y + windowHeight > (worldMap.height * mapScale))
        {
            knight.undoMovement();
        }

        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.GetCollisionRec(knight.getWorldPos()), knight.GetCollisionRec()))
                knight.undoMovement();
        }

        goblin.tick(dt);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->GetCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }

        EndDrawing();
    }
    UnloadTexture(worldMap);
    CloseWindow();
}