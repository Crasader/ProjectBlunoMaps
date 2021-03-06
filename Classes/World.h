//
//  World.h
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 8/2/15.
//
//

#ifndef __ProjectBlunoMaps__World__
#define __ProjectBlunoMaps__World__

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
    std::vector<GameObject *> m_gameObjectList;
    
    int m_numberOfGuards;

public:
    Grid        *grid;
    Actor       *player;
    
    //would need a vector of guards like
    //std::vector<Actor *> guards;
    //would need a list of taboo tiles
    //or just a list and not a list of gameobject like below
    //std::vector<GameObject *> tabooTiles;
    
public:
    //config game settings
    static float TileOpacityOnClick;
    static float SurroundingTileOpacity;
    static float ZoomFactor;
    static float RouteTimer;
    static float MaxZoomIn;
    static float MaxZoomOut;
    
public:
    
    void    loadLevel(std::string);
    void    loadConfig(std::string);
    void    update(float);
    
    void    destroyWorld();
    
public:
    
    void    touchDownBegan(Vector2);
    void    touchDownMoved(Vector2);
    void    touchDownEnded(Vector2);
    
//put in .inl file
private:
    
    inline void addObject(GameObject* object)
    {
        m_gameObjectList.push_back(object);
        m_scene->addChild(object->getAvatar(), 0);
    }
    
    inline void removeObject(GameObject* object)
    {
        m_scene->removeChild(object->getAvatar());
    }
    
    inline void addHUDObject(GameObject* object)
    {
        m_gameObjectList.push_back(object);
        m_scene->addChild(object->getAvatar(), 1);
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
    
    inline int getGuardsCount()
    {
        return m_numberOfGuards;
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
