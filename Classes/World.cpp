//
//  World.cpp
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 8/2/15.
//
//

#include <iostream>
#include <string>

#include "World.h"
#include "GameObject.h"
#include "Grid.h"
#include "Actor.h"

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"


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
    
    int playerCoord = document["Player"]["coord"].GetInt();
    int movableRadius = document["Grid"]["moveRadius"].GetInt();
    std::set<int> tiles = grid->getSurrondingTiles(playerCoord, movableRadius);
    std::set<int>::iterator it;
    
    for (it = tiles.begin(); it != tiles.end(); ++it)
    {
        GameObject *tile = new GameObject;
        tile->setAvatar("radiusTile.png", 1, 125);
        Vector2 pt = grid->getTileCoordCenterIso(*it);
        tile->setPosition(pt);
        this->addObject(tile);
        surroundingTiles.push_back(tile);
    }
    
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
        
        player = new Actor();
        player->setAvatar(image, opacity);
        pt = grid->getTileCoordCenterIso(coord);
        player->setPosition(pt);
        //player->getAvatar()->setScale(scaleX, scaleY);
        player->getAvatar()->setAnchorPoint(Vector2(0.5f, 0.1f));
        this->addObject(player);
    }
    
    fclose(pFile);
}

void World::addObject(GameObject* object)
{
    m_gameObjectList.push_back(*object);
    m_scene->addChild(object->getAvatar(), 1);
}

void World::removeObject(GameObject* object)
{
    m_scene->removeChild(object->getAvatar());
}

void World::setScene(Scene *scene)
{
    m_scene = scene;
}

Scene* World::getScene()
{
    return m_scene;
}

void World::update(Vector2 location)
{
     int clicked = grid->GetTileNumber(location);
     if(clicked >=0 && clicked <= 63)
     {
         Vector2 pt = grid->getTileCoordCenterIso(clicked);
         clickedTile->setPosition(pt);
     }
     
     Vector2 pos = player->getPosition();
     int playerOnTile = grid->GetTileNumber(pos);
     std::set<int> tiles = grid->getSurrondingTiles(playerOnTile, 3);
     std::set<int>::iterator it = tiles.find(clicked);
     if(it != tiles.end())
     {
         Vector2 pt = grid->getTileCoordCenterIso(clicked);
         
         player->move(2.0f, pt);
         
         for( std::vector<GameObject *>::iterator itr = surroundingTiles.begin(); itr != surroundingTiles.end(); ++itr)
         {
             this->removeObject(*itr);
         }
         
         surroundingTiles.clear();
         
         std::set<int> tiles = grid->getSurrondingTiles(clicked, 2);
         
         for ( std::set<int>::iterator itr = tiles.begin(); itr != tiles.end(); ++itr)
         {
             Grid *tile = new Grid(Vector2(193.525162,383.001984), 60, 60);
             tile->setAvatar("radiusTile.png", 1, 125);
             Vector2 pt = grid->getTileCoordCenterIso(*itr);
             tile->setPosition(pt);
             this->addObject(tile);
             surroundingTiles.push_back(tile);
         }
         // win tile
     }
    
    for(std::vector<GameObject>::iterator i = m_gameObjectList.begin(); i != m_gameObjectList.end(); ++i)
    {
        i->update(location);
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
