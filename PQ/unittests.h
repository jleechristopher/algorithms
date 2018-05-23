#ifndef __MY_PQ_TESTS__
#define __MY_PQ_TESTS__

#include "test_helpers.h"

class PQUnitTests final : public UnitTests
{
protected:
    void RunTests() final
    {
        ADD_TEST(PQUnitTests::singleElement);
        ADD_TEST(PQUnitTests::ordering);
    }

private:
    static bool singleElement();
    static bool ordering();

    static Test_Registrar<PQUnitTests> registrar;
};

#endif