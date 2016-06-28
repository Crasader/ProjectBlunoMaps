#include "MainScene.h"
#include "World.h"

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
    
    World *world = World::getInstance();
    
    auto fileUtils = FileUtils::getInstance();

    world->loadLevel(fileUtils->fullPathForFilename("Levels/testlevel.json"));

    return true;
}

bool MainScene::onTouchBegan(Touch* touch, Event* event)
{
    static World *world = World::getInstance();
    
    //update loop updating game logic and all things that need update
    world->update(touch->getLocation());
    
    //printf("x: %f, Y: %f", touch->getLocation().x, touch->getLocation().y);
    
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

