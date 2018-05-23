// PRIORITY QUEUE
// An implementation of a priority queue as a binary heap. The heap is implemented as a 1-indexed
// vector to support easy traversal. The program is max-ordered, so front() returns the maximum 
// value contained in the heap. This implementation guarantees a balanced heap by restricting 
// insert/remove operations to the end of the vector. If we wish to remove a value not at the end,
// it's swapped to the end index before removal.
// 
// Author: Chris Lee
// Date: May 23rd, 2018
// Last Edited: May 23rd, 2018

#ifndef _MY_PRIORITY_QUEUE_
#define _MY_PRIORITY_QUEUE_

#include <stdexcept> 
#include <vector>

#define FRONT 1

template<typename T>
class PQ
{
public:
	PQ()
	{
		m_data.resize(1); // m_data[0] is not used so we can support 1-indexing 
	}

	bool empty() const
	{
		if (m_data.size() == 1)
		{
			return true; 
		}
		return false; 
	}

	const T& front() const
	{
		if (empty())
		{
			throw std::invalid_argument( "Cannot return front of empty PQ" );
		}
		return m_data[1];
	}

	bool insert(const T& val)
	{
		m_data.push_back(val);
		rise(m_data.size() - 1);
		return true;
	}

	bool pop()
	{
		if (empty())
		{
			return false;
		}
		swap(FRONT, m_data.size() - 1);
		m_data.pop_back();
		sink(FRONT);
		return true; 
	}

private:
	std::vector<T> m_data;

	void sink(int pos)
	{
		int last = m_data.size() - 1;
		int nextL = pos * 2;
		int nextR = pos * 2 + 1;
		while ((nextL <= last) && (nextR <= last))
		{
			if (m_data[nextL] > m_data[nextR])
			{
				if (m_data[nextL] > m_data[pos])
				{
					swap(pos, nextL);
					pos = pos * 2;
					nextL = pos * 2;
					nextR = pos * 2 + 1;					
				}
				else
				{
					break;
				}
			}
			else
			{
				if (m_data[nextR] > m_data[pos])
				{
					swap(pos, nextR);
					pos = pos * 2 + 1;
					nextL = pos * 2;
					nextR = pos * 2 + 1;				
				}
				else
				{
					break;
				}
			}
		}
		if (nextL == last)
		{
			if (m_data[nextL] > m_data[pos])
			{
				swap(pos, nextL);
			}
		}
	}

	void rise(int pos)
	{
		while (pos > 1)
		{
			if (m_data[pos] > m_data[pos/2])
			{
				swap(pos, pos/2);
				pos = pos/2;
			}
			else
			{
				break;
			}
		}
	}

	void swap(int posA, int posB)
	{
		T temp = m_data[posA];
		m_data[posA] = m_data[posB];
		m_data[posB] = temp; 
	}
};

#endif