#include <math.h>
#include <raylib.h>
#include <stdio.h>

#include "Player.h"
// /
int map[20][20] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
const int screenWidth = 1200;
const int screenHeight = 800;
const int TILE_SIZE = 32;
const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 20;
const int MINI_TILE_SIZE = 10;
const int padx = (screenWidth - TILE_SIZE * MAP_WIDTH) / 2,
          pady = (screenHeight - TILE_SIZE * MAP_HEIGHT) / 2;
const int map_padx = 950, map_pady = 10;

Player RotateM(Player player, float rotSpeed, int d) {
    float OldDirX = player.dir.x;
    player.dir.x =
        player.dir.x * cos(rotSpeed) - d * player.dir.y * sin(rotSpeed);
    player.dir.y = player.dir.y * cos(rotSpeed) + d * OldDirX * sin(rotSpeed);

    float OldPlaneX = player.plane.x;
    player.plane.x =
        player.plane.x * cos(rotSpeed) - d * player.plane.y * sin(rotSpeed);
    player.plane.y =
        player.plane.y * cos(rotSpeed) + d * OldPlaneX * sin(rotSpeed);
    return player;
}

int CheckTargetPos(float posX, float posY) {
    int x = floor(posX / 32), y = floor(posY / 32);
    // printf("%f %f # %d %d %d\n",posX,posY,x,y,map[y][x]);
    if (map[y][x] > 0) return 0;
    return 1;
}

void ModifyMap(int c, int posX, int posY) {
    int x = (posX - padx) / TILE_SIZE;
    int y = (posY - pady) / TILE_SIZE;
    printf("%d %d %d\n", x, y, c);
    if (x > 0 && x < MAP_WIDTH - 1 && y > 0 && y < MAP_HEIGHT - 1)
        map[y][x] = c;
}

void ResetMap() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (x > 0 && x < MAP_WIDTH - 1 && y > 0 && y < MAP_HEIGHT - 1)
                map[y][x] = 0;
            else
                map[y][x] = 1;
        }
    }
    return;
}

void SaveMap() {
    FILE* mpf = fopen("src/map.txt", "w");
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            fprintf(mpf, "%d ", map[y][x]);
        }
        fprintf(mpf, "\n");
    }
    fclose(mpf);
    return;
}

void LoadMap() {
    FILE* mpf = fopen("src/map.txt", "r");
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            fscanf(mpf, "%d", &map[y][x]);
        }
    }
    fclose(mpf);
    return;
}

int main(void) {
    int game_mode = 0;
    Player player;
    player.pos.x = 1 * TILE_SIZE;
    player.pos.y = 1 * TILE_SIZE;
    player.map_pos.x = 1 * MINI_TILE_SIZE;
    player.map_pos.y = 1 * MINI_TILE_SIZE;
    player.dir.x = 1.0;
    player.dir.y = 0.0;
    player.plane.x = 0.0;
    player.plane.y = 0.66;
    InitWindow(screenWidth, screenHeight, "Raycaster");
    SetTargetFPS(60);
    LoadMap();
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // set game mode
        if (IsKeyPressed(KEY_M)) {
            game_mode = game_mode == 1 ? 0 : 1;
        }
        if (game_mode == 0) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                ModifyMap(1, GetMouseX(), GetMouseY());
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                ModifyMap(0, GetMouseX(), GetMouseY());
            }
            if (IsKeyPressed(KEY_F1)) {
                ResetMap();
            }
            if (IsKeyPressed(KEY_F5)) {
                SaveMap();
            }
            if (IsKeyPressed(KEY_F9)) {
                LoadMap();
            }
        }
        float moveSpeed = 100.0 * dt;
        float rotSpeed = 5.0 * dt;
        if (IsKeyDown(KEY_W)) {
            if (CheckTargetPos(player.pos.x + moveSpeed * player.dir.x,
                               player.pos.y + moveSpeed * player.dir.y)) {
                player.pos.y += moveSpeed * player.dir.y;
                player.pos.x += moveSpeed * player.dir.x;
                player.map_pos.y += moveSpeed * player.dir.y / 3.2;
                player.map_pos.x += moveSpeed * player.dir.x / 3.2;
            }
        }
        if (IsKeyDown(KEY_S)) {
            if (CheckTargetPos(player.pos.x - moveSpeed * player.dir.x,
                               player.pos.y - moveSpeed * player.dir.y)) {
                player.pos.y -= moveSpeed * player.dir.y;
                player.pos.x -= moveSpeed * player.dir.x;
                player.map_pos.y -= moveSpeed * player.dir.y / 3.2;
                player.map_pos.x -= moveSpeed * player.dir.x / 3.2;
            }
        }
        if (IsKeyDown(KEY_D)) {
            if (CheckTargetPos(player.pos.x + moveSpeed * player.dir.y,
                               player.pos.y + moveSpeed * player.dir.x)) {
                player.pos.x += moveSpeed * player.dir.y;
                player.pos.y += moveSpeed * player.dir.x;
                player.map_pos.x += moveSpeed * player.dir.y / 3.2;
                player.map_pos.y += moveSpeed * player.dir.x / 3.2;
            }
        }
        if (IsKeyDown(KEY_A)) {
            if (CheckTargetPos(player.pos.x - moveSpeed * player.dir.y,
                               player.pos.y - moveSpeed * player.dir.x)) {
                player.pos.x -= moveSpeed * player.dir.y;
                player.pos.y -= moveSpeed * player.dir.x;
                player.map_pos.x -= moveSpeed * player.dir.y / 3.2;
                player.map_pos.y -= moveSpeed * player.dir.x / 3.2;
            }
        }
        if (IsKeyDown(KEY_RIGHT)) {
            player = RotateM(player, rotSpeed, 1);
        }
        if (IsKeyDown(KEY_LEFT)) {
            player = RotateM(player, rotSpeed, -1);
        }
        BeginDrawing();
        ClearBackground(BLACK);
        if (game_mode == 0) {
            DrawText("Save map(F5)", 200, 30, 20, BLUE);
            DrawText("Load map(F9)", 550, 30, 20, WHITE);
            DrawText("Reset map(F1)", 900, 30, 20, WHITE);
            for (int y = 0; y < MAP_HEIGHT; y++) {
                for (int x = 0; x < MAP_WIDTH; x++) {
                    int screenX = padx + x * TILE_SIZE;
                    int screenY = pady + y * TILE_SIZE;
                    if (map[y][x] > 0) {
                        DrawRectangle(screenX, screenY, TILE_SIZE, TILE_SIZE,
                                      WHITE);
                    } else {
                        DrawRectangle(screenX, screenY, TILE_SIZE, TILE_SIZE,
                                      BLACK);
                    }
                    DrawRectangleLines(screenX, screenY, TILE_SIZE, TILE_SIZE,
                                       DARKGRAY);
                }
            }
            DrawCircle(padx + player.pos.x, pady + player.pos.y, 20, RED);
            DrawLine(padx + player.pos.x, pady + player.pos.y,
                     padx + player.pos.x + 40 * player.dir.x,
                     pady + player.pos.y + 40 * player.dir.y, BLUE);

        } else if (game_mode == 1) {
            printf("%d\n", game_mode);
            for (int x = 0; x < screenWidth; x++) {
                double cameraX = 2 * (x / (double)screenWidth) - 1;
                double rayDirX = player.dir.x + player.plane.x * cameraX;
                double rayDirY = player.dir.y + player.plane.y * cameraX;

                int mapX = floor(player.pos.x / TILE_SIZE),
                    mapY = floor(player.pos.y / TILE_SIZE);
                double posX = player.pos.x / TILE_SIZE,
                       posY = player.pos.y / TILE_SIZE;

                double sideDistX, sideDistY;

                double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
                double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
                double perpWallDist;

                int stepX, stepY;

                // DDA
                int hit = 0;
                int side;

                if (rayDirX < 0) {
                    stepX = -1;
                    sideDistX = (posX - mapX) * deltaDistX;
                } else {
                    stepX = 1;
                    sideDistX = (mapX + 1.0 - posX) * deltaDistX;
                }
                if (rayDirY < 0) {
                    stepY = -1;
                    sideDistY = (posY - mapY) * deltaDistY;
                } else {
                    stepY = 1;
                    sideDistY = (mapY + 1.0 - posY) * deltaDistY;
                }

                while (!hit) {
                    if (sideDistX < sideDistY) {
                        sideDistX += deltaDistX;
                        mapX += stepX;
                        side = 0;
                    } else {
                        sideDistY += deltaDistY;
                        mapY += stepY;
                        side = 1;
                    }
                    if (map[mapY][mapX]) hit = 1;
                }

                if (side == 0)
                    perpWallDist = (sideDistX - deltaDistX);
                else
                    perpWallDist = (sideDistY - deltaDistY);

                int lineHeight = (int)(screenHeight / perpWallDist);

                int drawStart = screenHeight / 2 - lineHeight / 2;
                if (drawStart < 0) drawStart = 0;
                int drawEnd = screenHeight / 2 + lineHeight / 2;
                if (drawEnd > screenHeight) drawEnd = screenHeight - 1;
                Color color = GRAY;
                if (side == 1) color = DARKGRAY;
                DrawLine(x, 0, x, drawStart, SKYBLUE);
                DrawLine(x, drawStart, x, drawEnd, color);
                DrawLine(x, drawEnd, x, screenHeight, BLACK);
            }
            for (int y = 0; y < MAP_HEIGHT; y++) {
                for (int x = 0; x < MAP_WIDTH; x++) {
                    if (map[y][x]) {
                        DrawRectangle(map_padx + x * MINI_TILE_SIZE,
                                      map_pady + y * MINI_TILE_SIZE,
                                      MINI_TILE_SIZE, MINI_TILE_SIZE, BLACK);
                    } else {
                        DrawRectangle(map_padx + x * MINI_TILE_SIZE,
                                      map_pady + y * MINI_TILE_SIZE,
                                      MINI_TILE_SIZE, MINI_TILE_SIZE, WHITE);
                    }
                    DrawRectangleLines(map_padx + x * MINI_TILE_SIZE,
                                       map_pady + y * MINI_TILE_SIZE,
                                       MINI_TILE_SIZE, MINI_TILE_SIZE,
                                       DARKGRAY);
                }
            }
            // printf("%f , %f\n",player.pos.x , player.pos.y);

            DrawCircle(map_padx + player.map_pos.x, map_pady + player.map_pos.y,
                       4, RED);
            DrawLine(map_padx + player.map_pos.x, map_pady + player.map_pos.y,
                     map_padx + player.map_pos.x + 10 * player.dir.x,
                     map_pady + player.map_pos.y + 10 * player.dir.y, RED);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}