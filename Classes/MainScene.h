#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "Defs.h"

class MainScene : public Layer
{
    
private:
    Vector2 m_oldSingleTouch, m_newSingleTouch;
    float m_oldDistanceMultiTouch, m_newDistanceMultiTouch;
    bool m_firstTimeSetup;
    
public:
   
    static cocos2d::Scene* createScene();

    cocos2d::Camera *gameCamera;
    virtual bool init() override;
      
    bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*) override;
    void onTouchMoved(cocos2d::Touch*, cocos2d::Event*) override;
    void onTouchEnded(cocos2d::Touch*, cocos2d::Event*) override;
    void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*) override;
    
    void onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event*) override;
    void onTouchesMoved(const std::vector<Touch *> &touches, cocos2d::Event*) override;
    void onTouchesEnded(const std::vector<Touch *> &touches, cocos2d::Event*) override;
    
    CREATE_FUNC(MainScene);
    
    bool setup();
    void update(float) override;
};

#endif // __MAIN_SCENE_H__
