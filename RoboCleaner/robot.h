#ifndef __ROBOCLEANER__
#define __ROBOCLEANER__

#include <vector> 
#include <sstream>
#include <memory> // unique_ptr
#include <stdexcept> // invalid_argument
#include <queue>
#include <iostream>

#define UP 0 // These numbers are in clockwise order because the robot can only turn 90 deg to the right 
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define NUM_ORI 4
#define MAX_COLUMNS 100 // arbitrary max chars in a single line of the input string

class RoboCleaner;

class FloorMap
{
private:
	class Node
	{
	public:
		Node(int tileId, bool impassable): 
		m_id{tileId}, 
		m_touched{0}, 
		m_searchId{0},
		m_isClean{false},
		m_impassable{impassable}
		{
			m_neighbors.resize(4);
			m_neighbors[UP] = 0;
			m_neighbors[DOWN] = 0;
			m_neighbors[LEFT] = 0;
			m_neighbors[RIGHT] = 0;
		}
		Node(const Node& n): // resets memory of neighbors
		m_id{n.m_id}, 
		m_touched{n.m_touched}, 
		m_searchId{n.m_searchId},
		m_isClean{n.m_isClean},
		m_impassable{n.m_impassable}
		{
			m_neighbors.resize(4);
			m_neighbors[UP] = 0;
			m_neighbors[DOWN] = 0;
			m_neighbors[LEFT] = 0;
			m_neighbors[RIGHT] = 0;
		}
	private:
		int m_id;
		int m_touched; // times robot moved onto this tile
		int m_searchId; // used to ID whether a node has been previously looked at in a search
		bool m_isClean;
		bool m_impassable; // whether or not we can move through this tile
		std::vector<int> m_neighbors;	
		friend FloorMap;
		friend RoboCleaner;
	};
public:
	FloorMap(std::stringstream& input_ss): m_idGenerator{0}
	{
		std::string input = input_ss.str();
		m_numRows = 0;
		m_numCol = 0;
		for (int ii = 0; ii < input.length(); ++ii)
		{
			if (input[ii] == '\n')
			{
				++m_numRows;
				if (!m_numCol)
				{
					m_numCol = ii;
				}
			}
		}
		m_nodes.resize(m_numRows);

		int row; 
		int col;
		for (int ii = 0; ii < input.length(); ++ii) 
		{
			row = id2row(m_idGenerator);
			col = id2col(m_idGenerator);
			if (input[ii] == ' ')
			{
				m_nodes[row][col] = std::unique_ptr<Node>();
				++m_idGenerator;
			}
			else if (input[ii] == '|')
			{
				m_nodes[row][col] = std::make_unique<Node>(m_idGenerator, true);
				if (col > 0) // avoid underflow
				{
					if (m_nodes[row][col-1])
					{
						m_nodes[row][col]->m_neighbors[LEFT] = m_idGenerator - 1;
						m_nodes[row][col-1]->m_neighbors[RIGHT] = m_idGenerator;
					}
				}
				if (row > 0) // avoid underflow
				{
					if (m_nodes[row-1][col])
					{
						m_nodes[row][col]->m_neighbors[UP] = m_idGenerator - MAX_COLUMNS;
						m_nodes[row-1][col]->m_neighbors[DOWN] = m_idGenerator;
					}
				}
				++m_idGenerator;
			}
			else if (input[ii] == '.')
			{
				m_nodes[row][col] = std::make_unique<Node>(m_idGenerator, false);
				if (col > 0) // avoid underflow
				{
					if (m_nodes[row][col-1])
					{
						m_nodes[row][col]->m_neighbors[LEFT] = m_idGenerator - 1;
						m_nodes[row][col-1]->m_neighbors[RIGHT] = m_idGenerator;
					}
				}
				if (row > 0) // avoid underflow
				{
					if (m_nodes[row-1][col])
					{
						m_nodes[row][col]->m_neighbors[UP] = m_idGenerator - MAX_COLUMNS;
						m_nodes[row-1][col]->m_neighbors[DOWN] = m_idGenerator;
					}
				}
				++m_idGenerator;
			}
			else if (input[ii] == 'R')
			{

				m_nodes[row][col] = std::make_unique<Node>(m_idGenerator, false);
				if (col > 0) // avoid underflow
				{
					if (m_nodes[row][col-1])
					{
						m_nodes[row][col]->m_neighbors[LEFT] = m_idGenerator - 1;
						m_nodes[row][col-1]->m_neighbors[RIGHT] = m_idGenerator;
					}
				}
				if (row > 0) // avoid underflow 
				{
					if (m_nodes[row-1][col])
					{
						m_nodes[row][col]->m_neighbors[UP] = m_idGenerator - MAX_COLUMNS;
						m_nodes[row-1][col]->m_neighbors[DOWN] = m_idGenerator;
					}
				}
				m_startPos = m_idGenerator;
				++m_idGenerator;
			}
			else if (input[ii] == '\n')
			{
				row = m_idGenerator / MAX_COLUMNS;
				m_idGenerator = (row + 1) * MAX_COLUMNS;
			}
		}
	}
	FloorMap(const FloorMap& masterMap): 
	m_idGenerator{masterMap.m_idGenerator},
	m_startPos{masterMap.m_startPos},
	m_numCol{masterMap.m_numCol},
	m_numRows{masterMap.m_numRows}
	{
		m_nodes.resize(m_numRows);
		int startRow = id2row(m_startPos);
		int startCol = id2col(m_startPos);
		for (int row = 0; row < m_numRows; ++row)
		{
			for (int col = 0; col < m_numCol; ++col)
			{
				m_nodes[row][col] = std::unique_ptr<Node>();
			}
		}
		m_nodes[startRow][startCol] = std::make_unique<Node>(*masterMap.m_nodes[startRow][startCol].get());
		++m_nodes[startRow][startCol]->m_touched;
	}
	Node* getNode(int tileId) const
	{
		return m_nodes[id2row(tileId)][id2col(tileId)].get();
	}
	int id2row(int tileId) const
	{
		return tileId / MAX_COLUMNS;
	}
	int id2col(int tileId) const
	{
		return tileId % MAX_COLUMNS;
	}
	void scan(int startId, int ori, std::vector<int>& newTiles) const // returns vector of objects in that direction
	{
		int startRow = id2row(startId);
		int startCol = id2col(startId);
		if (!m_nodes[startRow][startCol])
		{
			throw std::invalid_argument( "Invalid startId given. This node is nonexistent." );
		}

		newTiles.clear();
		int count = 0;
		if (ori == UP)
		{
			while (m_nodes[startRow-count][startCol]->m_neighbors[UP])
			{
				newTiles.push_back(m_nodes[startRow-count][startCol]->m_neighbors[UP]);
				if (m_nodes[startRow-count][startCol]->m_impassable)
				{
					break;
				}
				++count;
			}
		}
		else if (ori == DOWN)
		{
			while (m_nodes[startRow+count][startCol]->m_neighbors[DOWN])
			{
				newTiles.push_back(m_nodes[startRow+count][startCol]->m_neighbors[DOWN]);
				if (m_nodes[startRow+count][startCol]->m_impassable)
				{
					break;
				}
				++count;
			}
		}
		else if (ori == LEFT)
		{
			while (m_nodes[startRow][startCol-count]->m_neighbors[LEFT])
			{
				newTiles.push_back(m_nodes[startRow][startCol-count]->m_neighbors[LEFT]);
				if (m_nodes[startRow][startCol-count]->m_impassable)
				{
					break;
				}
				++count;
			}
		}
		else if (ori == RIGHT)
		{
			while (m_nodes[startRow][startCol+count]->m_neighbors[RIGHT])
			{
				newTiles.push_back(m_nodes[startRow][startCol+count]->m_neighbors[RIGHT]);
				if (m_nodes[startRow][startCol+count]->m_impassable)
				{
					break;
				}
				++count;
			}			
		}
	}
	void printMap(std::stringstream& output) const
	{
		for (int row = 0; row < m_numRows; ++row)
		{
			for (int col = 0; col < m_numCol; ++col)
			{
				if (!m_nodes[row][col])
				{
					output << " ";
				}
				else
				{
					if (m_nodes[row][col]->m_impassable)
					{
						output << "|";
					}
					else
					{
						if (m_nodes[row][col]->m_touched > 9)
						{
							output << 9;
						}
						else
						{
							output << m_nodes[row][col]->m_touched;
						}
					}
				}

				if (col == (m_numCol - 1))
				{
					output << std::endl;
				}
			}
		}
	}
	int getStartPos() const
	{
		return m_startPos;
	}
private:
	std::vector<std::array<std::unique_ptr<Node>, MAX_COLUMNS> > m_nodes;
	int m_idGenerator;
	int m_startPos;
	int m_numCol;
	int m_numRows;
	friend RoboCleaner;
};

class RoboCleaner
{
private:
	struct SearchData
	{
		SearchData(int ori, int current, int previous): m_ori{ori}, m_current{current}, m_previous{previous}
		{
		}
		int m_ori;
		int m_current;
		int m_previous;
	};
public:
	RoboCleaner(const FloorMap& masterMap, bool printTurns = false): // makes a copy of floorMap, initializes start pos
	m_myMap{masterMap}, 
	m_masterMap{&masterMap},
	m_searchNum{0},
	m_pos{masterMap.getStartPos()},
	m_ori{UP},
	m_xMoved{0},
	m_xScanned{0},
	m_xCleaned{0},
	m_xTurned{0},
	m_printTurns{printTurns}
	{
		m_pathTo.resize(masterMap.m_numRows * MAX_COLUMNS);
	}
	void cleanFloor(std::stringstream& output)
	{
		while (true)
		{
			if (getNextMoves())
			{
				if (m_printTurns)
				{
					m_myMap.printMap(output);
					std::cout << output.str() << std::endl;					
					output.str(std::string());
					// output.clear(); // clear eof bit flag
				}
				while (!m_nextMoves.empty())
				{
					int next = m_nextMoves.back();
					FloorMap::Node* current = m_myMap.getNode(m_pos);
					while (current->m_neighbors[m_ori] != next)
					{
						turn();
					}
					move();
					m_nextMoves.pop_back();
				}
				if (m_nextTile != m_pos)
				{
					throw std::invalid_argument( "Could not reach next planned tile" );
				}
				FloorMap::Node* current = m_myMap.getNode(m_pos);
				if (!current->m_isClean)
				{
					clean();
				}
				if (shouldScan(m_pos, m_ori))
				{
					scan();
				}
			}
			// edge case: robot is stuck in a corner with new space behind him. BFS() does a shouldScan()
			//    which returns false because it only looks at L/R/Front of the robot. The solution is to 
			//    do a virtual turn and check again whether we should scan. 
			else if (shouldScan(m_pos, virtualTurn(m_ori))) 
			{
				turn();
				scan();
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
	std::vector<int> m_nextMoves; // in stack order i.e. next move is m_nextMoves.back()
	std::vector<int> m_pathTo;
	int m_searchNum;
	int m_nextTile;
	int m_pos;
	int m_ori;
	int m_xMoved; // times moved
	int m_xScanned; // .. scanned
	int m_xCleaned; // .. cleaned
	int m_xTurned; // .. turned	
	bool m_printTurns; // option to print the map after every round of moves

	int virtualTurn(int ori) // for when we want to check the case where m_ori is different, without actually turn()ing
	{
		return (ori + 1) % NUM_ORI;
	}

	void move() // changes m_pos
	{
		m_nextTile = m_myMap.getNode(m_pos)->m_neighbors[m_ori];
		if (!m_nextTile)
		{
			throw std::invalid_argument( "Attempted to move into nonexistent tile" );
		}
		else if (m_myMap.getNode(m_nextTile)->m_impassable)
		{
			throw std::invalid_argument( "Cannot move into impassable object" );
		}
		m_pos = m_nextTile;
		++m_myMap.getNode(m_pos)->m_touched;
		++m_xMoved;
	}

	void scan() // sends current tileId, ori, m_newTiles to masterMap
	{
		int front = m_ori;
		int right = (m_ori + 1) % 4;
		int left = (m_ori + 3) % 4;

		m_masterMap->scan(m_pos, front, m_newTiles);
		addTiles(m_pos, front);
		m_masterMap->scan(m_pos, right, m_newTiles);
		addTiles(m_pos, right);
		m_masterMap->scan(m_pos, left, m_newTiles);
		addTiles(m_pos, left);

		++m_xScanned;
	}

	void clean() // changes m_pos.isClean
	{
		m_myMap.getNode(m_pos)->m_isClean = true;
		++m_xCleaned;
	}

	void turn() // changes m_ori
	{
		++m_ori; 
		m_ori = m_ori % 4;
		++m_xTurned;
	}

	void addTiles(int startId, int ori)
	{
		FloorMap::Node* current = m_myMap.getNode(startId);
		for (int ii = 0; ii < m_newTiles.size(); ++ii)
		{
			if (current->m_neighbors[ori])
			{
				current = m_myMap.getNode(current->m_neighbors[ori]);
				continue;
			}
			else
			{
				// create new node
				int newNeighbor = m_newTiles[ii];
				int row = m_myMap.id2row(newNeighbor);
				int col = m_myMap.id2col(newNeighbor);
				m_myMap.m_nodes[row][col] = std::make_unique<FloorMap::Node>(*m_masterMap->getNode(newNeighbor));
				// add neighbors if any
				if (row > 0) // avoid underflow
				{
					if (m_myMap.m_nodes[row-1][col])
					{
						m_myMap.getNode(newNeighbor)->m_neighbors[UP] = m_myMap.m_nodes[row-1][col]->m_id;
						m_myMap.m_nodes[row-1][col]->m_neighbors[DOWN] = newNeighbor;
					}
				}
				if (col > 0) // avoid underflow
				{
					if (m_myMap.m_nodes[row][col-1])
					{
						m_myMap.getNode(newNeighbor)->m_neighbors[LEFT] = m_myMap.m_nodes[row][col-1]->m_id;
						m_myMap.m_nodes[row][col-1]->m_neighbors[RIGHT] = newNeighbor;						
					}
				}
				if (row < (m_myMap.m_numRows - 1)) // avoid overflow
				{
					if (m_myMap.m_nodes[row+1][col])
					{
						m_myMap.getNode(newNeighbor)->m_neighbors[DOWN] = m_myMap.m_nodes[row+1][col]->m_id;
						m_myMap.m_nodes[row+1][col]->m_neighbors[UP] = newNeighbor;						
					}
				}
				if (col < (m_myMap.m_numCol - 1)) // avoid overflow
				{
					if (m_myMap.m_nodes[row][col+1])
					{
						m_myMap.getNode(newNeighbor)->m_neighbors[RIGHT] = m_myMap.m_nodes[row][col+1]->m_id;
						m_myMap.m_nodes[row][col+1]->m_neighbors[LEFT] = newNeighbor;						
					}
				}
				current = m_myMap.getNode(newNeighbor);
			}
		}
	}

	// searches for next closest tile. changes m_nextTile to tileId and return true, or returns false if none found
	bool bfs()
	{
		++m_searchNum;
		std::queue<SearchData> toSearch;
		toSearch.push(SearchData(m_ori, m_pos, m_pos));
		while (!toSearch.empty())
		{
			FloorMap::Node* current = m_myMap.getNode(toSearch.front().m_current);
			if (current->m_searchId == m_searchNum)
			{
				toSearch.pop(); // ignore previously visited node
				continue;
			}

			current->m_searchId = m_searchNum; // mark node as visited
			m_pathTo[current->m_id] = toSearch.front().m_previous; // record way to get to this node
			if (!current->m_isClean)
			{
				m_nextTile = current->m_id;
				return true;
			}
			if (shouldScan(current->m_id, toSearch.front().m_ori))
			{
				m_nextTile = current->m_id;
				return true;
			}

			int ori = toSearch.front().m_ori;
			for (int ii = 0; ii < NUM_ORI; ++ii)
			{
				if ((current->m_neighbors[ori]) && !(m_myMap.getNode(current->m_neighbors[ori])->m_impassable))
				{
					if (!(m_myMap.getNode(current->m_neighbors[ori])->m_searchId == m_searchNum))
					{
						toSearch.push(SearchData(ori, current->m_neighbors[ori], current->m_id)); // push non visited nodes
					}
				}
				ori = virtualTurn(ori);
			}
			toSearch.pop();
		}

		return false;
	}

	bool shouldScan(int tileId, int ori) // checks for undiscovered parts L/R/Front
	{
		FloorMap::Node* current = m_myMap.getNode(tileId); // check Front
		while (true)
		{
			if (current->m_neighbors[ori] == 0)
			{
				return true; // found unknown tile
			}
			FloorMap::Node* neighbor = m_myMap.getNode(current->m_neighbors[ori]);
			if (neighbor->m_impassable)
			{
				break; // reached the limit of scanning because we hit an object/wall
			}
			else
			{
				current = neighbor;
			}
			break;
		}

		ori = virtualTurn(ori); // check R
		current = m_myMap.getNode(tileId);
		while (true)
		{
			if (current->m_neighbors[ori] == 0)
			{
				return true; // found unknown tile
			}
			FloorMap::Node* neighbor = m_myMap.getNode(current->m_neighbors[ori]);
			if (neighbor->m_impassable)
			{
				break; // reached the limit of scanning because we hit an object/wall
			}
			else
			{
				current = neighbor;
			}
		}

		ori = virtualTurn(ori + 1); // we're looking at R currently, so turn twice to check L
		current = m_myMap.getNode(tileId);
		while (true)
		{
			if (current->m_neighbors[ori] == 0)
			{
				return true; // found unknown tile
			}
			FloorMap::Node* neighbor = m_myMap.getNode(current->m_neighbors[ori]);
			if (neighbor->m_impassable)
			{
				break; // reached the limit of scanning because we hit an object/wall
			}
			else
			{
				current = neighbor;
			}
		}		

		return false;
	}

	bool getNextMoves() // finds closest undiscovered/unclean part. Makes stack of next tiles to travel to
	{
		if (!bfs())
		{
			return false;
		}

		m_nextMoves.clear();
		if (m_nextTile == m_pos)
		{
			return true; // no moving necessary
		}

		m_nextMoves.push_back(m_nextTile);
		while (m_pathTo[m_nextMoves.back()] != m_pos) 
		{
			m_nextMoves.push_back(m_pathTo[m_nextMoves.back()]);
		}
		return true;
	}
};

#endif