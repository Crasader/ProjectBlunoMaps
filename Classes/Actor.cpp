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
m_controller (controller), m_actorType (actorType), m_startingTile(startingTile), m_reachedFlg(true), m_speed(speed)
{
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

void Actor::update(float dt)
{
    m_controller->update(*this, dt);
    if(m_vision != nullptr)
        m_vision->update(dt);
}

void Actor::setMoveTo(Vector2 position)
{
    m_moveToPt = position;
    m_distance.x = (m_moveToPt.x - m_position.x);
    m_distance.y = (m_moveToPt.y - m_position.y);
    m_reachedFlg = false;
}

bool Actor::reachedToDestination()
{
    return m_reachedFlg;
}

Actor::~Actor()
{
    
}
