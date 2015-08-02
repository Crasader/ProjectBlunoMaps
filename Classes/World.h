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

class World
{
private:
    
    static World *m_instance;
    
    //all constructors
    World(){}
    World(const World &){}
    World& operator=(const World &);
   
public:
    static World* getInstance()
    {
        if( m_instance == NULL)
            m_instance = new World();
        return m_instance;
    }
    
    
private:
   
    Scene    *m_scene;
    std::vector<GameObject> m_gameObjectList;
    
public:
    void setScene(Scene *scene);
    Scene* getScene();
    void addObject(GameObject* object);
    void update();
};


#endif /* defined(__ProjectBlunoMaps__World__) */
