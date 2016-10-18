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
    if(GameStateManager::getInstance()->getState() == GameState::GUARD_MOVING)
    {
       actor.move(dt);
    }
    
    //implement cone and calling lock down
    
    //
    
    if(GameStateManager::getInstance()->getState() == GameState::GUARD_TURN_BEGIN)
    {
        World *world = World::getInstance();
        Grid * grid = world->grid;
        
        switch (actor.getActorType())
        {
            case MOVE_DOWN_THREE_BLOCKS_GUARD:
            {
                int guardsStartingTile = actor.getStartingTile();
                Vector2 pos = actor.getPosition();
                int guardOnTile = grid->GetTileNumber(pos);
                
                int tileNumber;
                
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
                int guardsStartingTile = actor.getStartingTile();
                Vector2 pos = actor.getPosition();
                int guardOnTile = grid->GetTileNumber(pos);
                
                int tileNumber;
                
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
