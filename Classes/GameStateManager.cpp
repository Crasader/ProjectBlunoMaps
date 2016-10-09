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

void GameStateManager::endGame()
{
    
}

void GameStateManager::update()
{
    switch (m_gameState)
    {
        case GAME_BEGIN:
        {
            m_gameState = PLAYER_TURN;
            break;
        }
        case PLAYER_TURN:
        {
            m_gameState = GUARD_TURN;
            break;
        }
        case GUARD_TURN:
        {
            m_gameState = PLAYER_TURN;
            break;
        }
        default:
            break;
    }
}