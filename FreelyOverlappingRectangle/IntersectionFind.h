#ifndef __INTERSECTION_FIND__
#define __INTERSECTION_FIND__

#include "rectangle.h"

#define START 0
#define END 1

class IntersectionFind
{
public:
	bool getRectangleOverlap(const Polygon& p1, const Polygon& p2, Polygon& result)
	{
		if (!isValidRectangle(p1) || !isValidRectangle(p2))
		{
			return false;
		}

		// get intersecting pts
		std::vector<Vertex> resultVerts;
		resultVerts.push_back(Vertex());
		for (auto& line1 : p1.m_lines)
		{
			for (auto& line2 : p2.m_lines)
			{
				if (getLineIntersection(line1, line2, resultVerts[resultVerts.size() - 1]))
				{
					resultVerts.push_back(Vertex());
				}
			}
		}
		resultVerts.erase(resultVerts.end() - 1);

		// get internal pts
		for (auto& vert : p2.m_pts)
		{
			if (below(p1.m_lines[0], vert) && below(p1.m_lines[1], vert)
				&& above(p1.m_lines[2], vert) && above(p1.m_lines[3], vert))
			{
				resultVerts.push_back(vert);
			}
		}

		// remove any duplicates
		std::sort(resultVerts.begin(), resultVerts.end(), smaller_x);
		for (int ii = resultVerts.size() - 1; ii > 0; --ii)
		{
			if (resultVerts[ii] == resultVerts[ii - 1])
			{
				resultVerts.erase(resultVerts.begin() + ii);
			}
		}

		if (resultVerts.size() < 4)
		{
			return false;
		}
		result = Polygon(resultVerts);
		return true;
	}

	bool getLineIntersection(const Line& line1, const Line& line2, Vertex& result)
	{
		if (line1.m_polyId == line2.m_polyId)
		{
			return false;
		}
		if (line1 == line2)
		{
			return false;
		}
		int x;
		int y;
		if (std::isinf(line1.m_slope) || std::isinf(line2.m_slope)) // vertical line
		{
			if (std::isinf(line1.m_slope) && std::isinf(line2.m_slope))
			{
				return false;
			}
			else if (std::isinf(line1.m_slope))
			{
				y = line2.m_slope * line1.m_start.m_x + line2.m_intercept;
				x = line1.m_start.m_x;
			}
			else
			{
				y = line1.m_slope * line2.m_start.m_x + line1.m_intercept;
				x = line2.m_start.m_x;
			}
		}
		else
		{
			x = (line2.m_intercept - line1.m_intercept)/(line1.m_slope - line2.m_slope);
			y = line1.m_slope * x + line1.m_intercept;
		}

		// check whether intersection is beyond the endpoints of either line 
		if ((x < line1.m_start.m_x) || (x < line2.m_start.m_x) || (x > line1.m_end.m_x) || (x > line2.m_end.m_x))
		{
			return false; 
		}
		if (line1.m_top == START)
		{
			if ((y > line1.m_start.m_y) || (y < line1.m_end.m_y))
			{
				return false;
			}
		}
		else
		{
			if ((y > line1.m_end.m_y) || (y < line1.m_start.m_y))
			{
				return false;
			}
		}
		if (line2.m_top == START)
		{
			if ((y > line2.m_start.m_y) || (y < line2.m_end.m_y))
			{
				return false;
			}
		}
		else
		{
			if ((y > line2.m_end.m_y) || (y < line2.m_start.m_y))
			{
				return false;
			}
		}

		result.m_x = x;
		result.m_y = y;
		return true;
	}

	// definition: 4 lines, opposite lines are parallel (or both have slope = infinity)
	bool isValidRectangle(const Polygon& p)
	{
		if (!(p.m_lines.size() == 4))
		{
			return false;
		}
		if (!(std::isinf(p.m_lines[0].m_slope) && (std::isinf(p.m_lines[2].m_slope))) 
			&& (p.m_lines[0].m_slope != p.m_lines[2].m_slope))
		{
			return false;
		}
		if (!(std::isinf(p.m_lines[1].m_slope) && (std::isinf(p.m_lines[3].m_slope))) 
			&& (p.m_lines[1].m_slope != p.m_lines[3].m_slope))
		{
			return false;
		}
		return true;
	}
private:
	bool above(const Line& line, const Vertex& vert)
	{
		if (std::isinf(line.m_slope))
		{
			if (vert.m_x < line.m_start.m_x)
			{
				return true;
			}
			return false; 			
		}
		else
		{
			double y = line.m_slope * vert.m_x + line.m_intercept;
			if (vert.m_y > y)
			{
				return true; 
			}
			return false; 			
		}
	}
	bool below(const Line& line, const Vertex& vert)
	{
		if (std::isinf(line.m_slope))
		{
			if (vert.m_x > line.m_start.m_x)
			{
				return true;
			}
			return false; 			
		}
		else
		{
			double y = line.m_slope * vert.m_x + line.m_intercept;
			if (vert.m_y < y)
			{
				return true; 
			}
			return false; 			
		}
	}
    static bool smaller_x(const Vertex& objA, const Vertex& objB)
    {
        if (objA.m_x < objB.m_x)
        {
            return true;
        }
        return false;
    }
};

#endif