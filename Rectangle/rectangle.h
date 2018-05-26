// RECTANGLE INTERSECTION
// This program takes two rectangles as input and returns the overlapping rectangle. If no 
// intersection is found, it returns a rectangle with coordinates (0,0,0,0).  
//
// NEW PATTERNS IMPLEMENTED
// 1) Return value optimization utilized to avoid extra copying
// 
// Author: Chris Lee
// Date: May 25th, 2018
// Last Edited: May 25th, 2018

#ifndef __RECTANGLE_INTERSECTION__
#define __RECTANGLE_INTERSECTION__

#include <iostream> // operator<<

struct Rectangle
{
	Rectangle(int lt, int rt, int top, int bot): m_lt{lt}, m_rt{rt}, m_top{top}, m_bot{bot}
	{
	}
	int m_lt;
	int m_rt;
	int m_top;
	int m_bot;

	bool operator==(const Rectangle& other)
	{
		if (m_lt != other.m_lt)
		{
			return false;
		}
		if (m_rt != other.m_rt)
		{
			return false;
		}
		if (m_top != other.m_top)
		{
			return false;
		}
		if (m_bot != other.m_bot)
		{
			return false;
		}
		return true;
	}
};

class IntersectionFind
{
public:
	IntersectionFind()
	{
	}

	Rectangle getInter(const Rectangle& rec1, const Rectangle& rec2)
	{
		// future option: flip incorrect variable assignments e.g. if m_rt < m_lt swap(m_rt,m_lt)
		if (isIllegal(rec1) || isIllegal(rec2))
		{
			return Rectangle(0,0,0,0);			
		}
		int lt; 
		int rt; 
		int top;
		int bot; 
		if ((rec1.m_lt >= rec2.m_lt) && (rec1.m_lt < rec2.m_rt))
		{
			lt = rec1.m_lt;
		}
		else if ((rec2.m_lt >= rec1.m_lt) && (rec2.m_lt < rec1.m_rt))
		{
			lt = rec2.m_lt;
		}
		else if (rec1.m_lt == rec2.m_lt) // catches 0 width overlap case
		{
			lt = rec1.m_lt;
		}
		else
		{
			return Rectangle(0,0,0,0); // out of bounds			
		}

		if ((rec1.m_rt >= rec2.m_lt) && (rec1.m_rt < rec2.m_rt))
		{
			rt = rec1.m_rt;
		}
		else if ((rec2.m_rt >= rec1.m_lt) && (rec2.m_rt < rec1.m_rt))
		{
			rt = rec2.m_rt;
		}
		else if (rec1.m_rt == rec2.m_rt) // catches 0 width overlap case
		{
			rt = rec1.m_rt;
		}
		else
		{
			return Rectangle(0,0,0,0); // out of bounds			
		}

		if ((rec1.m_top <= rec2.m_top) && (rec1.m_top > rec2.m_bot))
		{
			top = rec1.m_top;
		}
		else if ((rec2.m_top <= rec1.m_top) && (rec2.m_top > rec1.m_bot))
		{
			top = rec2.m_top;
		}
		else if (rec1.m_top == rec2.m_top) // catches 0 height overlap case
		{
			top = rec1.m_top;
		}
		else
		{
			return Rectangle(0,0,0,0); // out of bounds			
		}

		if ((rec1.m_bot >= rec2.m_bot) && (rec1.m_bot < rec2.m_top))
		{
			bot = rec1.m_bot;
		}
		else if ((rec2.m_bot >= rec1.m_bot) && (rec2.m_bot < rec1.m_top))
		{
			bot = rec2.m_bot;
		}
		else if (rec1.m_bot == rec2.m_bot) // catches 0 height overlap case
		{
			bot = rec1.m_bot;
		}
		else
		{
			return Rectangle(0,0,0,0); // out of bounds			
		}

		return Rectangle(lt, rt, top, bot);
	}
private:
	// illegal: rt < lt or negative coords
	bool isIllegal(const Rectangle& rec)
	{
		if (rec.m_lt < 0)
		{
			return true;
		}
		if (rec.m_rt < 0)
		{
			return true;
		}
		if (rec.m_top < 0)
		{
			return true;
		}
		if (rec.m_bot < 0)
		{
			return true;
		}

		if (rec.m_lt > rec.m_rt)
		{
			return true;
		}
		if (rec.m_top < rec.m_bot)
		{
			return true;
		}
		return false;
	}
};

std::ostream& operator<< (std::ostream& os, Rectangle& rec) 
{
    os << "Lt: " << rec.m_lt << " Rt: " << rec.m_rt << " Top: " << rec.m_top << " Bot: " << rec.m_bot << std::endl;
    return os;
}

#endif