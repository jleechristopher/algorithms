#include "unittests.h"
#include "calendar.h"
#include <vector>

Test_Registrar<CalendarTests> CalendarTests::registrar;

bool CalendarTests::illegalEventsTest()
{
	Calendar c;
	VERIFY_TRUE(c.addEvent(1, 1, 1, 2));
	VERIFY_FALSE(c.addEvent(1, 1, 1, 2));
	VERIFY_TRUE(c.addEvent(1, 3, 1, 2));
	VERIFY_FALSE(c.addEvent(1, 5, 3, 2));
	return true;
}

bool CalendarTests::singleCollisionTest()
{
	Calendar c;
	VERIFY_EQ(c.maxCollisions(), 0);
	VERIFY_TRUE(c.addEvent(1, 1, 1, 2));
	VERIFY_EQ(c.maxCollisions(), 0);
	VERIFY_TRUE(c.addEvent(1, 2, 1, 2));
	VERIFY_EQ(c.maxCollisions(), 1);	
	return true;
}

bool CalendarTests::nonoverlappingTest()
{
	Calendar c;
	VERIFY_TRUE(c.addEvent(1, 1, 1, 2));
	VERIFY_TRUE(c.addEvent(1, 2, 3, 4));
	VERIFY_EQ(c.maxCollisions(), 0);
	return true;
}

bool CalendarTests::sequentialEventsTest()
{
	Calendar c;
	VERIFY_TRUE(c.addEvent(1, 1, 1, 5));
	VERIFY_TRUE(c.addEvent(1, 2, 2, 5));	
	VERIFY_TRUE(c.addEvent(1, 3, 3, 5));
	VERIFY_TRUE(c.addEvent(1, 4, 4, 6));
	VERIFY_TRUE(c.addEvent(1, 5, 6, 7));
	VERIFY_EQ(c.maxCollisions(), 3);
	return true;
}

bool CalendarTests::openCalendarTest()
{
	Calendar c;
	Calendar d;
	std::vector<int64_t> solution;
	solution.push_back(1);
	solution.push_back(6);
	VERIFY_TRUE(c.findMeetingSlot(5, 1, 10, c.getCalendar(), d.getCalendar()) == solution);
	return true;
}

bool CalendarTests::impossibleIntervalTest()
{
	Calendar c;
	Calendar d;
	std::vector<int64_t> solution; 
	solution.push_back(0);
	solution.push_back(0);
	VERIFY_TRUE(c.findMeetingSlot(5, 1, 5, c.getCalendar(), d.getCalendar()) == solution);
	return true;
}

bool CalendarTests::singleOpenIntervalTest()
{
	Calendar bob;
	VERIFY_TRUE(bob.addEvent(1, 1, 1, 5));
	Calendar adam;
	VERIFY_TRUE(adam.addEvent(2, 2, 10, 15));
	std::vector<int64_t> solution; 
	solution.push_back(5);
	solution.push_back(10);
	VERIFY_TRUE(bob.findMeetingSlot(5, 1, 20, bob.getCalendar(), adam.getCalendar()) == solution);
	return true;
}

bool CalendarTests::overlappingStartTest()
{
	Calendar bob;
	VERIFY_TRUE(bob.addEvent(1, 1, 1, 5));
	Calendar adam;
	VERIFY_TRUE(adam.addEvent(2, 2, 3, 7));
	std::vector<int64_t> solution; 
	solution.push_back(7);
	solution.push_back(12);
	VERIFY_TRUE(bob.findMeetingSlot(5, 2, 20, bob.getCalendar(), adam.getCalendar()) == solution);
	return true;
}

// a small interval midway that isn't long enough for the requested meeting
bool CalendarTests::falseInterval()
{
	Calendar bob;
	VERIFY_TRUE(bob.addEvent(1, 1, 1, 5));
	Calendar adam;
	VERIFY_TRUE(adam.addEvent(2, 2, 7, 14));
	std::vector<int64_t> solution; 
	solution.push_back(14);
	solution.push_back(19);
	VERIFY_TRUE(bob.findMeetingSlot(5, 1, 20, bob.getCalendar(), adam.getCalendar()) == solution);
	return true;
}

bool CalendarTests::openBeginning()
{
	Calendar bob;
	Calendar adam;
	VERIFY_TRUE(adam.addEvent(2, 2, 6, 14));
	std::vector<int64_t> solution; 
	solution.push_back(1);
	solution.push_back(6);
	VERIFY_TRUE(bob.findMeetingSlot(5, 1, 20, bob.getCalendar(), adam.getCalendar()) == solution);
	return true;
}

// two empty calendars and one with events
bool CalendarTests::twoEmpty()
{
	std::vector<std::vector<Calendar::Event>* > people;
	Calendar bob;
	Calendar adam;
	Calendar tim;
	VERIFY_TRUE(tim.addEvent(1, 1, 1, 5));
	people.push_back(bob.getCalendarPtr());
	people.push_back(adam.getCalendarPtr());	
	people.push_back(tim.getCalendarPtr());		
	std::vector<int64_t> solution; 
	solution.push_back(5);
	solution.push_back(10);
	VERIFY_TRUE(bob.findMeetingSlot(5, 1, 20, people) == solution);
	return true;
}

bool CalendarTests::allEmpty()
{
	std::vector<std::vector<Calendar::Event>* > people;
	Calendar bob;
	Calendar adam;
	Calendar tim;
	people.push_back(bob.getCalendarPtr());
	people.push_back(adam.getCalendarPtr());	
	people.push_back(tim.getCalendarPtr());		
	std::vector<int64_t> solution; 
	solution.push_back(1);
	solution.push_back(6);
	VERIFY_TRUE(bob.findMeetingSlot(5, 1, 20, people) == solution);
	return true;
}

bool CalendarTests::multipleCalendars()
{
	std::vector<std::vector<Calendar::Event>* > people;
	Calendar bob;
	VERIFY_TRUE(bob.addEvent(3, 3, 13, 25));
	Calendar adam;
	VERIFY_TRUE(adam.addEvent(2, 2, 3, 9));
	Calendar tim;
	VERIFY_TRUE(tim.addEvent(1, 1, 1, 5));
	people.push_back(bob.getCalendarPtr());
	people.push_back(adam.getCalendarPtr());	
	people.push_back(tim.getCalendarPtr());		
	std::vector<int64_t> solution; 
	solution.push_back(25);
	solution.push_back(30);
	VERIFY_TRUE(bob.findMeetingSlot(5, 1, 50, people) == solution);
	return true;
}
