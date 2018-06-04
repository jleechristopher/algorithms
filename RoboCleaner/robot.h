// ROBOCLEANER
//  
// NEW PATTERNS IMPLEMENTED
// 
// Author: Chris Lee
// Date: June 4th, 2018
// Last Edited: June 4th, 2018

#ifndef __ROBOCLEANER__
#define __ROBOCLEANER__

#include <queue>
#include <vector> 
#include <iostream>
#include <sstream>
#include <memory> // unique_ptr

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define MAX_COLUMNS 100 // arbitrary max chars in a single line of the input string

class FloorMap
{
private:
	class Node
	{
		Node(int tileId, bool impassable): m_id{tileId}, m_impassable{impassable}, m_touched{0}, m_isClean{false} 
		{
			m_neighbors.resize(4);
			m_neighbors[UP] = 0;
			m_neighbors[DOWN] = 0;
			m_neighbors[LEFT] = 0;
			m_neighbors[RIGHT] = 0;
		}
		int m_id;
		bool m_impassable; // whether or not we can move through this tile
		int m_touched; // times robot moved onto this tile
		bool m_isClean;
		std::vector<int> m_neighbors;	
	};
public:
	FloorMap(std::stringstream& Input): m_idGenerator{1}
	{
		m_startPos = 0;
		// TODO
		// parse starting pos
		// add objects in map 
	}
	FloorMap(const FloorMap& masterMap)
	{
		// TODO
		// copies the size of m_nodes but sets every ptr to null except startPos
	}
	Node* getNode(int tileId)
	{
		// TODO
		return m_nodes[id2row(tileId)][id2col(tileId)].get();
	}
	int id2row(int tileId) const
	{
		// TODO
		return 0;
	}
	int id2col(int tileid) const
	{
		// TODO
		return 0;
	}
	void scan(int startId, int direction, const std::vector<int>& newTiles) // returns vector of objects in that direction
	{
		// TODO
	}
	void printMap(std::stringstream& output)
	{

	}
	int getStartPos() const
	{
		return m_startPos;
	}
private:
	std::vector<std::array<std::unique_ptr<Node>, MAX_COLUMNS> > m_nodes;
	int m_idGenerator;
	int m_startPos;
};

class RoboCleaner
{
public:
	RoboCleaner(const FloorMap& masterMap): 
	m_myMap{masterMap}, 
	m_masterMap{&masterMap},
	m_pos{masterMap.getStartPos()}, 
	m_xMoved{0},
	m_xScanned{0},
	m_xCleaned{0},
	m_xTurned{0}
	{
		// makes a copy of floorMap, initializes start pos
	}
	void cleanFloor(std::stringstream& output)
	{
		while (true)
		{
			if (getNextMoves())
			{
				while (!m_nextMoves.empty())
				{
					// do all moves
				}
			}
			else
			{
				break;
			}
		}
		output << "Times moved: " << m_xMoved << std::endl;
		output << "Times scanned: " << m_xScanned << std::endl;
		output << "Times cleaned: " << m_xCleaned << std::endl;
		output << "Times turned: " << m_xTurned << std::endl;
		m_myMap.printMap(output);
	}
private:
	FloorMap m_myMap; // map discovered by scanning environment
	const FloorMap* m_masterMap; // program input
	std::vector<int> m_newTiles;
	std::queue<int> m_nextMoves;
	int m_nextTile;
	int m_pos;
	int m_ori;
	int m_xMoved; // times moved
	int m_xScanned; // .. scanned
	int m_xCleaned; // .. cleaned
	int m_xTurned; // .. turned	

	void move() // changes m_pos
	{
		// TODO
	}
	void scan() // sends current tileId, m_ori, m_newTiles to masterMap
	{
		// TODO
	}
	void clean() // changes m_pos.isClean
	{
		// TODO
	}
	void turn() // changes m_ori
	{
		// TODO
	}

	// searches for next closest tile. changes m_nextTile to tileId and return true, or returns false if none found
	bool bfs()
	{
		// TODO
		return false;
	}
	bool shortestPath(int nodeId) // adds path to m_nextMoves
	{
		// TODO
		return false; 
	}
	bool shouldScan() // checks for undiscovered parts L/R/Front
	{
		// TODO
		return false;
	}
	bool getNextMoves() // finds closest undiscovered/unclean part. Can return a scan order by returning SCAN in the queue
	{
		// TODO
		return false;
	}
};

#endif