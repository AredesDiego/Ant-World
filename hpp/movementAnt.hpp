#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP
#include<iostream>
#include "raylib.h"

float moveAnt(float antSpeed, float antSpeedUp, float deltaTime, float antSlowDown, float antDirection, float maxSpeedAnt){
        //Move of Ant
        if(IsKeyDown(KEY_UP)){
           antSpeed -= antSpeedUp * deltaTime;
            if(antSpeed > maxSpeedAnt){
                antSpeed = maxSpeedAnt;
            }
        }else if(IsKeyDown(KEY_DOWN)){
            antDirection = 1;
            antSpeed += antSpeedUp * deltaTime;
            if(antSpeed > maxSpeedAnt){
                antSpeed = maxSpeedAnt;
            }
        }
        //speed reduction of friction 
        else{ 
            antSpeed += antSlowDown * deltaTime * antDirection;
            if(antDirection == -1 && antSpeed < 0){
                antSpeed = 0;
            }else if(antDirection == 1 && antSpeed > 0){
                antSpeed = 0;
            }
        }
    return antSpeed;
}
float rotationAnt (float antRotation, const int ROTATION_SPEED , float deltaTime, float antSpeed)
{
        //Rotation of Ant
        if(IsKeyDown(KEY_LEFT)){
            antRotation -= ROTATION_SPEED * deltaTime * std::abs(antSpeed);
        }else if(IsKeyDown(KEY_RIGHT)){
            antRotation += ROTATION_SPEED * deltaTime * std::abs(antSpeed);
        }
        
        if(antRotation >= 360){
            antRotation = 0;
        }
    return antRotation;
}


#endif // MOVEMENT_HPP