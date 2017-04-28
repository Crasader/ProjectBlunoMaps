//
//  UIManager.cpp
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 11/25/16.
//
//

#include <iostream>
#include <string>

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

#include "UIManager.h"
#include "GameStateManager.h"
#include "World.h"

using namespace rapidjson;

UIManager* UIManager::m_instance = NULL;

void UIManager::loadUI(std::string filename)
{
    World * world = World::getInstance();
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    FILE *pFile = fopen(filename.c_str(), "r");
    char buffer[65536];
    FileReadStream is(pFile, buffer, sizeof(buffer));
    
    Document document;
    document.ParseStream<kParseStopWhenDoneFlag>(is);
    
    
    m_UIRect = cocos2d::Rect(0, 0, 2* visibleSize.width, (2*visibleSize.height) - 200);
    
    GameObject *uiBackdrop = new GameObject();
    uiBackdrop->getAvatar()->setPosition(Vector2(0, 2*visibleSize.height - 200));
    uiBackdrop->getAvatar()->setTextureRect(m_UIRect);
    uiBackdrop->getAvatar()->setColor(cocos2d::Color3B::YELLOW);
    world->addGameObject(uiBackdrop);

    int len = document["UI"].Size();

    for(int i = 0; i < len; ++i)
    {
        std::string image = document["UI"][i]["image"].GetString();
        float opacity = document["Guards"][i]["opacity"].GetFloat();
        float scaleX = document["Guards"][i]["scaleX"].GetFloat();
        float scaleY = document["Guards"][i]["scaleY"].GetFloat();
        //float anchorPtX = document["Player"]["anchorPtX"].GetFloat();
        //float anchorPtY = document["Player"]["anchorPtY"].GetFloat();
        int offsetX = document["UI"][i]["offsetX"].GetInt();
        int offsetY = document["UI"][i]["offsetY"].GetInt();
        
        uiObject= new GameObject();
        uiObject->setAvatar(image, 1, opacity);
        uiObject->setPosition(visibleSize.width - offsetX, visibleSize.height - offsetY);
        uiObject->setScale(scaleX, scaleY);
        uiObject->isAHUDObject();
        world->addGameObject(uiObject);
        
        m_UIRect = uiObject->getAvatar()->getBoundingBox();
        
    }
    
    fclose(pFile);
}

void UIManager::touchDownBegan(Vector2 touchLocation)
{
    if(GameStateManager::getInstance()->getState() == GameState::GET_PLAYER_INPUT)
    {
       if( m_UIRect.containsPoint(touchLocation))
       {
          uiObject->setColor(1,45,45, 50);
           
       }
        
        //if(grid->confirmRoute(touchLocation))
         //   GameStateManager::getInstance()->updateToNextState();
    }
}

void UIManager::touchDownMoved(Vector2 touchLocation)
{
    if(GameStateManager::getInstance()->getState() == GameState::GET_PLAYER_INPUT)
    {
        //grid->confirmRoute(touchLocation);
    }
}

void UIManager::touchDownEnded(Vector2 touchLocation)
{
    if(GameStateManager::getInstance()->getState() == GameState::GET_PLAYER_INPUT)
    {
       // grid->stopRoute(touchLocation);
    }
}
