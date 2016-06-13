//
//  GameObject.cpp
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 7/27/15.
//
//

#include "GameObject.h"

GameObject::GameObject() {}


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
}

void GameObject::setAvatar(const std::string &avatarFileName, float depth, float opacity)
{
    m_avatar = Sprite::create(avatarFileName);
    m_avatar->setOpacity(opacity);
}

Sprite* GameObject::getAvatar()
{
    return m_avatar;
}

GameObject::~GameObject()
{
    
}
