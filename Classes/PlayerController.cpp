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
    World *world = World::getInstance();
    Grid * grid = world->grid;
    
    if(GameStateManager::getInstance()->getState() == GameState::MARK_SURROUNDING_TILES)
    {
        Vector2 position = actor.getPosition();
        int playerOnTile = grid->getTileNumber(position);
        
        grid->markSurrondingTiles(playerOnTile, 2);
        
        GameStateManager::getInstance()->updateToNextState();
    }
    
    if(GameStateManager::getInstance()->getState() == GameState::PLAYER_TURN_BEGIN)
    {
        grid->clearSurrondingTiles();
        GameStateManager::getInstance()->updateToNextState();
    }
    
    if(GameStateManager::getInstance()->getState() == GameState::PLAYER_MOVING)
    {
        unsigned long sizeOfTiles = grid->routingTiles.size();
        
        bool actorReachedToDestination = actor.reachedToDestination();
        
        if(sizeOfTiles == 0 && actorReachedToDestination)
            GameStateManager::getInstance()->updateToNextState();
        
        if(sizeOfTiles > 0 && actorReachedToDestination)
        {
            Vector2 position = grid->getTileCoordCenterIso(grid->routingTiles.front());
            grid->routingTiles.erase(grid->routingTiles.begin());
            actor.setMoveTo(position);
        }
        
         actor.move(dt);
    }
}
