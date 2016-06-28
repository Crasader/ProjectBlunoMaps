//
//  ActorController.h
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 8/1/15.
//
//

#ifndef __ProjectBlunoMaps__ActorController__
#define __ProjectBlunoMaps__ActorController__

#include <stdio.h>
#include "Defs.h"

class Actor;

class ActorController
{
public:
    void update(Actor &actor, Vector2 location);
    
};

#endif /* defined(__ProjectBlunoMaps__ActorController__) */
