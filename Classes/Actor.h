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
    STILL_GUARD,
    ROTATING_GUARD,
    MOVE_DOWN_THREE_BLOCKS_GUARD,
    MOVE_LEFT_THREE_BLOCKS_GUARD
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
    int             m_actorType;
    int             m_startingTile;
    ActorController *m_controller;
    Vision          *m_vision;
    bool            m_reachedFlg;
    
public:
    Actor(ActorController *, int, int, float);
    
    void    changeController(ActorController *);
    void    move(float dt);
    void    setMoveTo(Vector2);
    bool    reachedToDestination();
    
    void    setVision(Vision *vision);
    
    int     getActorType();
    int     getStartingTile();
    
    virtual void update(float);
    virtual ~Actor();
};

#endif /* defined(__ProjectBlunoMaps__Actor__) */
