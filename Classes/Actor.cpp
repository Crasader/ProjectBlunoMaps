//
//  Actor.cpp
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 8/1/15.
//
//

#include <math.h>
#include "Actor.h"
#include "ActorController.h"
#include "GameStateManager.h"

Actor::Actor(ActorController *controller, int actorType, int startingTile, float speed) :  m_controller (controller), m_actorType (actorType), m_startingTile(startingTile), m_reachedFlg(true), m_speed(speed) {}

void Actor::move(float dt)
{
    m_reachedFlg = false;
    
    // Move a sprite to a specific location over duration.
    m_position.x += (m_moveToPt.x - m_position.x) * (m_speed *dt);
    m_position.y += (m_moveToPt.y - m_position.y) * (m_speed *dt);
    m_avatar->setPosition(m_position);
    
    if( (fabsf(m_moveToPt.x - m_position.x) <= 2 && fabsf(m_moveToPt.y - m_position.y) <= 2) )
    {
        m_reachedFlg = true;
    }
}

void Actor::update(float dt)
{
    m_controller->update(*this, dt);
}

void Actor::changeController(ActorController *actorController)
{
    m_controller = actorController;
}

int Actor::getActorType()
{
    return m_actorType;
}

int Actor::getStartingTile()
{
    return m_startingTile;
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
