//
//  Vision.h
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 11/5/16.
//
//

#ifndef Vision_h
#define Vision_h

#include "GameObject.h"

class Vision : public GameObject
{
private:
    Vision() {}
    
private:
    float   m_height;
    float   m_radius;
    float   m_direction;
    
public:

    Vision(float height, float radius, float direction);
    void setRotation(float rad);
    virtual void update(float);
    
    //virtual ~Vision();
};

#endif /* Vision_h */
