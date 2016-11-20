//
//  GameStateManager.h
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 10/17/15.
//
//

#ifndef __ProjectBlunoMaps__GameStateManager__
#define __ProjectBlunoMaps__GameStateManager__

enum GameState
{
    GAME_BEGIN = 0,
    MARK_SURROUNDING_TILES,
    GET_PLAYER_INPUT,
    PLAYER_TURN_BEGIN,
    PLAYER_MOVING,
    PLAYER_TURN_END,
    GUARD_TURN_BEGIN,
    GUARD_MOVING,
    GUARD_TURN_END,
    GAME_END =999
};


class GameStateManager
{
    
private:

    static GameStateManager *m_instance;
    
    GameStateManager() :m_gameState(MARK_SURROUNDING_TILES) {};
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
    
    int m_guardsCount;
    GameState m_gameState;

public:
    
    int getState();
    void updateToNextState();
    void endGame();
    
};

#endif /* defined(__ProjectBlunoMaps__GameStateManager__) */
