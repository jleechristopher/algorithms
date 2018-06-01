#ifndef __FO_RECTANGLE_INTERSECTION_TESTS__
#define __FO_RECTANGLE_INTERSECTION_TESTS__

#include "test_helpers.h"

class FO_RectangleUnitTests final : public UnitTests
{
protected:
    void RunTests() final
    {
        ADD_TEST(FO_RectangleUnitTests::slopeTest);
        ADD_TEST(FO_RectangleUnitTests::ccwSortTest);
        ADD_TEST(FO_RectangleUnitTests::samePoly);
        ADD_TEST(FO_RectangleUnitTests::linesEqual);
        ADD_TEST(FO_RectangleUnitTests::endpointIntersect);
        ADD_TEST(FO_RectangleUnitTests::middleIntersect);
        ADD_TEST(FO_RectangleUnitTests::outOfBounds);
        ADD_TEST(FO_RectangleUnitTests::rectangleOrNot);
        ADD_TEST(FO_RectangleUnitTests::singleEdgeOverlap);
        ADD_TEST(FO_RectangleUnitTests::octagonOverlap);
        ADD_TEST(FO_RectangleUnitTests::fullOverlap);
        ADD_TEST(FO_RectangleUnitTests::bigInSmall);
        ADD_TEST(FO_RectangleUnitTests::diamondInSquare);
    }

private:
    static bool slopeTest();
    static bool ccwSortTest();
    static bool samePoly();
    static bool linesEqual();
    static bool endpointIntersect();
    static bool middleIntersect();
    static bool outOfBounds();
    static bool rectangleOrNot();
    static bool singleEdgeOverlap();
    static bool octagonOverlap();
    static bool fullOverlap();
    static bool bigInSmall();
    static bool diamondInSquare();

    static Test_Registrar<FO_RectangleUnitTests> registrar;
};

#endif