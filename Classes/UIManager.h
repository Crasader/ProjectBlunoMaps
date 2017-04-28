//
//  UIManager.h
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 11/25/16.
//
//

#ifndef UIManager_h
#define UIManager_h

#include "Defs.h"
#include <vector>

using namespace std;

class Ability;
class GameObject;

class UIManager
{
private:
    
    static UIManager *m_instance;
    
    UIManager() {}
    UIManager(const UIManager &){}
    UIManager& operator=(const UIManager &);
    ~UIManager();
    
public:
    static UIManager* getInstance()
    {
        if( m_instance == NULL)
            m_instance = new UIManager();
        return m_instance;
    }
    
private:
    cocos2d::Rect m_UIRect;
    GameObject *uiObject;
    //vector<Ability> m_abilites;
    
public:
    
    void    loadUI(std::string);
    
    void    touchDownBegan(Vector2);
    void    touchDownMoved(Vector2);
    void    touchDownEnded(Vector2);
};

#endif /* UIManager_h */
