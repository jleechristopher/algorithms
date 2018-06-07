#ifndef __ROBOCLEANER_TESTS__
#define __ROBOCLEANER_TESTS__

#include "test_helpers.h"

class RoboCleanerUnitTests final : public UnitTests
{
protected:
    void RunTests() final
    {
        ADD_TEST(RoboCleanerUnitTests::square);
        ADD_TEST(RoboCleanerUnitTests::hallway);
        ADD_TEST(RoboCleanerUnitTests::diamond);
    }

private:
    static bool square();
    static bool hallway();
    static bool diamond();

    static Test_Registrar<RoboCleanerUnitTests> registrar;
};

#endif