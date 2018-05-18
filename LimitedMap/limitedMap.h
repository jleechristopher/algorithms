// MAP
// This implementation of map guarantees O(1) set, get, remove operations given the maximum number
// of elements. If the number of elements exceeds its maximum, the map replaces the least relevant
// index, as determined by the last time the index was inserted or accessed by get().
//
// Author: Chris Lee
// Date: May 17th, 2018
// Last edited: May 17th, 2018

#ifndef __LIMITED_MAP__
#define __LIMITED_MAP__

#include <iostream>
#include <stdexcept>
#include <map>
#include <memory>

template<typename Key, typename Value>
class LimitedMap
{
private:
    class MapQueue
    {
    private:
        class Node
        {
            Node(const Key& key): m_data(key), m_next(nullptr), m_previous(nullptr)
            {
            }
            Key m_data;
            Node* m_next;
            Node* m_previous;
            friend MapQueue;
            friend LimitedMap;
        };
    public:
        MapQueue(): m_front(nullptr), m_back(nullptr)
        {
        }
        ~MapQueue()
        {
            if (!m_front)
            {
                return;
            }
            else
            {
                Node* toDelete = m_front;
                while (m_front)
                {
                    m_front = m_front->m_next;
                    delete toDelete;
                    toDelete = m_front;
                }
            }
        }

        Key& front()
        {
            if (m_front)
            {
                return m_front->m_data;
            }
            else
            {
                throw std::invalid_argument( "Empty queue" );
            }
        }

        Node* push(const Key& key)
        {
            if (!m_front)
            {
                m_front = new Node(key);
                m_back = m_front;
                return m_front;
            }

            else
            {
                m_back->m_next = new Node(key);
                m_back->m_next->m_previous = m_back;
                m_back = m_back->m_next;
                return m_back;
            }
        }

        bool pop()
        {
            if (!m_front)
            {
                return false;
            }
            if (!m_front->m_next)
            {
                delete m_front;
                m_front = nullptr;
                m_back = nullptr;
            }
            else
            {
                Node* temp = m_front;
                m_front = m_front->m_next;
                m_front->m_previous = nullptr;
                delete temp;
            }

            return true;
        }

        void removeNode(Node* node)
        {
            if (node == m_front)
            {
                pop();
            }
            else if (node == m_back)
            {
                m_back = m_back->m_previous;
                m_back->m_next = nullptr;
                delete node;
            }
            else
            {
                node->m_previous->m_next = node->m_next;
                node->m_next->m_previous = node->m_previous;
                delete node;
            }
        }

    private:
        Node* m_front;
        Node* m_back;
        friend LimitedMap;
    };

    struct MapData
    {
        MapData(const Value& value, typename MapQueue::Node* node): m_value{value}, m_node{node}
        {
        }
        Value m_value;
        typename MapQueue::Node* m_node; 
    };
public:
    LimitedMap(int size): m_maxSize{size}
    {
    }
    bool set(const Key& key, const Value& value)
    {
        if (m_map.size() == m_maxSize) 
        {
            Key& oldest = q.front();
            typename MapQueue::Node* qPtr = m_map[oldest]->m_node;
            m_map.erase(qPtr->m_data);
            q.removeNode(qPtr);
        }
        typename MapQueue::Node* qPtr = q.push(key);
        auto myPtr = std::make_shared<MapData>(value, qPtr);
        m_map[key] = myPtr;
        return true;
    }

    bool remove(const Key& key) 
    {
        if (m_map.find(key) == m_map.end())
        {
            return false;
        }
        typename MapQueue::Node* qPtr = m_map[key]->m_node;
        q.removeNode(qPtr);
        m_map.erase(key);
        return true;
    }

    Value& get(const Key& key)
    {
        typename MapQueue::Node* qPtr = m_map[key]->m_node;
        q.removeNode(qPtr);
        qPtr = q.push(key);
        auto myPtr = m_map[key];
        myPtr->m_node = qPtr;
        return myPtr->m_value;
    }
private:
    std::map<Key, std::shared_ptr<MapData>> m_map;
    MapQueue q;
    int m_maxSize;
};

#endif