#include "MainScene.h"
#include "World.h"
#include "UIManager.h"
#include "TouchGridWrapper.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    Scene * scene = Scene::create();
    
    World::getInstance()->setScene(scene);
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();
    
    // add layer as a child to  scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
};

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
    
    this->scheduleUpdate();
    
    return true;
}

bool MainScene::setup()
{
    World *world = World::getInstance();
    UIManager *ui = UIManager::getInstance();
    auto fileUtils = FileUtils::getInstance();
    auto cameraDefault = Camera::getDefaultCamera();
    
    gameCamera = Camera::createPerspective(60, 1.77, 1, 1500);
    gameCamera->setCameraFlag(CameraFlag::USER2);
    gameCamera->lookAt(Vec3(0,0,0), Vec3(0,1,0));
    gameCamera->setPosition3D(cameraDefault->getPosition3D());
    world->getScene()->addChild(gameCamera);
    
    world->loadConfig(fileUtils->fullPathForFilename("Config/GameSettings.json"));
    world->loadLevel(fileUtils->fullPathForFilename("Levels/testlevel.json"));
    ui->loadUI(fileUtils->fullPathForFilename("Levels/testlevel.json"));
    
    return true;
}

//update loop
void MainScene::update(float dt)
{
    if(!m_firstTimeSetup)
        m_firstTimeSetup = setup();
    
    static World *world = World::getInstance();
    world->update(dt);
}

/*
 Vector3 get3dPoint(Vector2 point2D)
 //, int width,int height)
 {
 
 //double x = 2.0 * winX / clientWidth - 1;
 // double y = - 2.0 * winY / clientHeight + 1;
 
 Camera *camera = Camera::getDefaultCamera();
 Vector3 point3D(point2D.x, point2D.y, 0);
 Matrix viewProj = camera->getViewProjectionMatrix();
 Vector3 v;
 viewProj.transformPoint(point3D, &v);
 return v;
 }
 
 
 Vector2 get2dPoint(Vector3 point3D)
 {
 Camera *camera = Camera::getDefaultCamera();
 Matrix viewProj = camera->getViewProjectionMatrix();
 Vector3 v;
 viewProj.transformPoint(point3D, &v);
 
 // int winX = (int) Math.round((( point3D.getX() + 1 ) / 2.0) *
 //  width );
 //we calculate -point3D.getY() because the screen Y axis is
 //oriented top->down
 // int winY = (int) Math.round((( 1 - point3D.getY() ) / 2.0) *
 // height );
 return Vector2(v.x, v.y);
 }*/

bool MainScene::onTouchBegan(Touch* touch, Event* event)
{
    //m_oldSingleTouch = Vector2(0,0);
    Vector2 touchLocation = touch->getLocation();
    //Vector3 point = get3dPoint(touchLocation);
    printf("touchLoc x: %f, y: %f", touchLocation.x, touchLocation.y);
    
    //printf("World 3D: x: %f, y: %f, z:%f", point.x, point.y, point.z);
    
    //Vector2 pt = get2dPoint(point);
    //printf("2D x: %f, y: %f", pt.x, pt.y);
    
    //Camera *camera = Camera:: getDefaultCamera();
    // camera->setPosition3D(Vec3(camera->getPositionX(), camera->getPositionY(), camera->getPositionZ() - 200 ));
    
    
    static World *world = World::getInstance();
    world->touchDownBegan(touchLocation);
    
    static UIManager *ui = UIManager::getInstance();
    ui->touchDownBegan(touchLocation);
    
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
    // Camera *camera = Camera:: getDefaultCamera();
    // camera->setPosition3D(Vec3(camera->getPositionX(), camera->getPositionY(), camera->getPositionZ() + 200 ));
    
    
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
    //start//178.638107, y: 319         //70.89  //2   0.7
    //val //278.475342, y: 368.919159   //10 //5
    //val2 //325.398071, y: 391.881348
    
    
    // 66.823883, y: 319.001404touch ended  //9135
    //193.615082, y: 381.897827touch ended //11.98 //5.49
    //257.509918, y: 412.846863touch ended
    
    TouchGridWrapper *wrapper = TouchGridWrapper::getInstance();
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
        
        //camera2D = Camera::getDefaultCamera();
        float cameraZ = gameCamera->getPositionZ();
        //camera->lookAt(Vec3(-568, -320, -553.346008), Vec3(0,1,0));
        
        //camera->setCameraFlag(CameraFlag::USER2);
        
        float zoom = World::ZoomFactor * fabsf(m_newDistanceMultiTouch - m_oldDistanceMultiTouch);
        
        if(m_oldDistanceMultiTouch < m_newDistanceMultiTouch && cameraZ > World::MaxZoomIn )
        {
            //This is a hack //Take it out
            wrapper->setFactors( -(0.9135* zoom), -(0.02* zoom) , 0.1 * zoom , 0.0549* zoom);
            
            //Zoom in
            gameCamera->setPosition3D(Vec3(gameCamera->getPositionX(), gameCamera->getPositionY(), cameraZ - zoom ));
            m_oldDistanceMultiTouch = m_newDistanceMultiTouch;
        }
        else if(cameraZ < World::MaxZoomOut)
        {
            //This is a hack //Take it out
            wrapper->setFactors( (0.9135* zoom), (0.02* zoom),-(0.1 * zoom) , -( 0.0549* zoom));
            
            //Zoom out
            gameCamera->setPosition3D(Vec3(gameCamera->getPositionX(), gameCamera->getPositionY(), cameraZ + zoom ));
            m_oldDistanceMultiTouch = m_newDistanceMultiTouch;
        }
    }
}

void MainScene::onTouchesEnded(const std::vector<Touch *> &touches, cocos2d::Event*)
{
    m_oldDistanceMultiTouch = 0;
}


