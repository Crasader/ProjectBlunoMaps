//
//  Actor.cpp
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 8/1/15.
//
//

#include "Actor.h"
#include "ActorController.h"

void Actor::move(float duration, Vector2 toPosition)
{
    // Move a sprite to a specific location over duration.
    auto moveTo = cocos2d::MoveTo::create(duration, toPosition);
    m_avatar->runAction(moveTo);
    m_position = toPosition;
}

void Actor::update(Vector2 location)
{
    m_controller->update(*this, location);
}

Actor::~Actor()
{
    
}
