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

class ActorController;

class Actor : public GameObject
{
private:
    ActorController *m_controller;
    
public:
    Actor(){}
    virtual void update(Vector2);
    void move(float duration, Vector2 toPosition);
    virtual ~Actor();
};

#endif /* defined(__ProjectBlunoMaps__Actor__) */
