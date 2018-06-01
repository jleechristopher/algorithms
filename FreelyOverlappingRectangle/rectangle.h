// FREELY OVERLAPPING RECTANGLE INTERSECTION
// This program takes two rectangles as input and returns the overlapping polygon. It allows for 
// any angle of intersection between the rectangles. The program checks for two types of result 
// vertices: 
// 1) intersection of lines
// 2) vertices from one rectangle internally contained by the other rectangle
// The result vertices are then used to construct a new polygon made from those vertices.
//
// NEW PATTERNS IMPLEMENTED
// 1) GTest library used for unit testing
// 2) Functor with member variable passed in to test whether a vertex is in the upper/lower half
// 3) Static ID generator used to delineate lines/vertices from different polygons
// 
// Author: Chris Lee
// Date: June 1st, 2018
// Last Edited: June 1st, 2018

#ifndef __FO_RECTANGLE_INTERSECTION__
#define __FO_RECTANGLE_INTERSECTION__

#define START 0
#define END 1

#include <vector>
#include <iostream>
#include <algorithm> // stable_sort
#include <sstream> // string stream for printing

struct Vertex
{
	Vertex(const double x, const double y, const int lineId = 0, const int polyId = 0): 
	m_x{x}, 
	m_y{y},
	m_lineId{lineId},
	m_polyId{polyId}
	{
	}
	Vertex(const Vertex& v)
	{
		*this = v;
	}
	Vertex()
	{
	}
	void operator=(const Vertex& v)
	{
		m_x = v.m_x;
		m_y = v.m_y;
		m_lineId = v.m_lineId;
		m_polyId = v.m_polyId;
	}
	bool operator==(const Vertex& v) const
	{
		if ((m_x == v.m_x) && (m_y == (v.m_y)))
		{
			return true;
		}
		return false;
	}
	double m_x;
	double m_y;
	int m_lineId; 
	int m_polyId;
	int m_type;
};

struct Line
{
	// Constructor sets the "start" vertex to be the leftmost vertex, so we can do a left-to-right
	// sweep of the vertices later on
	Line(const Vertex& v1, const Vertex& v2, const int lineId = 0, const int polyId = 0):
	m_lineId{lineId},
	m_polyId{polyId}
	{
		if (v1.m_x < v2.m_x)
		{
			m_start = v1;
			m_end = v2;
		}
		else
		{
			m_start = v2; 
			m_end = v1;
		}

		if (m_start.m_y > m_end.m_y)
		{
			m_top = START;
		}
		else
		{
			m_top = END;
		}

		m_slope = (m_end.m_y - m_start.m_y)/(m_end.m_x - m_start.m_x); // (y2 - y1)/(x2 - x1)
		m_intercept = m_start.m_y - (m_slope * m_start.m_x); // b = y - mx
		m_start.m_lineId = lineId;
		m_start.m_polyId = polyId;
		m_start.m_type = START;
		m_end.m_lineId = lineId;
		m_end.m_polyId = polyId;
		m_end.m_type = END;
	}
	bool operator==(const Line& rhs) const
	{
		if ((m_start == rhs.m_start) && (m_end == rhs.m_end))
		{
			return true;
		}
		return false;
	}

	Vertex m_start;
	Vertex m_end;
	int m_top;
	double m_slope;
	double m_intercept;
	int m_lineId; 
	int m_polyId;	
};

class Polygon
{
protected:
	struct IsUpperHalf
	{
		IsUpperHalf(const Vertex& dividingVertex): m_dividingVertex{dividingVertex}
		{
		}

		bool operator()(const Vertex& v1, const Vertex& v2)
		{
			if ((v1 == m_dividingVertex) || (v2 == m_dividingVertex))
			{
				return false; // the divider should not move
			}
			if ((v1.m_y > m_dividingVertex.m_y) && (v2.m_y <= m_dividingVertex.m_y))
			{
				return true;
			}
			return false;
		}
		Vertex m_dividingVertex;
	};
public: 
	int m_polyId;
	std::vector<Vertex> m_pts;
	std::vector<Line> m_lines;

	Polygon()
	{
	}
	Polygon(const std::vector<Vertex>& pts): m_polyId{s_idGenerator++}, m_pts{pts}
	{
		sortCCW(m_pts);
		int lineId = 0;
		for (int ii = 0; ii < m_pts.size() - 1; ++ii)
		{
			m_lines.push_back(Line(m_pts[ii], m_pts[ii + 1], lineId, m_polyId));
			++lineId;
		}
		m_lines.push_back(Line(m_pts[m_pts.size()-1], m_pts[0], lineId, m_polyId));
	}
	void printPts(std::stringstream& outString) const
	{
		int count = 0;
		for (auto& vert : m_pts)
		{
			outString << "Rank: " << count << " x: " << vert.m_x << " y: " << vert.m_y << std::endl;
			++count;
		}
	}
	bool operator==(const Polygon& rhs)
	{
		if (m_lines.size() != rhs.m_lines.size())
		{
			return false;
		}
		for (int ii = 0; ii < m_lines.size(); ++ii)
		{
			if (!(m_lines[ii] == rhs.m_lines[ii]))
			{
				return false;
			}
		}
		return true; 
	}
	int getId() const
	{
		return m_polyId;
	}
protected:
	static int s_idGenerator;

	// 1) Sorts points from left to right. Equivalent points sorted from bottom to top
	// 2) Stable sorts into upper/lower halves, beginning with leftmost bottommost point
	// 3) Swaps lower half to make the order from right to left
	// End result: upper half sorted left to right, lower half sorted right to left
	void sortCCW(std::vector<Vertex>& pts)
	{
		std::stable_sort(pts.begin(), pts.end(), leftmost_bottommost);
		for (int ii = pts.size() - 1; ii > 0; --ii) // get rid of duplicates
		{
			if (pts[ii] == pts[ii-1])
			{
				pts.erase(pts.begin() + ii);
			}
		}
		IsUpperHalf divider(pts[0]);
		std::stable_sort(pts.begin(), pts.end(), divider);
		int lowerHalfStart = 1;
		while ((lowerHalfStart < pts.size()) && (pts[lowerHalfStart].m_y > pts[0].m_y))
		{
			++lowerHalfStart;
		}
		int count = 0;
		int numSwaps = (pts.size() - lowerHalfStart) / 2;
		while (count < numSwaps)
		{
			std::swap(pts[lowerHalfStart + count], pts[pts.size() - 1 - count]);
			++count;
		}
	}

	static bool leftmost_bottommost(const Vertex& v1, const Vertex& v2)
	{
		if (v1.m_x == v2.m_x)
		{
			return v1.m_y < v2.m_y;
		}
		return v1.m_x < v2.m_x;
	}	
};

std::ostream& operator<< (std::ostream& os, const Polygon& p) 
{
    std::stringstream outString;
    p.printPts(outString);
    os << "PolyID: " << p.getId() << std::endl;
    os << outString.str();
    return os;
}

std::ostream& operator<< (std::ostream& os, const Vertex& v) 
{
	os << "x: " << v.m_x << " y: " << v.m_y << std::endl;
    return os;
}

#endif