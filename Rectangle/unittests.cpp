#include "unittests.h"
#include "rectangle.h"

Test_Registrar<RectangleUnitTests> RectangleUnitTests::registrar;

bool RectangleUnitTests::nextToLt()
{
	auto rec1 = Rectangle(11, 15, 15, 11); // left, right, top, bottom coords
	auto rec2 = Rectangle(5, 11, 15, 11);
	auto empty = Rectangle(0, 0, 0, 0);

	IntersectionFind finder;
	VERIFY_EQ(finder.getInter(rec1, rec2), empty);
	VERIFY_EQ(finder.getInter(rec2, rec1), empty);

	return true; 
}
bool RectangleUnitTests::nextToTop()
{
	auto rec1 = Rectangle(11, 15, 15, 11); // left, right, top, bottom coords
	auto rec2 = Rectangle(11, 15, 20, 15);
	auto empty = Rectangle(0, 0, 0, 0);

	IntersectionFind finder;
	VERIFY_EQ(finder.getInter(rec1, rec2), empty);
	VERIFY_EQ(finder.getInter(rec2, rec1), empty);

	return true; 
}

bool RectangleUnitTests::cornerOverlap()
{
	auto rec1 = Rectangle(11, 15, 15, 11); // left, right, top, bottom coords
	auto rec2 = Rectangle(13, 18, 20, 13);
	auto solution = Rectangle(13, 15, 15, 13);

	IntersectionFind finder;
	VERIFY_EQ(finder.getInter(rec1, rec2), solution);
	VERIFY_EQ(finder.getInter(rec2, rec1), solution);

	return true; 	
}

bool RectangleUnitTests::overlapLt()
{
	auto rec1 = Rectangle(11, 15, 15, 11); // left, right, top, bottom coords
	auto rec2 = Rectangle(5, 12, 18, 9);
	auto solution = Rectangle(11, 12, 15, 11);

	IntersectionFind finder;
	VERIFY_EQ(finder.getInter(rec1, rec2), solution);
	VERIFY_EQ(finder.getInter(rec2, rec1), solution);

	return true;	
}

bool RectangleUnitTests::overlapTop()
{
	auto rec1 = Rectangle(11, 15, 15, 11); // left, right, top, bottom coords
	auto rec2 = Rectangle(12, 14, 20, 13);
	auto solution = Rectangle(12, 14, 15, 13);

	IntersectionFind finder;
	VERIFY_EQ(finder.getInter(rec1, rec2), solution);
	VERIFY_EQ(finder.getInter(rec2, rec1), solution);

	return true;	
}

bool RectangleUnitTests::smallInsideBig()
{
	auto rec1 = Rectangle(11, 15, 15, 11); // left, right, top, bottom coords
	auto rec2 = Rectangle(12, 14, 14, 12);
	auto solution = Rectangle(12, 14, 14, 12);

	IntersectionFind finder;
	VERIFY_EQ(finder.getInter(rec1, rec2), solution);
	VERIFY_EQ(finder.getInter(rec2, rec1), solution);

	return true;	
}

bool RectangleUnitTests::widthOverlap()
{
	auto rec1 = Rectangle(11, 15, 15, 11); // left, right, top, bottom coords
	auto rec2 = Rectangle(11, 15, 20, 13);
	auto solution = Rectangle(11, 15, 15, 13);

	IntersectionFind finder;
	VERIFY_EQ(finder.getInter(rec1, rec2), solution);
	VERIFY_EQ(finder.getInter(rec2, rec1), solution);

	return true;	
}

bool RectangleUnitTests::heightOverlap()
{
	auto rec1 = Rectangle(11, 15, 15, 11); // left, right, top, bottom coords
	auto rec2 = Rectangle(12, 16, 15, 11);
	auto solution = Rectangle(12, 15, 15, 11);

	IntersectionFind finder;
	VERIFY_EQ(finder.getInter(rec1, rec2), solution);
	VERIFY_EQ(finder.getInter(rec2, rec1), solution);

	return true;	
}

bool RectangleUnitTests::zeroWidthOverlap()
{
	auto rec1 = Rectangle(0, 0, 15, 11); // left, right, top, bottom coords
	auto rec2 = Rectangle(0, 0, 20, 10);
	auto solution = Rectangle(0, 0, 15, 11);

	IntersectionFind finder;
	VERIFY_EQ(finder.getInter(rec1, rec2), solution);
	VERIFY_EQ(finder.getInter(rec2, rec1), solution);

	return true;	
}
bool RectangleUnitTests::zeroHeightOverlap()
{
	auto rec1 = Rectangle(5, 10, 0, 0); // left, right, top, bottom coords
	auto rec2 = Rectangle(4, 12, 0, 0);
	auto solution = Rectangle(5, 10, 0, 0);

	IntersectionFind finder;
	VERIFY_EQ(finder.getInter(rec1, rec2), solution);
	VERIFY_EQ(finder.getInter(rec2, rec1), solution);

	return true;	
}

bool RectangleUnitTests::totalOverlap()
{
	auto rec1 = Rectangle(11, 15, 15, 11); // left, right, top, bottom coords
	auto rec2 = Rectangle(11, 15, 15, 11);
	auto solution = Rectangle(11, 15, 15, 11);

	IntersectionFind finder;
	VERIFY_EQ(finder.getInter(rec1, rec2), solution);
	VERIFY_EQ(finder.getInter(rec2, rec1), solution);

	return true;	
}