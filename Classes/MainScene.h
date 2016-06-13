#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

class Grid;
class Actor;

class MainScene : public cocos2d::Layer
{
    
private:
    Grid *grid;
    Actor *player;
    Grid *ytile;
    
public:
    
    static cocos2d::Scene* createScene();

    virtual bool init();
      
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
    
    CREATE_FUNC(MainScene);
};

#endif // __MAIN_SCENE_H__
