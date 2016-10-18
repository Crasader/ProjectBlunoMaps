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

Actor::Actor(ActorController *controller, int actorType, int startingTile) :  m_controller (controller), m_actorType (actorType), m_startingTile(startingTile), m_speed(2.0f) {}

void Actor::move(float dt)
{
    // Move a sprite to a specific location over duration.
    m_position.x += (m_moveToPt.x - m_position.x) * (m_speed *dt);
    m_position.y += (m_moveToPt.y - m_position.y) * (m_speed *dt);
    m_avatar->setPosition(m_position);
    
    if( (fabsf(m_moveToPt.x - m_position.x) <= 1 && fabsf(m_moveToPt.y - m_position.y) <= 1) && m_reachedFlg == false )
    {
        GameStateManager::getInstance()->updateToNextState();
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
    m_reachedFlg = false;
}

Actor::~Actor()
{
    
}
