//
//  GameStateManager.cpp
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 10/17/15.
//
//

#include "GameStateManager.h"
#include "World.h"

GameStateManager* GameStateManager::m_instance = NULL;

int GameStateManager::getState()
{
    return m_gameState;
}

void GameStateManager::endGame()
{
    
}

void GameStateManager::updateToNextState()
{
    switch (m_gameState)
    {
        case GAME_BEGIN:
        {
            m_gameState = MARK_SURROUNDING_TILES;
            break;
        }
        case MARK_SURROUNDING_TILES:
        {
            m_gameState = GET_PLAYER_INPUT;
            break;
        }
        case GET_PLAYER_INPUT:
        {
            m_gameState = PLAYER_TURN_BEGIN;
            break;
        }
        case PLAYER_TURN_BEGIN:
        {
            m_gameState = PLAYER_MOVING;
            break;
        }
        case PLAYER_MOVING:
        {
            m_gameState = GUARD_TURN_BEGIN;
            break;
        }
        case GUARD_TURN_BEGIN:
        {
            m_gameState = GUARD_MOVING;
            break;
        }
        case GUARD_MOVING:
        {
            --m_guardsCount;
            if(m_guardsCount <= 0)
            {
                m_guardsCount = World::getInstance()->getGuardsCount();
                m_gameState = PLAYER_TURN_BEGIN;
            }
            break;
        }
        default:
            break;
    }
}
