// CALENDAR
// 
// Author: Chris Lee
// Date: May 18th, 2018
// Last edited: May 18th, 2018

#ifndef __MY_CALENDAR__
#define __MY_CALENDAR__

#include <vector>
#include <algorithm>

#define LEFT 0
#define RIGHT 1

class Calendar
{
private:
    struct Timepoint
    {
        Timepoint(int64_t time, bool side): m_time{time}, m_endpointSide{side}
        {
        }
        int64_t m_time;
        bool m_endpointSide; // left or right endpoint
    };

public:
    struct Event
    {
        Event(int personId, int eventId, int64_t start_time, int64_t end_time): 
        m_personId{personId}, 
        m_eventId{eventId},
        m_start_time{start_time},
        m_end_time{end_time}
        {
        }
        int m_personId;
        int m_eventId;
        int64_t m_start_time;
        int64_t m_end_time;
    };

    Calendar()
    {
    }
    // doesn't check for duplicates. could add isExistingEvent() check later
    bool addEvent(const int personId,const int eventId,const int64_t start_time,const int64_t end_time)
    {
        m_events.push_back(Event(personId, eventId, start_time, end_time));
        return true;
    }

    // Max collisions for any given timepoint
    int maxCollisions()
    {
        if (m_events.empty())
        {
            return 0;
        }

        std::vector<Timepoint> times; 
        for (auto& it : m_events)
        {
            times.push_back(Timepoint(it.m_start_time, LEFT));
            times.push_back(Timepoint(it.m_end_time, RIGHT));
        }

        std::sort(times.begin(),times.end(), less);
        int maxConcurrent = 0;
        int concurrent = 0;
        for (auto& it : times)
        {
            if (it.m_endpointSide == LEFT)
            {
                ++concurrent;
            }
            else // = RIGHT
            {
                --concurrent;
            }
            if (concurrent > maxConcurrent)
            {
                maxConcurrent = concurrent;
            }
        }

        return maxConcurrent - 1; // 
    }

    bool findMeetingSlot(int64_t duration, int64_t between_start, int64_t between_end, 
        const std::vector<Event>& person1, const std::vector<Event>& person2)
    {
        if (between_end - between_start < duration)
        {
            return false;
        }

        return false;
    }

    std::vector<Event>& getCalendar()
    {
        return m_events;
    }

private:
    std::vector<Event> m_events;

    static bool less(const Timepoint& objA, const Timepoint& objB)
    {
        if (objA.m_time < objB.m_time)
        {
            return true;
        }
        return false;
    }
};

#endif