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
    
    World *world = World::getInstance();
    
    auto fileUtils = FileUtils::getInstance();

    world->loadLevel(fileUtils->fullPathForFilename("Levels/testlevel.json"));
    
    //This is all going to be in World Load Level //thinking json or xml
    grid = new Grid(Vector2(193.525162,383.001984), 39.93, 19.97);
    grid->setAvatar("Grid.png", 1.0f);
    grid->setPosition(Vector2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    world->addObject(grid);
    
    GameObject *couch = new GameObject();
    couch->setAvatar("couch.png", 1.0f);
    couch->getAvatar()->setScale( 0.5, 0.5 );
    Vector2 pt = grid->getTileCoordCenterIso(53);
    couch->setPosition(pt);
    world->addObject(couch);
    
    ytile = new Grid(Vector2(193.525162,383.001984), 60, 60);
    ytile->setAvatar("yellowRadiusTile.png", 1, 125);
    pt = grid->getTileCoordCenterIso(0);
    ytile->setPosition(pt);
    world->addObject(ytile);
    
    std::set<int> tiles = grid->getSurrondingTiles(0, 2);
    std::set<int>::iterator it;
    
    for (it = tiles.begin(); it != tiles.end(); ++it)
    {
        Grid *tile = new Grid(Vector2(193.525162,383.001984), 60, 60);
        tile->setAvatar("radiusTile.png", 1, 125);
        Vector2 pt = grid->getTileCoordCenterIso(*it);
        tile->setPosition(pt);
        world->addObject(tile);
        surroundingTiles.push_back(tile);
    }
    
    player = new Actor();
    player->setAvatar("stickman.png", 1.0f);
    pt = grid->getTileCoordCenterIso(0);
    player->setPosition(pt);
    player->getAvatar()->setAnchorPoint(Vector2(0.5f, 0.1f));
    world->addObject(player);
    
    return true;
}

bool MainScene::onTouchBegan(Touch* touch, Event* event)
{
    static World *world = World::getInstance();
    //world->m_gameObjectList[2].setPosition(touch->getLocation());
    
    //update loop updating game logic and all things that need update
    //world->update();
    
    //printf("x: %f, Y: %f", touch->getLocation().x, touch->getLocation().y);
    
    int clickedTile = grid->GetTileNumber(touch->getLocation());
    if(clickedTile >=0 && clickedTile <= 63)
    {
        Vector2 pt = grid->getTileCoordCenterIso(clickedTile);
        ytile->setPosition(pt);
    }
    
    
    Vector2 pos = player->getPosition();
    int playerOnTile = grid->GetTileNumber(pos);
    std::set<int> tiles = grid->getSurrondingTiles(playerOnTile, 3);
    std::set<int>::iterator it = tiles.find(clickedTile);
    if(it != tiles.end())
    {
        Vector2 pt = grid->getTileCoordCenterIso(clickedTile);
       
        
        player->move(2.0f, pt);
        
        
        for( std::vector<Grid *>::iterator itr = surroundingTiles.begin(); itr != surroundingTiles.end(); ++itr)
        {
            world->removeObject(*itr);
        }
        
        surroundingTiles.clear();
        
        std::set<int> tiles = grid->getSurrondingTiles(clickedTile, 2);
        
        for ( std::set<int>::iterator itr = tiles.begin(); itr != tiles.end(); ++itr)
        {
            Grid *tile = new Grid(Vector2(193.525162,383.001984), 60, 60);
            tile->setAvatar("radiusTile.png", 1, 125);
            Vector2 pt = grid->getTileCoordCenterIso(*itr);
            tile->setPosition(pt);
            world->addObject(tile);
            surroundingTiles.push_back(tile);
        }
       // win tile
    }
    
    //printf("\ntile: %d\n",tile);
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

