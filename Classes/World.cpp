//
//  World.cpp
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 8/2/15.
//
//


#include "World.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <iostream>
#include <string>

World* World::m_instance = NULL;


using namespace rapidjson;


void World::loadLevel(std::string filename)
{
    FILE *pFile = fopen(filename.c_str(), "r");
    char buffer[65536];
    FileReadStream is(pFile, buffer, sizeof(buffer));
    
    Document document;
    document.ParseStream<kParseStopWhenDoneFlag>(is);
    
    assert(document.HasMember("project"));
    assert(document["project"].IsString());
    
    std::cout << document["project"].GetString() << std::endl;
    
    fclose(pFile);
}

void World::addObject(GameObject* object)
{
    m_gameObjectList.push_back(*object);
    m_scene->addChild(object->getAvatar(), 1);
}

void World::removeObject(GameObject* object)
{
    m_scene->removeChild(object->getAvatar());
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

void World::destroyWorld()
{
    delete m_instance;
}


World::~World()
{
    /*
    std::vector<GameObject>::iterator it;
    for(it = m_gameObjectList.begin(); it != m_gameObjectList.end(); ++it)
    {
        //remove from m_scene
        
        //delete object
        delete &it;
    }
    m_gameObjectList.clear();
    */
}
