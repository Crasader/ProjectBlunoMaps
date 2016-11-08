//
//  Grid.cpp
//  ProjectBlunoMaps
//
//  Created by Aaraddhya Bhatalkar on 8/1/15.
//
//

#include "Grid.h"
#include "World.h"

Grid::Grid(Vector2 startingPoint, float xLength, float yLength)
:m_startingPoint(startingPoint), m_XLength(xLength), m_YLength(yLength)
{
    m_totalTiles = 0;
    World *world = World::getInstance();
   
    for(int i=0; i < 8; ++i)
    {
        for(int j=0; j < 8; ++j)
        {
            GameObject *tile = new GameObject();
            tile->setAvatar("radiusTile.png", 1, 0.0f);
            tile->setColor(0, 0, 0);
            Vector2 pt = getTileCoordCenterIso(m_totalTiles);
            tile->setPosition(pt);
            m_allTiles.insert( std::pair<int, GameObject *>(m_totalTiles,tile) );
            world->addGameObject(tile);
            m_grid[i][j] = m_totalTiles++;
        }
    }
}

Vector2 Grid::getTileCoordCenterIso(int tileNumber)
{
    int y = tileNumber / 8;
    int x = tileNumber % 8;

    return Vector2( m_startingPoint.x + (x * m_XLength) +(y * m_XLength) + m_XLength, m_startingPoint.y +(x * m_YLength) - (y * m_YLength));
}

int Grid::getTileNumber(Vector2 tileCoord)
{
    float xCoord = (tileCoord.x - m_startingPoint.x)/m_XLength;
    float yCoord = (tileCoord.y - m_startingPoint.y)/m_YLength;
    
    int y = ((xCoord - yCoord)/2.0f);
    int x = ((xCoord + yCoord)/2.0f);
    
    return ((y * 8) + x);
    
}

std::set<int> Grid::getSurrondingTiles()
{
    return m_surroundingTiles;
}

void Grid::markSurrondingTiles(int tileNumber, int radius)
{
    m_surroundingTiles.clear();
    
    //use grid matrix to find out surronds
    m_surroundingTiles = getSurrondingTilesHelper(m_surroundingTiles, tileNumber, radius, false);
    
    //remove the tile
    m_surroundingTiles.erase(tileNumber);
    
    //clear grid and mark surrounding tiles
    for (std::map<int,GameObject *>::iterator it = m_allTiles.begin(); it != m_allTiles.end(); ++it)
    {
        auto search = m_surroundingTiles.find(it->first);
        if(search != m_surroundingTiles.end())
        {
            (it->second)->setOpacity(World::SurroundingTileOpacity);
        }
        else
        {
            (it->second)->setOpacity(0.0f);
        }
    }
}

void Grid::clearSurrondingTiles()
{
    m_surroundingTiles.clear();
    m_routes.clear();

    //clear grid
    for (std::map<int,GameObject *>::iterator it = m_allTiles.begin(); it != m_allTiles.end(); ++it)
    {
        (it->second)->setColor(0,0,0, 0.0f);
    }
}

std::set<int> Grid::getSurrondingTilesHelper(std::set<int> &surroundingTiles, int tileNumber, int radius, bool updown)
{
    
    if(radius <= 0 && !updown)
        return surroundingTiles;
    
    if( (tileNumber % 8) ==  ((tileNumber + 1) % 8 ) -1)
    {
        surroundingTiles.insert(tileNumber+1);
        surroundingTiles = getSurrondingTilesHelper(surroundingTiles, tileNumber + 1, radius - 1, false);
    }
    
    if( (tileNumber -1) >= 0 && ((tileNumber % 8) ==  ((tileNumber - 1) % 8 ) +1) )
    {
        surroundingTiles.insert(tileNumber-1);
        surroundingTiles = getSurrondingTilesHelper(surroundingTiles, tileNumber - 1, radius - 1, false);
    }
    
    if(radius <= 0)
        return surroundingTiles;
    
    int down = tileNumber + 8;
    
    if( down >= 0 && down < m_totalTiles)
    {
        surroundingTiles.insert(down);
        surroundingTiles = getSurrondingTilesHelper(surroundingTiles, down, radius - 1, true);
    }
    
    int up = tileNumber - 8;
    
    if( up >= 0 && up < m_totalTiles)
    {
        surroundingTiles.insert(up);
        surroundingTiles = getSurrondingTilesHelper(surroundingTiles, up, radius - 1, true);
    }
    
    return surroundingTiles;
}


bool Grid::confirmRoute(Vector2 touchLocation)
{
    int clickedTile = getTileNumber(touchLocation);
    auto search = m_surroundingTiles.find(clickedTile);
    
    if(search != m_surroundingTiles.end())
    {
        unsigned long numRoutes = m_routes.size();
        bool createNewRoute = false;
        Route * route;
        
        if(numRoutes > 0)
        {
            //last route
            route = m_routes.back();
            
            if(route->m_carved == true && clickedTile == route->m_routeTiles.back())
            {
                routingTiles = route->m_routeTiles;
                return true;
            }
            else if(route->m_carved)
            {
                createNewRoute = true;
            }
            else
            {
                auto searchTile = find(route->m_routeTiles.begin(), route->m_routeTiles.end(), clickedTile);
                
                if(searchTile != route->m_routeTiles.end())
                {
                    return false;
                }
            }
        }
        
        if( numRoutes == 0 || createNewRoute)
        {
            unsigned long routeGradient = m_surroundingTiles.size();
            
            //new route
            route = new Route(routeGradient, World::RouteTimer);
            m_routes.push_back(route);
        }
        
        route->m_routeTiles.push_back(clickedTile);
        
        std::map<int,GameObject *>::iterator it = m_allTiles.find(clickedTile);
        if (it != m_allTiles.end())
        {
            float gradient = route->getGradient();
            (it->second)->setColor(gradient, 0, 0, World::TileOpacityOnClick);
        }
    }
    return false;
}

void Grid::stopRoute(Vector2 touchLocation)
{
    unsigned long numRoutes = m_routes.size();
    
    if(numRoutes > 0)
    {
        Route * lastRoute = m_routes.back();
       
        if(lastRoute->m_timer == World::RouteTimer)
        {
            lastRoute->m_carved = true;
        }
    }
}

int Grid::moveToLeftTile(int currentTile, int byNumber)
{
    int newTile = currentTile - byNumber;
    return (0 <= newTile && newTile <= 63) ? newTile : -1;
}

int Grid::moveToDownTile(int currentTile, int byNumber)
{
    int newTile = currentTile + (8*byNumber);
    return (0 <= newTile && newTile <= 63) ? newTile : -1;
}

int Grid::moveToUpTile(int currentTile, int byNumber)
{
    int newTile = currentTile - (8*byNumber);
    return (0 <= newTile && newTile <= 63) ? newTile : -1;
}

int Grid::moveToRightTile(int currentTile, int byNumber)
{
    int newTile = currentTile + byNumber;
    return (0 <= newTile && newTile <= 63) ? newTile : -1;
}

void Grid::update(float dt)
{
    for (std::vector<Route *>::iterator it = m_routes.begin(); it != m_routes.end();)
    {
        if((*it)->m_carved == true)
        {
            (*it)->m_timer -= dt;
            if((*it)->m_timer < 0.0f)
            {
                for( std::vector<int>::iterator itr = (*it)->m_routeTiles.begin(); itr != (*it)->m_routeTiles.end(); ++itr)
                {
                    auto search = m_allTiles.find(*itr);
                    if (search != m_allTiles.end())
                    {
                        (search->second)->setColor(0, 0, 0, World::SurroundingTileOpacity);
                    }
                }
                Route *route = *it;
                it = m_routes.erase(it);
                delete route;
            }
            else
            {
                ++it;
            }
        }
        else
        {
            ++it;
        }
    }
}

/*
 Vector2 Grid::getTileCoordCenterP(int tileNumber)
 {
 int y = tileNumber / 8;
 int x = tileNumber % 8;
 
 return Vector2( m_startingPoint.x + (x * m_XLength) + (m_XLength/2) , m_startingPoint.y - (y * m_YLength) - (m_YLength/2) );
 
 }
 
 Vector2 Grid::getTileCoordStartP(int tileNumber)
 {
 int y = tileNumber / 8;
 int x = tileNumber % 8;
 
 return Vector2(x * m_XLength , y * m_YLength);
 }
 
 Vector2 Grid::axisAlignedToIso(Vector2 position)
 {
 Vector2 isoPosition(0, 0);
 isoPosition.x = m_startingPoint.x + (2 * (m_startingPoint.y - position.y ) + (position.x - m_startingPoint.x ) ) / 2;
 isoPosition.y = m_startingPoint.y - (2 * (m_startingPoint.y - position.y) - (position.x - m_startingPoint.x) )/ 2;
 return isoPosition;
 }
 */

Grid::~Grid()
{
    
}
