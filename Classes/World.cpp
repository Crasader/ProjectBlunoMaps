//
//  World.cpp
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 8/2/15.
//
//

#include "World.h"


World* World::m_instance = NULL;

void World::addObject(GameObject* object)
{
    m_gameObjectList.push_back(*object);
    m_scene->addChild(object->getAvatar(), 1);
}

void World::setScene(Scene *scene)
{
    m_scene = scene;
}

Scene* World::getScene()
{
    return m_scene;
}

void World::update()
{
    std::vector<GameObject>::iterator it;
    for(it = m_gameObjectList.begin(); it != m_gameObjectList.end(); ++it)
    {
        it->update();
    }
}