//
//  PlayerController.h
//  
//
//  Created by Aaraddhya Bhatalkar on 9/4/16.
//
//

#ifndef ____PlayerController__
#define ____PlayerController__

#include "ActorController.h"

class Actor;

class PlayerController : public ActorController
{
public:
    virtual void update(Actor &actor, float dt);
    
};

#endif /* defined(____PlayerController__) */
