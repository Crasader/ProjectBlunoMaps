//
//  GameObject.cpp
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 7/27/15.
//
//

#include "GameObject.h"

GameObject::GameObject()
{
    m_avatar = Sprite::create();
}


void GameObject::setPosition(float x, float y)
{
    m_position.x = x;
    m_position.y = y;
    m_avatar->setPosition(Vector2(x,y));
}

void GameObject::setPosition(Vector2 position)
{
    m_position = position;
    m_avatar->setPosition(position);
}

Vector2 GameObject::getPosition()
{
    return m_position;
}

void GameObject::setAvatar(const std::string &avatarFileName, float depth)
{
    m_avatar = Sprite::create(avatarFileName);
    m_avatar->setPosition(m_position);
    m_avatar->setGlobalZOrder(depth);
}

void GameObject::setAvatar(const std::string &avatarFileName, float depth, float opacity)
{
    m_avatar = Sprite::create(avatarFileName);
    m_avatar->setPosition(m_position);
    m_avatar->setOpacity(opacity);
    m_avatar->setGlobalZOrder(depth);
}

void GameObject::setScale(float x, float y)
{
    m_avatar->setScale(x,y);
}

void GameObject::setAnchorPoint(Vector2 position)
{
    m_avatar->setAnchorPoint(position);
}

void GameObject::setColor(float x, float y, float z)
{
    m_avatar->setColor(Color(x, y, z));
}

void GameObject::setColor(float x, float y, float z , float opacity)
{
    m_avatar->setColor(Color(x, y, z));
    m_avatar->setOpacity(opacity);
}

void GameObject::setOpacity(float opacity)
{
    m_avatar->setOpacity(opacity);
}

void GameObject::setRotation(float rad)
{
    m_avatar->setRotation(rad);
}

Sprite* GameObject::getAvatar()
{
    return m_avatar;
}

void GameObject::isAGameObject()
{
    m_avatar->setCameraMask((unsigned short)cocos2d::CameraFlag::USER2);
}

void GameObject::isAHUDObject()
{
     m_avatar->setCameraMask((unsigned short)cocos2d::CameraFlag::DEFAULT);
}
 
void GameObject::update(float t)
{
   
}

GameObject::~GameObject()
{
    
}
