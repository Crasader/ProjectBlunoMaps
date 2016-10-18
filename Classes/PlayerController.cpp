//
//  PlayerController.cpp
//  
//
//  Created by Aaraddhya Bhatalkar on 9/4/16.
//
//

#include "PlayerController.h"
#include "GameStateManager.h"
#include "Actor.h"
#include "World.h"
#include "Grid.h"

void PlayerController::update(Actor &actor, float dt)
{
    if(GameStateManager::getInstance()->getState() == GameState::MARK_SURROUNDING_TILES)
    {
        World *world = World::getInstance();
        Grid * grid = world->grid;

        Vector2 pos = actor.getPosition();
        int playerOnTile = grid->GetTileNumber(pos);
       
        //world->m_surroundingTiles.clear();
        
        grid->markSurrondingTiles(playerOnTile, 2);
        
        GameStateManager::getInstance()->updateToNextState();
    }
    
    if(GameStateManager::getInstance()->getState() == GameState::PLAYER_MOVING)
    {
        actor.move(dt);
    }
    
    
    if(GameStateManager::getInstance()->getState() == GameState::PLAYER_TURN_BEGIN)
    {
        World *world = World::getInstance();
        Grid * grid = world->grid;
        GameObject * clickedTile = world->clickedTile;

        //check if 0 then return
        
       /* int clicked = grid->GetTileNumber(world->getLastTouchLocation());
        if(clicked >=0 && clicked <= 63)
        {
            Vector2 pt = grid->getTileCoordCenterIso(clicked);
            clickedTile->setPosition(pt);
        }*/

       // GameStateManager::getInstance()->updateToNextState();
    }
}
