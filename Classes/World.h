//
//  World.h
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 8/2/15.
//
//

#ifndef __ProjectBlunoMaps__World__
#define __ProjectBlunoMaps__World__

#include <stdio.h>
#include "Defs.h"
#include "GameObject.h"

class Grid;
class Actor;

class World
{
private:
    
    static World *m_instance;
    
    World(){}
    World(const World &){}
    World& operator=(const World &);
    ~World();
   
public:
    static World* getInstance()
    {
        if( m_instance == NULL)
            m_instance = new World();
        return m_instance;
    }
    
private:
   
    Scene    *m_scene;

public:
    Grid        *grid;
    Actor       *player;
    GameObject  *clickedTile;

    std::vector<GameObject *> surroundingTiles;
    std::vector<GameObject *> tabooTiles;
    
public:
    void   setScene(Scene *scene);
    Scene* getScene();
    
    void   addObject(GameObject* object);
    void   removeObject(GameObject* object);
    
    void   loadLevel(std::string);
    void   update(Vector2 location);
    void   destroyWorld();
    
public:
    std::vector<GameObject> m_gameObjectList;
};


#endif /* defined(__ProjectBlunoMaps__World__) */
