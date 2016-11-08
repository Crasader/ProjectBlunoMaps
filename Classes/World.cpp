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
#include "GameStateManager.h"

World* World::m_instance = NULL;
float World::TileOpacityOnClick = 0.0f;
float World::SurroundingTileOpacity = 0.0f;
float World::RouteTimer = 0.0f;

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
        float speed = document["Guards"][i]["speed"].GetFloat();
        
        Actor *guard = new Actor(guardControl, type, coord, speed);
        guard->setAvatar(image, opacity);
        Vector2 pt = grid->getTileCoordCenterIso(coord);
        guard->setPosition(pt);
        guard->getAvatar()->setScale(scaleX, scaleY);
        guard->getAvatar()->setAnchorPoint(Vector2(0.5f, 0.1f));
        this->addObject(guard);
        ++m_numberOfGuards;
    }
    
    {
        std::string image = document["Player"]["image"].GetString();
        float opacity = document["Player"]["opacity"].GetFloat();
        float scaleX = document["Player"]["scaleX"].GetFloat();
        float scaleY = document["Player"]["scaleY"].GetFloat();
        float anchorPtX = document["Player"]["anchorPtX"].GetFloat();
        float anchorPtY = document["Player"]["anchorPtY"].GetFloat();
        int coord = document["Player"]["coord"].GetInt();
        float speed = document["Player"]["speed"].GetFloat();
        
        player = new Actor(playerControl, PLAYER, coord, speed);
        player->setAvatar(image, opacity);
        Vector2 pt = grid->getTileCoordCenterIso(coord);
        player->setPosition(pt);
        player->getAvatar()->setScale(scaleX, scaleY);
        player->getAvatar()->setAnchorPoint(Vector2(anchorPtX, anchorPtY));
        this->addObject(player);
        //because player needs to the last rendered
        //please take this hack out and get it flowing from json.
        player->getAvatar()->setGlobalZOrder(150.0f);
    }
    
    fclose(pFile);
}

void World::loadConfig(std::string filename)
{
    FILE *pFile = fopen(filename.c_str(), "r");
    char buffer[65536];
    FileReadStream is(pFile, buffer, sizeof(buffer));
    
    Document document;
    document.ParseStream<kParseStopWhenDoneFlag>(is);
    
    Vector2 origin = Director::getInstance()->getVisibleOrigin();
    
    {
        TileOpacityOnClick = document["Settings"]["TileOpacityOnClick"].GetFloat();
        SurroundingTileOpacity = document["Settings"]["SurroundingTileOpacity"].GetFloat();
        RouteTimer = document["Settings"]["RouteTimer"].GetFloat();
    }
    
    fclose(pFile);
}


void World::update(float dt)
{
    grid->update(dt);
    
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
    if(GameStateManager::getInstance()->getState() == GameState::GET_PLAYER_INPUT)
    {
        if(grid->confirmRoute(touchLocation))
            GameStateManager::getInstance()->updateToNextState();
    }
}

void World::touchDownMoved(Vector2 touchLocation)
{
    if(GameStateManager::getInstance()->getState() == GameState::GET_PLAYER_INPUT)
    {
        grid->confirmRoute(touchLocation);
    }
}

void World::touchDownEnded(Vector2 touchLocation)
{
    if(GameStateManager::getInstance()->getState() == GameState::GET_PLAYER_INPUT)
    {
        grid->stopRoute(touchLocation);
    }
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
