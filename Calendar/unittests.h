#ifndef __MY_CALENDAR_TESTS__
#define __MY_CALENDAR_TESTS__

#include <test_helpers.h>

class CalendarTests final : public UnitTests
{
protected:
    void RunTests() final
    {
        ADD_TEST(CalendarTests::illegalEventsTest);
        ADD_TEST(CalendarTests::singleCollisionTest);
        ADD_TEST(CalendarTests::nonoverlappingTest);
        ADD_TEST(CalendarTests::sequentialEventsTest);
        ADD_TEST(CalendarTests::openCalendarTest);
        ADD_TEST(CalendarTests::impossibleIntervalTest);
        ADD_TEST(CalendarTests::singleOpenIntervalTest);
        ADD_TEST(CalendarTests::overlappingStartTest);
        ADD_TEST(CalendarTests::falseInterval);
        ADD_TEST(CalendarTests::openBeginning);
        ADD_TEST(CalendarTests::twoEmpty);
        ADD_TEST(CalendarTests::allEmpty);
        ADD_TEST(CalendarTests::multipleCalendars);
        ADD_TEST(CalendarTests::startEndOverlap);
    }

private:
    static bool illegalEventsTest();
	static bool singleCollisionTest();
    static bool nonoverlappingTest();
    static bool sequentialEventsTest();
    static bool openCalendarTest();
    static bool impossibleIntervalTest();
    static bool singleOpenIntervalTest();
    static bool overlappingStartTest();
    static bool falseInterval();
    static bool openBeginning();
    static bool twoEmpty();
    static bool allEmpty();
    static bool multipleCalendars();
    static bool startEndOverlap();

    static Test_Registrar<CalendarTests> registrar;
};

#endif