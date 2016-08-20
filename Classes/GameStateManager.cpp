//
//  GameStateManager.cpp
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 10/17/15.
//
//

#include "GameStateManager.h"

GameStateManager* GameStateManager::m_instance = NULL;

int GameStateManager::getState()
{
    return m_gameState;
}
