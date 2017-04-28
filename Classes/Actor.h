//
//  Actor.h
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 8/1/15.
//
//

#ifndef __ProjectBlunoMaps__Actor__
#define __ProjectBlunoMaps__Actor__

#include "GameObject.h"

enum ActorType
{
    PLAYER = 0,
    STILL_GUARD = 1,
    ROTATING_GUARD = 2,
    MOVE_DOWN_THREE_BLOCKS_GUARD = 3,
    MOVE_LEFT_THREE_BLOCKS_GUARD = 4
};

class Vision;
class ActorController;

class Actor : public GameObject
{
private:
    Actor(){}
    
private:
   
    Vector2         m_moveToPt;
    Vector2         m_distance;
    float           m_speed;
    float           m_rotSpeed;
    float           m_rotateTo;
    int             m_actorType;
    int             m_startingTile;
    
    ActorController *m_controller;
    Vision          *m_vision;
    
    bool            m_reachedFlg;
    bool            m_rotatedFlg;
    
public:
    Actor(ActorController *, int, int, float);
    
    void    changeController(ActorController *);
    void    setMoveTo(Vector2);
    void    rotateBy(float degree, float speed);
    void    setVision(Vision *vision);
    
    void    move(float dt);
    void    rotate(float dt);
    
    int     getActorType();
    int     getStartingTile();
    
    bool    reachedToDestination();
    bool    rotatedToDestination();
    
    virtual void update(float);
    virtual ~Actor();
};

#endif /* defined(__ProjectBlunoMaps__Actor__) */
