#include "unittests.h"
#include "calendar.h"

Test_Registrar<CalendarTests> CalendarTests::registrar;

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
	VERIFY_TRUE(c.findMeetingSlot(5, 1, 10, c.getCalendar(), d.getCalendar()));
	return true;
}

bool CalendarTests::closedCalendarTest()
{
	Calendar c;
	Calendar d;
	VERIFY_FALSE(c.findMeetingSlot(5, 1, 5, c.getCalendar(), d.getCalendar()));
	return true;
}

bool CalendarTests::singleOpenIntervalTest()
{
	Calendar bob;
	VERIFY_TRUE(bob.addEvent(1, 1, 1, 5));
	Calendar adam;
	VERIFY_TRUE(adam.addEvent(2, 2, 10, 15));
	VERIFY_TRUE(bob.findMeetingSlot(5, 1, 20, bob.getCalendar(), adam.getCalendar()));
	return true;
}

bool CalendarTests::overlappingStartTest()
{
	Calendar bob;
	VERIFY_TRUE(bob.addEvent(1, 1, 1, 5));
	Calendar adam;
	VERIFY_TRUE(adam.addEvent(2, 2, 3, 7));
	VERIFY_TRUE(bob.findMeetingSlot(5, 2, 20, bob.getCalendar(), adam.getCalendar()));
	return true;
}

// a small interval midway that isn't long enough for the requested meeting
bool CalendarTests::falseInterval()
{
	Calendar bob;
	VERIFY_TRUE(bob.addEvent(1, 1, 1, 5));
	Calendar adam;
	VERIFY_TRUE(adam.addEvent(2, 2, 7, 14));
	VERIFY_TRUE(bob.findMeetingSlot(5, 1, 20, bob.getCalendar(), adam.getCalendar()));
	return true;
}