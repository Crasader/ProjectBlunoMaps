//
//  Actor.cpp
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 8/1/15.
//
//

#include "Actor.h"
#include "Vision.h"
#include "ActorController.h"
#include "GameStateManager.h"

Actor::Actor(ActorController *controller, int actorType, int startingTile, float speed) :
m_controller (controller), m_actorType (actorType), m_startingTile(startingTile), m_speed(speed)
{
    m_rotSpeed = 0;
    m_rotateTo = 0;
    m_reachedFlg = true;
    m_rotatedFlg = true;
    m_vision = nullptr;
}

void Actor::changeController(ActorController *actorController)
{
    m_controller = actorController;
}

void Actor::setVision(Vision *vision)
{
    m_vision = vision;
}

int Actor::getActorType()
{
    return m_actorType;
}

int Actor::getStartingTile()
{
    return m_startingTile;
}

void Actor::update(float dt)
{
    m_controller->update(*this, dt);
    if(m_vision != nullptr)
        m_vision->update(dt);
}

void Actor::move(float dt)
{
    m_reachedFlg = false;
    
    // Move a sprite to a specific location over duration.
    m_position.x += (m_moveToPt.x - m_position.x) * (m_speed *dt);
    m_position.y += (m_moveToPt.y - m_position.y) * (m_speed *dt);
    m_avatar->setPosition(m_position);
    if(m_vision != nullptr)
    {
        m_vision->setPosition(m_position);
    }
    
    if( (fabsf(m_moveToPt.x - m_position.x) <= 2 && fabsf(m_moveToPt.y - m_position.y) <= 2) )
    {
        m_reachedFlg = true;
    }
}

void Actor::rotate(float dt)
{
    m_rotatedFlg = false;
    
    // Rotate the vision over duration.
    if(m_vision != nullptr)
    {
        float degree = m_vision->getRotation();
        
        degree += m_rotSpeed *dt;
        m_vision->setRotation(degree);
        
        if( (fabsf(degree - m_rotateTo) <= 0.5) )
        {
            float degree = (int)(m_rotateTo + 0.5f) % 360;
            m_vision->setRotation(degree);
            m_rotatedFlg = true;
        }
    }
    
}

void Actor::setMoveTo(Vector2 position)
{
    m_moveToPt = position;
    m_distance.x = (m_moveToPt.x - m_position.x);
    m_distance.y = (m_moveToPt.y - m_position.y);
    m_reachedFlg = false;
}

void Actor::rotateBy(float degree, float speed)
{
    m_rotSpeed = speed;
    m_rotateTo = m_vision->getRotation() + degree;
    m_rotatedFlg = false;
}

bool Actor::reachedToDestination()
{
    return m_reachedFlg;
}

bool Actor::rotatedToDestination()
{
    return m_rotatedFlg;
}

Actor::~Actor()
{
    
}
