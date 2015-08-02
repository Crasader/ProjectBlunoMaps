//
//  Grid.h
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 8/1/15.
//
//

#ifndef __ProjectBlunoMaps__Grid__
#define __ProjectBlunoMaps__Grid__

#include <stdio.h>
#include "Defs.h"
#include "GameObject.h"

class Grid : public GameObject
{
private:
    int m_totalTiles;
    int m_grid[8][8];
    
public:
    
    Vector2 twoDtoIso(Vector2 position);
    int     getTile(Vector2 position);
    virtual void update(){int t =0;}
    ~Grid();
};

#endif /* defined(__ProjectBlunoMaps__Grid__) */
