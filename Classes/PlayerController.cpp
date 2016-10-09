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

void PlayerController::update(Actor &actor, Vector2 location)
{
    if(GameStateManager::getInstance()->getState() == GameState::PLAYER_TURN)
    {
        World *world = World::getInstance();
        Grid * grid = world->grid;
        GameObject * clickedTile = world->clickedTile;

        int clicked = grid->GetTileNumber(location);
        if(clicked >=0 && clicked <= 63)
        {
            Vector2 pt = grid->getTileCoordCenterIso(clicked);
            clickedTile->setPosition(pt);
        }

        Vector2 pos = actor.getPosition();
        int playerOnTile = grid->GetTileNumber(pos);
        std::set<int> tiles = grid->getSurrondingTiles(playerOnTile, 3);
        std::set<int>::iterator it = tiles.find(clicked);
        if(it != tiles.end())
        {
            Vector2 pt = grid->getTileCoordCenterIso(clicked);
            
            actor.move(2.0f, pt);
            
            for( std::vector<GameObject *>::iterator itr = world->surroundingTiles.begin(); itr != world->surroundingTiles.end(); ++itr)
            {
                world->removeGameObject(*itr);
            }
            
            world->surroundingTiles.clear();
            
            std::set<int> tiles = grid->getSurrondingTiles(clicked, 2);
            
            for ( std::set<int>::iterator itr = tiles.begin(); itr != tiles.end(); ++itr)
            {
                Grid *tile = new Grid(Vector2(193.525162,383.001984), 60, 60);
                tile->setAvatar("radiusTile.png", 1, 125);
                Vector2 pt = grid->getTileCoordCenterIso(*itr);
                tile->setPosition(pt);
                world->surroundingTiles.push_back(tile);
                world->addGameObject(tile);
            }
            // win tile
        }
    }
}