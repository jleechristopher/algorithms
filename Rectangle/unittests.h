#ifndef __RECTANGLE_INTERSECTION_TESTS__
#define __RECTANGLE_INTERSECTION_TESTS__

#include "test_helpers.h"

class RectangleUnitTests final : public UnitTests
{
protected:
    void RunTests() final
    {
        ADD_TEST(RectangleUnitTests::nextToLt);
        ADD_TEST(RectangleUnitTests::nextToTop);
        ADD_TEST(RectangleUnitTests::cornerOverlap);
        ADD_TEST(RectangleUnitTests::overlapLt);
        ADD_TEST(RectangleUnitTests::overlapTop);
        ADD_TEST(RectangleUnitTests::smallInsideBig);
        ADD_TEST(RectangleUnitTests::widthOverlap);
        ADD_TEST(RectangleUnitTests::heightOverlap);
        ADD_TEST(RectangleUnitTests::zeroWidthOverlap);
        ADD_TEST(RectangleUnitTests::zeroHeightOverlap);
        ADD_TEST(RectangleUnitTests::totalOverlap);
    }

private:
    static bool nextToLt();
	static bool nextToTop();
	static bool cornerOverlap();
	static bool overlapLt();
	static bool overlapTop();
	static bool smallInsideBig();
	static bool widthOverlap();
	static bool heightOverlap();
	static bool zeroWidthOverlap();
	static bool zeroHeightOverlap();
	static bool totalOverlap();


    static Test_Registrar<RectangleUnitTests> registrar;
};

#endif