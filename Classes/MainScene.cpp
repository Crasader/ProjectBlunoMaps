 #include "MainScene.h"
#include "GameObject.h"
#include "World.h"
#include "Grid.h"
#include "Actor.h"


USING_NS_CC;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    Scene * scene = Scene::create();
    
    World::getInstance()->setScene(scene);
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool MainScene::init()
{
    //super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(MainScene::onTouchMoved, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(MainScene::onTouchCancelled, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    //This is all going to be in World Load Level
   
    Grid *grid = new Grid();
    grid->setAvatar("Grid.png", 1.0f);
    grid->setPosition(Vector2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    
    Actor *player = new Actor();
    player->setAvatar("stickman.png", 1.0f);
    player->setPosition(Vector2(235,435));


    World *world = World::getInstance();
    world->addObject((GameObject*)grid);
    world->addObject((GameObject*)player);


    //update loop updating game logic and all things that need update
   // while(1)
    //    world->update();
    
    return true;
}

bool MainScene::onTouchBegan(Touch* touch, Event* event)
{
    
    return true;
}

void MainScene::onTouchEnded(Touch* touch, Event* event)
{
    cocos2d::log("touch ended");
}

void MainScene::onTouchMoved(Touch* touch, Event* event)
{
    cocos2d::log("touch moved");
}

void MainScene::onTouchCancelled(Touch* touch, Event* event)
{
    cocos2d::log("touch cancelled");
}

