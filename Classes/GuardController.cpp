//
//  GuardController.cpp
//  
//
//  Created by Aaraddhya Bhatalkar on 8/19/16.
//
//

#include "GuardController.h"
#include "GameStateManager.h"
#include "World.h"
#include "Grid.h"
#include "Actor.h"

void GuardController::update(Actor &actor, float dt)
{
    bool actorReachedToDestination = actor.reachedToDestination();
    
    if(GameStateManager::getInstance()->getState() == GameState::GUARD_MOVING && !actorReachedToDestination)
    {
        actor.move(dt);
        actorReachedToDestination = actor.reachedToDestination();
        
        if(actorReachedToDestination)
            GameStateManager::getInstance()->updateToNextState();
    }
    
    if(GameStateManager::getInstance()->getState() == GameState::GUARD_TURN_BEGIN)
    {
        World *world = World::getInstance();
        Grid * grid = world->grid;
      
        int guardsStartingTile = actor.getStartingTile();
        Vector2 position = actor.getPosition();
        int guardOnTile = grid->getTileNumber(position);
        int tileNumber;
        
        switch (actor.getActorType())
        {
            case MOVE_DOWN_THREE_BLOCKS_GUARD:
            {
                if(guardOnTile == guardsStartingTile)
                {
                    tileNumber = grid->moveToDownTile(guardOnTile, 3);
                }
                else
                {
                    tileNumber = grid->moveToUpTile(guardOnTile, 3);
                }
                
                Vector2 pt = grid->getTileCoordCenterIso(tileNumber);
                actor.setMoveTo(pt);
                break;
            }
            case MOVE_LEFT_THREE_BLOCKS_GUARD:
            {
                if(guardOnTile == guardsStartingTile)
                {
                    tileNumber = grid->moveToLeftTile(guardOnTile, 3);
                }
                else
                {
                    tileNumber = grid->moveToRightTile(guardOnTile, 3);
                }
                
                Vector2 pt = grid->getTileCoordCenterIso(tileNumber);
                actor.setMoveTo(pt);
                break;
            }
            default:
                break;
        }
        
        GameStateManager::getInstance()->updateToNextState();
    }
}
