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
     touchListener->onTouchMoved = CC_CALLBACK_2(MainScene::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(MainScene::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    auto touchListenerMulti = cocos2d::EventListenerTouchAllAtOnce::create();
    touchListenerMulti->onTouchesBegan = CC_CALLBACK_2(MainScene::onTouchesBegan, this);
     touchListenerMulti->onTouchesEnded = CC_CALLBACK_2(MainScene::onTouchesEnded, this);
    touchListenerMulti->onTouchesMoved = CC_CALLBACK_2(MainScene::onTouchesMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListenerMulti, this);
    
    World *world = World::getInstance();
    
    auto fileUtils = FileUtils::getInstance();
    
    world->loadConfig(fileUtils->fullPathForFilename("Config/GameSettings.json"));
    world->loadLevel(fileUtils->fullPathForFilename("Levels/testlevel.json"));
    
    this->scheduleUpdate();

    return true;
}

//update loop
void MainScene::update(float dt)
{
    static World *world = World::getInstance();
    world->update(dt);
}

bool MainScene::onTouchBegan(Touch* touch, Event* event)
{
    Vector2 touchLocation = touch->getLocation();
    printf("x: %f, y: %f", touchLocation.x, touchLocation.y);
    static World *world = World::getInstance();
    world->touchDownBegan(touchLocation);
    
    return true;
}


void MainScene::onTouchMoved(Touch *touch, Event *event)
{
    Vector2 touchLocation = touch->getLocation();
    static World *world = World::getInstance();
    world->touchDownMoved(touchLocation);
    cocos2d::log("touch moved");
}

void MainScene::onTouchEnded(Touch *touch, Event *event)
{
    Vector2 touchLocation = touch->getLocation();
    static World *world = World::getInstance();
    world->touchDownEnded(touchLocation);
    cocos2d::log("touch ended");
}

void MainScene::onTouchCancelled(Touch *touch, Event *event)
{
    cocos2d::log("touch cancelled");
    onTouchEnded(touch, event);
}

void MainScene::onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event*)
{
    unsigned long tsize = touches.size();
    if(tsize == 2)
    {
        Vector2 touch1 = touches.at(0)->getLocation();
        Vector2 touch2 = touches.at(1)->getLocation();
        
        m_oldDistance = touch1.distance(touch2);
    }
}

void MainScene::onTouchesMoved(const std::vector<Touch *> &touches, cocos2d::Event*)
{
    unsigned long tsize = touches.size();
    if(tsize == 2)
    {
        Vector2 touch1 = touches.at(0)->getLocation();
        Vector2 touch2 = touches.at(1)->getLocation();
        
        m_newDistance = touch1.distance(touch2);
        Camera *_camera = Camera::getDefaultCamera();
        //printf("camera x: %f, y: %f, z:%f", _camera->getPositionX(),_camera->getPositionY(), _camera->getPositionZ());
        float cameraZ = _camera->getPositionZ();
       
        if(m_oldDistance < m_newDistance && cameraZ > 200.0f )
        {
            //Zoom in
            _camera->setPosition3D(Vec3(_camera->getPositionX(), _camera->getPositionY(), cameraZ - (0.1 * fabsf(m_newDistance - m_oldDistance))));
        }
        else if(cameraZ < 800.0f)
        {
            //Zoom out
            _camera->setPosition3D(Vec3(_camera->getPositionX(), _camera->getPositionY(), cameraZ + ( 0.1 * fabsf(m_newDistance - m_oldDistance))));
        }
        
        m_oldDistance = m_newDistance;
    }
}

void MainScene::onTouchesEnded(const std::vector<Touch *> &touches, cocos2d::Event*)
{
    
}

