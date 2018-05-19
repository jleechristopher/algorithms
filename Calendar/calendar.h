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
    bool addEvent(const int personId,const int eventId,const int64_t start_time,const int64_t end_time)
    {
        if (contains(personId, eventId))
        {
            return false;
        }
        if (end_time <= start_time)
        {
            return false;
        }
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

    bool findMeetingSlot(const int64_t duration, const int64_t between_start, const int64_t between_end, 
        const std::vector<Event>& person1, const std::vector<Event>& person2)
    {
        if ((between_end - between_start) < duration)
        {
            return false;
        }
        if (person1.empty() && person2.empty())
        {
            return true;
        }
        std::vector<Timepoint> filteredPts;
        filterEvents(filteredPts, person1, duration, between_start, between_end);
        filterEvents(filteredPts, person2, duration, between_start, between_end);
        std::sort(filteredPts.begin(),filteredPts.end(), less);
        int concurrent = 0;
        for (int ii = 0; ii < filteredPts.size(); ++ii)
        {
            if (filteredPts[ii].m_endpointSide == LEFT)
            {
                ++concurrent;
            }
            else // = RIGHT
            {
                --concurrent;
            }
            if (concurrent == 0)
            {
                if (ii + 1 == filteredPts.size()) // final endpoint
                {
                    if ((between_end - filteredPts[ii].m_time) >= duration)
                    {
                        return true;
                    }
                }
                else
                {
                    // the next endpoint is guaranteed to be a LEFT if we are in a blank interval
                    if (filteredPts[ii+1].m_time - filteredPts[ii].m_time >= duration)
                    {
                        return true; // TODO return an event with precise timing
                    }                    
                }
            }
        }

        return false;
    }

    std::vector<Event>& getCalendar()
    {
        return m_events;
    }

private:
    std::vector<Event> m_events;

    bool contains(const int64_t personId, const int64_t eventId)
    {
        for (auto& it : m_events)
        {
            if ((it.m_personId == personId) && (it.m_eventId == eventId))
            {
                return true;
            }
        }
        return false;
    }

    bool filterEvents(std::vector<Timepoint>& filteredPts, const std::vector<Event>& person, 
        const int64_t duration, const int64_t between_start, const int64_t between_end)
    {
        for (auto& it : person)
        {
            if (it.m_start_time > between_end)
            {
                continue;
            }
            // new events can start at the same time others end, so if end_time == between_start we can ignore it
            else if (it.m_end_time <= between_start) 
            {
                continue;
            }
            else
            {
                if (it.m_start_time <= between_start)
                {
                    if (it.m_end_time <= between_end)
                    {
                        filteredPts.push_back(Timepoint(between_start, LEFT)); // make cutoff at between_start
                        filteredPts.push_back(Timepoint(it.m_end_time, RIGHT));                        
                    }
                    else // event ends after between_start
                    {
                        return false; // event spans the entire desired time interval
                    }
                }
                else // event starts after between_start
                {
                    if (it.m_end_time <= between_end)
                    {
                        filteredPts.push_back(Timepoint(it.m_start_time, LEFT));
                        filteredPts.push_back(Timepoint(it.m_end_time, RIGHT));                                                
                    }
                    else // event ends after between_end
                    {
                        filteredPts.push_back(Timepoint(it.m_start_time, LEFT));
                        filteredPts.push_back(Timepoint(between_end, RIGHT)); // make cutoff at between_end                                                                      
                    }
                }
            }
        }
        return true;
    }

    static bool less(const Timepoint& objA, const Timepoint& objB)
    {
        if (objA.m_time < objB.m_time)
        {
            return true;
        }
        else if (objA.m_time == objB.m_time)
        {
            if (objA.m_endpointSide != objB.m_endpointSide)
            {
                if (objA.m_endpointSide == LEFT)
                {
                    return true; // prioritize LEFT endpoints to appear earlier than RIGHT endpoints
                }
                return false;
            }
        }
        return false;
    }
};

#endif