//
//  GameStateManager.h
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 10/17/15.
//
//

#ifndef __ProjectBlunoMaps__GameStateManager__
#define __ProjectBlunoMaps__GameStateManager__

#include <stdio.h>

enum GameState
{
    GAME_BEGIN = 0,
    PLAYER_TURN,
    GUARD_TURN,
    GAME_END
};


class GameStateManager
{
    
private:

    static GameStateManager *m_instance;
    
    GameStateManager();
    GameStateManager(const GameStateManager &){}
    GameStateManager& operator=(const GameStateManager &);
    ~GameStateManager();
    
public:
    static GameStateManager* getInstance()
    {
        if( m_instance == NULL)
            m_instance = new GameStateManager();
        return m_instance;
    }
    
private:
    
    GameState m_gameState;

public:
    
    int getState();
    
};

#endif /* defined(__ProjectBlunoMaps__GameStateManager__) */
