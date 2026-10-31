#include "raylib.h"
#include "iostream"
#include <cmath>
#include <hpp/movementAnt.hpp>

const short int ROTATION_SPEED = 10;
const short int CAMERA_FOLLOW_THRESH = 100;
                                                    //DECLARATION OF VARIABLES
//Windows 
int worldWidth = 5000;
int worldHeight = 5000;                                                
short int widthWindow = 400;
short int heightWindow = 600;

//Ant variables
float antWidth = 20;
float antHeight = 50;

float antPositionX = widthWindow/2 - 10;
float antPositionY = heightWindow/2-25;

short int antDirection = -1;
float antSpeed = 0;
float maxSpeedAnt = 10.0f;
float antRotation = -90;
float antSpeedUp = 10;
float antSlowDown = 15;

int main()
{
    InitWindow(widthWindow, heightWindow, "Ant World");
    SetTargetFPS(60);
    
    Image backgroundImage = LoadImage("Resource/PNG/Background_Tiles/Soil_Tile.png");
    ImageRotateCW(&backgroundImage);
    Texture2D backgroundTexture = LoadTextureFromImage(backgroundImage);

    Image antImage = LoadImage("Resource/Hormiga.png");
    ImageRotateCW(&antImage);
    Texture2D antTexture = LoadTextureFromImage(antImage);
    Rectangle antTextureRect = {
        .x = 0,
        .y = 0,
        .width = static_cast<float>(antTexture.width),
        .height = static_cast<float>(antTexture.height),
    };

     Camera2D camera = {
            .offset = (Vector2){0, 0},
            .target = (Vector2){0, 0},
            .rotation = 0,
            .zoom = 1.0,
        };


    while (!WindowShouldClose()){
        float deltaTime = GetFrameTime();
        BeginDrawing();
        ClearBackground(GREEN);


        BeginMode2D(camera);

        int titleCountCol = ceil(worldWidth/backgroundTexture.width);
        int titleCountRow = ceil(worldHeight/backgroundTexture.height);

        for (int x = 0; x < titleCountCol; x++)
        {
            for (int y = 0; y < titleCountRow; y++)
            {
                DrawTexture(backgroundTexture, x * backgroundTexture.width, y * backgroundTexture.height, WHITE);
                
            }
            
        }

        antSpeed = moveAnt(antSpeed, antSpeedUp,  deltaTime, antSlowDown, antDirection, maxSpeedAnt);
        antRotation = rotationAnt(antRotation, ROTATION_SPEED, deltaTime, antSpeed);

        float radians = PI * antRotation/180;
        float x_move = antSpeed * cosf(radians);
        float y_move = antSpeed * sinf(radians);
        antPositionX -= x_move;
        antPositionY -= y_move;

//ssssssssssssssssss
        if(antPositionX + camera.offset.x < CAMERA_FOLLOW_THRESH){
            camera.offset.x = -antPositionX + CAMERA_FOLLOW_THRESH;
        }
        if(antPositionX + camera.offset.x > (widthWindow - CAMERA_FOLLOW_THRESH)){
            camera.offset.x = -antPositionX + (widthWindow - CAMERA_FOLLOW_THRESH);
        }
//ssssssssssssssssss
        if(antPositionY + camera.offset.y < CAMERA_FOLLOW_THRESH){
            camera.offset.y = -antPositionY + CAMERA_FOLLOW_THRESH;
        }
        if(antPositionY + camera.offset.y > (heightWindow - CAMERA_FOLLOW_THRESH)){
            camera.offset.y = -antPositionY + (heightWindow - CAMERA_FOLLOW_THRESH);
        }
//ssssssssssssssssss



        if(camera.offset.x > 0){
            camera.offset.x = 0;
        }
        
        if(camera.offset.x < -worldWidth + widthWindow + CAMERA_FOLLOW_THRESH){
            camera.offset.x = -worldWidth + widthWindow + CAMERA_FOLLOW_THRESH;
        }
        if(camera.offset.y > 0){
            camera.offset.y = 0;
        }
        if(camera.offset.y < -worldHeight + heightWindow + CAMERA_FOLLOW_THRESH){
            camera.offset.y = -worldHeight + heightWindow + CAMERA_FOLLOW_THRESH;
        }

       Rectangle antRect = {
        .x = antPositionX,
        .y = antPositionY,
        .width = antHeight,
        .height = antWidth,
        };

        Vector2 antOrigin = {
            .x = antHeight/2,
            .y = antWidth/2,
        };
        DrawTexturePro(antTexture, antTextureRect, antRect, antOrigin, antRotation, WHITE);
        EndDrawing();
    }
    UnloadImage(antImage);
    UnloadTexture(antTexture);
    UnloadImage(backgroundImage);
    UnloadTexture(backgroundTexture);
    
    CloseWindow();
    return 0;
}
