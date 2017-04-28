//
//  Vision.cpp
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 11/5/16.
//
//

#include <stdio.h>
#include "Vision.h"
#include "World.h"
#include "Grid.h"
#include "Actor.h"

Vision::Vision(float height, float radius, float direction)
:m_height(height), m_direction(direction), m_radius(radius)
{
 
}

void Vision::update(float)
{
    World * world = World::getInstance();
    Actor * player = world->player;
    Vector2 playerPosition = player->getPosition();
    float distance = m_position.distance(playerPosition);
    
    if(distance <= m_height)
    {
        Vector2 toPlayer = playerPosition - m_position;
        toPlayer.normalize();
        
        float radian = -m_direction * M_PI/ 180.0;
    
        Vector2 toGuard = Vector2(cos(radian), sin(radian));
        toGuard.normalize();

        float dotproduct = toPlayer.dot(toGuard);
        float angle = acos(dotproduct);
        
        angle = angle * 180.0 / M_PI;
        
        //printf("dotproduct: %f\n", dotproduct);
        //printf("angle: %f\n", angle);
    
        if( angle <= m_radius/2 )
            world->grid->lockDown();
    }
}

void Vision::setRotation(float rad)
{
    m_direction = rad;
    m_avatar->setRotation(rad);
}

float Vision::getRotation()
{
    return m_direction;
}
