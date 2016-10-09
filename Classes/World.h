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
    
    World() {}
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
    
    std::vector<GameObject *> m_tempAddObjects;
    std::vector<GameObject *> m_tempRemoveObjects;

public:
    Grid        *grid;
    Actor       *player;
    GameObject  *clickedTile;
    //would need a vector of guards like
    //std::vector<Actor *> guards;

    std::vector<GameObject *> m_gameObjectList;
    std::vector<GameObject *> surroundingTiles;
   
    //would need a list of taboo tiles
    //or just a list and not a list of gameobject like below
    //std::vector<GameObject *> tabooTiles;
    
public:
    
    void   loadLevel(std::string);
    void   update(Vector2 location);
    void   destroyWorld();
    
//put in .inl file
private:
    
    inline void addObject(GameObject* object)
    {
        m_gameObjectList.push_back(object);
        m_scene->addChild(object->getAvatar(), 1);
    }
    
    inline void removeObject(GameObject* object)
    {
        m_scene->removeChild(object->getAvatar());
    }
    
public:
    
    inline void addGameObject(GameObject* object)
    {
        m_tempAddObjects.push_back(object);
    }
    
    inline void removeGameObject(GameObject* object)
    {
        m_tempRemoveObjects.push_back(object);
    }
    
    inline void setScene(Scene *scene)
    {
        m_scene = scene;
    }
    
    inline Scene* getScene()
    {
        return m_scene;
    }
};


#endif /* defined(__ProjectBlunoMaps__World__) */
