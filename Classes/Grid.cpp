//
//  Grid.cpp
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 8/1/15.
//
//

#include "Grid.h"


Vector2 Grid::twoDtoIso(Vector2 position)
{
    Vector2 isoPosition(0, 0);
    isoPosition.x = (2 * position.y + position.x) / 2;
    isoPosition.y = (2 * position.y - position.x) / 2;
    return isoPosition;
}

///void Grid::update()
//{
    
//}