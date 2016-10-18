//
//  World.cpp
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 8/2/15.
//
//

#include <iostream>
#include <string>

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

#include "World.h"
#include "GameObject.h"
#include "Grid.h"
#include "Actor.h"
#include "GuardController.h"
#include "PlayerController.h"

World* World::m_instance = NULL;

using namespace rapidjson;

void World::loadLevel(std::string filename)
{
    FILE *pFile = fopen(filename.c_str(), "r");
    char buffer[65536];
    FileReadStream is(pFile, buffer, sizeof(buffer));
    
    Document document;
    document.ParseStream<kParseStopWhenDoneFlag>(is);
    
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    Vector2 origin = Director::getInstance()->getVisibleOrigin();
    
    {
        std::string image = document["Grid"]["image"].GetString();
        float opacity = document["Grid"]["opacity"].GetFloat();
        float startingPtX = document["Grid"]["startingPtX"].GetFloat();
        float startingPtY = document["Grid"]["startingPtY"].GetFloat();
        float lenghtX = document["Grid"]["lenghtX"].GetFloat();
        float lenghtY = document["Grid"]["lenghtY"].GetFloat();
        
        grid = new Grid(Vector2(startingPtX, startingPtY), lenghtX, lenghtY);
        grid->setAvatar(image, opacity);
        grid->setPosition(Vector2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        this->addObject(grid);
    }
    
    int len = document["Obstacles"].Size();
    
    for(int i = 0; i < len; ++i)
    {
        std::string image = document["Obstacles"][i]["image"].GetString();
        float opacity = document["Obstacles"][i]["opacity"].GetFloat();
        float scaleX = document["Obstacles"][i]["scaleX"].GetFloat();
        float scaleY = document["Obstacles"][i]["scaleY"].GetFloat();
        int coord = document["Obstacles"][i]["coord"].GetInt();

        GameObject *obj = new GameObject();
        obj->setAvatar(image, opacity);
        obj->getAvatar()->setScale(scaleX, scaleY);
        Vector2 pt = grid->getTileCoordCenterIso(coord);
        obj->setPosition(pt);
        this->addObject(obj);
    }
    
    len = document["Guards"].Size();
    m_numberOfGuards = 0;
    GuardController *guardControl = new GuardController();
    PlayerController *playerControl = new PlayerController();
    
    for(int i = 0; i < len; ++i)
    {
        std::string image = document["Guards"][i]["image"].GetString();
        float opacity = document["Guards"][i]["opacity"].GetFloat();
        float scaleX = document["Guards"][i]["scaleX"].GetFloat();
        float scaleY = document["Guards"][i]["scaleY"].GetFloat();
        int coord = document["Guards"][i]["coord"].GetInt();
        int type = document["Guards"][i]["type"].GetInt();
        
        Actor *guard = new Actor(guardControl, type, coord);
        guard->setAvatar(image, opacity);
        Vector2 pt = grid->getTileCoordCenterIso(coord);
        guard->setPosition(pt);
        guard->getAvatar()->setScale(scaleX, scaleY);
        guard->getAvatar()->setAnchorPoint(Vector2(0.5f, 0.1f));
        this->addObject(guard);
        ++m_numberOfGuards;
    }
    
    int playerCoord = document["Player"]["coord"].GetInt();
    int movableRadius = document["Grid"]["moveRadius"].GetInt();
   /* std::set<int> tiles = grid->getSurrondingTiles(playerCoord, movableRadius);
    std::set<int>::iterator it;
    
    for (it = tiles.begin(); it != tiles.end(); ++it)
    {
        GameObject *tile = new GameObject;
        tile->setAvatar("radiusTile.png", 1, 125);
        Vector2 pt = grid->getTileCoordCenterIso(*it);
        tile->setPosition(pt);
        this->addObject(tile);
        m_surroundingTiles.push_back(tile);
    }*/
    
    clickedTile = new GameObject();
    clickedTile->setAvatar("yellowRadiusTile.png", 1, 125);
    Vector2 pt = grid->getTileCoordCenterIso(playerCoord);
    clickedTile->setPosition(pt);
    this->addObject(clickedTile);
    
    {
        std::string image = document["Player"]["image"].GetString();
        float opacity = document["Player"]["opacity"].GetFloat();
        //float scaleX = document["Player"]["scaleX"].GetFloat();
        //float scaleY = document["Player"]["scaleY"].GetFloat();
        //float anchorPtX = document["Player"]["anchorPtX"].GetFloat();
        //float anchorPtY = document["Player"]["anchorPtY"].GetFloat();
        int coord = document["Player"]["coord"].GetInt();
        
        player = new Actor(playerControl, PLAYER, coord);
        player->setAvatar(image, opacity);
        pt = grid->getTileCoordCenterIso(coord);
        player->setPosition(pt);
        //player->getAvatar()->setScale(scaleX, scaleY);
        player->getAvatar()->setAnchorPoint(Vector2(0.5f, 0.1f));
        this->addObject(player);
    }
    
    fclose(pFile);
}

void World::update(float dt)
{
    for(std::vector<GameObject *>::iterator itr = m_gameObjectList.begin(); itr != m_gameObjectList.end(); ++itr)
    {
        (*itr)->update(dt);
    }
    
    for(std::vector<GameObject *>::iterator itr = m_tempRemoveObjects.begin(); itr != m_tempRemoveObjects.end(); ++itr)
    {
        removeObject(*itr);
    }
    
    for(std::vector<GameObject *>::iterator itr = m_tempAddObjects.begin(); itr != m_tempAddObjects.end(); ++itr)
    {
       addObject(*itr);
    }
    
    m_tempAddObjects.clear();
    m_tempRemoveObjects.clear();
}

void World::touchDownBegan(Vector2 touchLocation)
{
    //Route * newRoute = new Route;
    //m_routes.push_back(newRoute);
    //newRoute->
}

void World::touchDownMoved(Vector2 touchLocation)
{
    //int lastRoute = m_routes.size() - 1;
    //Route * route = m_routes.at(lastRoute);
   // int clickedOnTile = grid->GetTileNumber(touchLocation);
    
   // std::vector<GameObject *> tiles = m_surroundingTiles;
  //  for ( std::vector<GameObject *>::iterator itr = tiles.begin(); itr != tiles.end(); ++itr)
    {
        //if(.  clickedOnTile)
        {
            
            //break;
        }
    }
    //route->m_routeTiles;
}

void World::touchDownEnded()
{
    
}

void World::destroyWorld()
{
    delete m_instance;
}

World::~World()
{
    /*
    std::vector<GameObject>::iterator it;
    for(it = m_gameObjectList.begin(); it != m_gameObjectList.end(); ++it)
    {
        //remove from m_scene
        
        //delete object
        delete &it;
    }
    m_gameObjectList.clear();
    */
}
