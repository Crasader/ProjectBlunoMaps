//
//  Actor.h
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 8/1/15.
//
//

#ifndef __ProjectBlunoMaps__Actor__
#define __ProjectBlunoMaps__Actor__

#include <stdio.h>
#include "GameObject.h"

enum ActorType
{
    PLAYER = 0,
    STILL_GUARD,
    ROTATING_GUARD,
    MOVE_DOWN_THREE_BLOCKS_GUARD,
    MOVE_LEFT_THREE_BLOCKS_GUARD
};

class ActorController;

class Actor : public GameObject
{
private:
    Actor(){}
    
private:
    int m_actorType;
    int m_startingTile;
    ActorController *m_controller;
    
public:
    Actor(ActorController *, int, int);
    virtual void update(Vector2);
    void changeController(ActorController *);
    void move(float duration, Vector2 toPosition);
    int  getActorType();
    int  getStartingTile();
    virtual ~Actor();
};

#endif /* defined(__ProjectBlunoMaps__Actor__) */
