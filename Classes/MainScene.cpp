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
    //m_oldSingleTouch = Vector2(0,0);
    Vector2 touchLocation = touch->getLocation();
    printf("x: %f, y: %f", touchLocation.x, touchLocation.y);
    static World *world = World::getInstance();
    world->touchDownBegan(touchLocation);
    
    return true;
}


void MainScene::onTouchMoved(Touch *touch, Event *event)
{
    /*
    m_newSingleTouch = touch->getLocation();
    
    if(m_oldSingleTouch == Vector2::ZERO)
    {
        m_oldSingleTouch = m_newSingleTouch;
        return;
    }
    
    Camera *camera = Camera::getDefaultCamera();
    float cameraZ = camera->getPositionZ();
    
    Vector2 dir = m_oldSingleTouch - m_newSingleTouch;
    
    camera->setPosition3D(Vec3(camera->getPositionX() + (0.01*dir.x), camera->getPositionY() + (0.01*dir.y), cameraZ ));
    m_oldDistanceMultiTouch = m_newDistanceMultiTouch;
*/

    Vector2 touchLocation = touch->getLocation();
    static World *world = World::getInstance();
    world->touchDownMoved(touchLocation);
    cocos2d::log("touch moved");
}

void MainScene::onTouchEnded(Touch *touch, Event *event)
{
   // m_oldSingleTouch = Vector2(0,0);
    Vector2 touchLocation = touch->getLocation();
    static World *world = World::getInstance();
    world->touchDownEnded(touchLocation);
    cocos2d::log("touch ended");
}

void MainScene::onTouchCancelled(Touch *touch, Event *event)
{
    onTouchEnded(touch, event);
    cocos2d::log("touch cancelled");
}

void MainScene::onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event*)
{
    m_oldDistanceMultiTouch = 0;
}

void MainScene::onTouchesMoved(const std::vector<Touch *> &touches, cocos2d::Event*)
{
    unsigned long tsize = touches.size();
    if(tsize == 2)
    {
        
        Vector2 touch1 = touches.at(0)->getLocation();
        Vector2 touch2 = touches.at(1)->getLocation();
        
        m_newDistanceMultiTouch = touch1.distance(touch2);
        
        if(m_oldDistanceMultiTouch == 0)
        {
            m_oldDistanceMultiTouch = m_newDistanceMultiTouch;
            return;
        }
        
        Camera *camera = Camera::getDefaultCamera();
        float cameraZ = camera->getPositionZ();
        
        float zoom = World::ZoomFactor * fabsf(m_newDistanceMultiTouch - m_oldDistanceMultiTouch);
        
        if(m_oldDistanceMultiTouch < m_newDistanceMultiTouch && cameraZ > World::MaxZoomIn )
        {
            //Zoom in
            camera->setPosition3D(Vec3(camera->getPositionX(), camera->getPositionY(), cameraZ - zoom ));
            m_oldDistanceMultiTouch = m_newDistanceMultiTouch;
        }
        else if(cameraZ < World::MaxZoomOut)
        {
            //Zoom out
            camera->setPosition3D(Vec3(camera->getPositionX(), camera->getPositionY(), cameraZ + zoom ));
            m_oldDistanceMultiTouch = m_newDistanceMultiTouch;
        }
    }
}

void MainScene::onTouchesEnded(const std::vector<Touch *> &touches, cocos2d::Event*)
{
     m_oldDistanceMultiTouch = 0;
}

