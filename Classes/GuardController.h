//
//  GuardController.h
//  
//
//  Created by Aaraddhya Bhatalkar on 8/19/16.
//
//

#ifndef ____GuardController__
#define ____GuardController__

#include "ActorController.h"

class Actor;

class GuardController : public ActorController
{
public:
    virtual void update(Actor &actor, float dt);
    
};
#endif /* defined(____GuardController__) */
