//
//  GameObject.h
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 7/27/15.
//
//

#ifndef __ProjectBlunoMaps__GameObject__
#define __ProjectBlunoMaps__GameObject__

#include <stdio.h>
#include "Defs.h"

class GameObject : public Layer
{
protected:
    
    Vector2   m_position;
    Sprite   *m_avatar;
    
public:
    GameObject();
    
    void    setPosition(float x, float y);
    void    setPosition(Vector2 position);
    void    setOpacity(float opacity);
    Vector2 getPosition();
    void    setAvatar(const std::string& avatarFileName, float depth);
    void    setAvatar(const std::string &avatarFileName, float depth, float opacity);
    Sprite* getAvatar();
    void    setColor(float x, float y, float z);
    
    virtual void update(Vector2 ) {}
    
    void update(float) override;
    
    virtual ~GameObject();
};

typedef std::shared_ptr<GameObject> MGameObject;

#endif /* defined(__ProjectBlunoMaps__GameObject__) */
