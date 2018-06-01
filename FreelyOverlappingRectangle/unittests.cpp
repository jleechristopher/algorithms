#include "unittests.h"
#include "rectangle.h"
#include "IntersectionFind.h"
#include <vector>
#include <math.h> // isinf()
#include <sstream> // print test 

Test_Registrar<FO_RectangleUnitTests> FO_RectangleUnitTests::registrar;
int Polygon::s_idGenerator = 1;

bool FO_RectangleUnitTests::slopeTest()
{
	Vertex v1(10.0, 10.0);
	Vertex v2(10.0, 20.0);

	Vertex v3(10.0, 30.0);
	Vertex v4(20.0, 40.0);

	Vertex v5(10.0, 10.0);
	Vertex v6(13.0, 15.0);

	Line l1(v1, v2);
	Line l2(v3, v4);
	Line l3(v5, v6);
	Line l4(v4, v3);

	VERIFY_TRUE(std::isinf(l1.m_slope));
	VERIFY_EQ(l2.m_slope, 1.0);
	VERIFY_EQ(l2.m_intercept, 20.0);
	VERIFY_EQ(l3.m_slope, 5.0/3.0);

	return true; 
}

bool FO_RectangleUnitTests::ccwSortTest()
{
	Vertex v1(10.0, 10.0);
	Vertex v2(10.0, 20.0);
	Vertex v3(20.0, 10.0);
	Vertex v4(20.0, 20.0);

	Vertex v5(20.0, 20.0);
	Vertex v6(20.0, 30.0);
	Vertex v7(15.0, 25.0);
	Vertex v8(25.0, 25.0);

	Vertex v9(30.0, 30.0);
	Vertex v10(25.0, 25.0);
	Vertex v11(28.0, 20.0);
	Vertex v12(35.0, 20.0);

	std::vector<Vertex> vec1;
	vec1.push_back(v1);
	vec1.push_back(v2);
	vec1.push_back(v3);
	vec1.push_back(v4);

	std::vector<Vertex> vec2;
	vec2.push_back(v5);
	vec2.push_back(v6);
	vec2.push_back(v7);
	vec2.push_back(v8);

	std::vector<Vertex> vec3;
	vec3.push_back(v9);
	vec3.push_back(v10);
	vec3.push_back(v11);
	vec3.push_back(v12);

	Polygon p1(vec1);
	Polygon p2(vec2);
	Polygon p3(vec3);

	std::stringstream solution1;
	std::stringstream solution2;
	std::stringstream solution3;

	solution1 << "Rank: 0 x: 10 y: 10" << std::endl;
	solution1 << "Rank: 1 x: 10 y: 20" << std::endl;
	solution1 << "Rank: 2 x: 20 y: 20" << std::endl;
	solution1 << "Rank: 3 x: 20 y: 10" << std::endl;

	solution2 << "Rank: 0 x: 15 y: 25" << std::endl;
	solution2 << "Rank: 1 x: 20 y: 30" << std::endl;
	solution2 << "Rank: 2 x: 25 y: 25" << std::endl;
	solution2 << "Rank: 3 x: 20 y: 20" << std::endl;

	solution3 << "Rank: 0 x: 25 y: 25" << std:: endl;
	solution3 << "Rank: 1 x: 30 y: 30" << std:: endl;
	solution3 << "Rank: 2 x: 35 y: 20" << std:: endl;
	solution3 << "Rank: 3 x: 28 y: 20" << std:: endl;

	std::stringstream output1;
	std::stringstream output2;
	std::stringstream output3;

	p1.printPts(output1);
	p2.printPts(output2);
	p3.printPts(output3);

	VERIFY_EQ(output1.str(), solution1.str());
	VERIFY_EQ(output2.str(), solution2.str());
	VERIFY_EQ(output3.str(), solution3.str());

	return true;
}

bool FO_RectangleUnitTests::samePoly()
{
	Vertex v1(10.0, 10.0);
	Vertex v2(10.0, 20.0);
	Vertex v3(5.0, 10.0);
	Vertex v4(15.0, 20.0);

	Line l1(v1, v2, 0, 1);
	Line l2(v3, v4, 0, 1);

	Vertex solution(10.0, 15.0);
	Vertex output;

	IntersectionFind finder;
	VERIFY_FALSE(finder.getLineIntersection(l1, l2, output));
	return true;
}

bool FO_RectangleUnitTests::linesEqual()
{
	Vertex v1(10.0, 10.0);
	Vertex v2(10.0, 20.0);
	Vertex v3(10.0, 10.0);
	Vertex v4(10.0, 20.0);

	Line l1(v1, v2, 0, 0);
	Line l2(v3, v4, 0, 1);

	Vertex solution(10.0, 15.0);
	Vertex output;

	IntersectionFind finder;
	VERIFY_FALSE(finder.getLineIntersection(l1, l2, output));
	return true;
}

bool FO_RectangleUnitTests::endpointIntersect()
{
	Vertex v1(10.0, 10.0);
	Vertex v2(10.0, 20.0);
	Vertex v3(0.0, 10.0);
	Vertex v4(10.0, 20.0);

	Line l1(v1, v2, 0, 1);
	Line l2(v3, v4, 0, 0);

	Vertex solution(10.0, 20.0);
	Vertex output;

	IntersectionFind finder;
	VERIFY_TRUE(finder.getLineIntersection(l1, l2, output));
	VERIFY_EQ(output, solution);
	return true;
}

bool FO_RectangleUnitTests::middleIntersect()
{
	Vertex v1(10.0, 10.0);
	Vertex v2(10.0, 20.0);
	Vertex v3(5.0, 10.0);
	Vertex v4(15.0, 20.0);

	Line l1(v1, v2, 0, 1);
	Line l2(v3, v4, 0, 0);

	Vertex solution(10.0, 15.0);
	Vertex output;

	IntersectionFind finder;
	VERIFY_TRUE(finder.getLineIntersection(l1, l2, output));
	VERIFY_EQ(output, solution);

	return true;
}

bool FO_RectangleUnitTests::outOfBounds()
{
	Vertex v1(10.0, 10.0);
	Vertex v2(10.0, 20.0);
	Vertex v3(5.0, 20.0);
	Vertex v4(15.0, 30.0);

	Line l1(v1, v2, 0, 1);
	Line l2(v3, v4, 0, 0);

	Vertex output;

	IntersectionFind finder;
	VERIFY_FALSE(finder.getLineIntersection(l1, l2, output));

	return true;
}

bool FO_RectangleUnitTests::rectangleOrNot() 
{
	Vertex v1(10.0, 10.0);
	Vertex v2(10.0, 20.0);
	Vertex v3(20.0, 10.0);
	Vertex v4(20.0, 20.0);

	Vertex v5(9.0, 15.0);
	Vertex v6(21.0, 15.0);
	Vertex v7(15.0, 21.0);
	Vertex v8(15.0, 9.0);

	Vertex v9(10.0, 10.0);
	Vertex v10(10.0, 21.0);
	Vertex v11(20.0, 10.0);
	Vertex v12(20.0, 20.0);

	std::vector<Vertex> vec1;
	vec1.push_back(v1);
	vec1.push_back(v2);
	vec1.push_back(v3);
	vec1.push_back(v4);

	std::vector<Vertex> vec2;
	vec2.push_back(v5);
	vec2.push_back(v6);
	vec2.push_back(v7);
	vec2.push_back(v8);

	std::vector<Vertex> vec3;
	vec3.push_back(v9);
	vec3.push_back(v10);
	vec3.push_back(v11);
	vec3.push_back(v12);


	Polygon p1(vec1);
	Polygon p2(vec2);
	Polygon p3(vec3);
	vec3.push_back(v5);
	Polygon p4(vec3);

	IntersectionFind finder;
	VERIFY_TRUE(finder.isValidRectangle(p1));
	VERIFY_TRUE(finder.isValidRectangle(p2));
	VERIFY_FALSE(finder.isValidRectangle(p3));
	VERIFY_FALSE(finder.isValidRectangle(p4));

	return true;
}

bool FO_RectangleUnitTests::singleEdgeOverlap()
{
	Vertex v1(10.0, 10.0);
	Vertex v2(10.0, 20.0);
	Vertex v3(20.0, 10.0);
	Vertex v4(20.0, 20.0);
	Vertex v5(20.0, 10.0);
	Vertex v6(20.0, 20.0);
	Vertex v7(30.0, 10.0);
	Vertex v8(30.0, 20.0);

	std::vector<Vertex> vec1;
	vec1.push_back(v1);
	vec1.push_back(v2);
	vec1.push_back(v3);
	vec1.push_back(v4);

	std::vector<Vertex> vec2;
	vec2.push_back(v5);
	vec2.push_back(v6);
	vec2.push_back(v7);
	vec2.push_back(v8);

	Polygon p1(vec1);
	Polygon p2(vec2);
	Polygon output;
	Polygon solution;

	IntersectionFind finder;
	VERIFY_FALSE(finder.getRectangleOverlap(p1, p2, output));

	return true; 
}

bool FO_RectangleUnitTests::octagonOverlap()
{
	Vertex v1(10.0, 10.0);
	Vertex v2(10.0, 20.0);
	Vertex v3(20.0, 10.0);
	Vertex v4(20.0, 20.0);

	Vertex v5(9.0, 15.0);
	Vertex v6(21.0, 15.0);
	Vertex v7(15.0, 21.0);
	Vertex v8(15.0, 9.0);

	Vertex s1(10.0, 16.0);
	Vertex s2(10.0, 14.0);
	Vertex s3(14.0, 20.0);
	Vertex s4(16.0, 20.0);
	Vertex s5(20.0, 16.0);
	Vertex s6(20.0, 14.0);
	Vertex s7(16.0, 10.0);
	Vertex s8(14.0, 10.0);

	std::vector<Vertex> vec1;
	vec1.push_back(v1);
	vec1.push_back(v2);
	vec1.push_back(v3);
	vec1.push_back(v4);

	std::vector<Vertex> vec2;
	vec2.push_back(v5);
	vec2.push_back(v6);
	vec2.push_back(v7);
	vec2.push_back(v8);

	std::vector<Vertex> vec3;
	vec3.push_back(s1);
	vec3.push_back(s2);
	vec3.push_back(s3);
	vec3.push_back(s4);
	vec3.push_back(s5);
	vec3.push_back(s6);
	vec3.push_back(s7);
	vec3.push_back(s8);

	Polygon p1(vec1);
	Polygon p2(vec2);
	Polygon solution(vec3);
	Polygon output;

	IntersectionFind finder;
	VERIFY_TRUE(finder.getRectangleOverlap(p1, p2, output));
	VERIFY_EQ(solution, output);

	return true;
}
bool FO_RectangleUnitTests::fullOverlap()
{
	Vertex v1(10.0, 10.0);
	Vertex v2(10.0, 20.0);
	Vertex v3(20.0, 10.0);
	Vertex v4(20.0, 20.0);

	std::vector<Vertex> vec1;
	vec1.push_back(v1);
	vec1.push_back(v2);
	vec1.push_back(v3);
	vec1.push_back(v4);

	Polygon p1(vec1);
	Polygon p2(vec1);
	Polygon solution(vec1);
	Polygon output;

	IntersectionFind finder;
	VERIFY_TRUE(finder.getRectangleOverlap(p1, p2, output));
	VERIFY_EQ(solution, output);

	return true;	
}
bool FO_RectangleUnitTests::bigInSmall()
{
	Vertex v1(9.0, 9.0);
	Vertex v2(9.0, 21.0);
	Vertex v3(21.0, 9.0);
	Vertex v4(21.0, 21.0);

	Vertex v5(10.0, 10.0);
	Vertex v6(20.0, 20.0);
	Vertex v7(20.0, 10.0);
	Vertex v8(10.0, 20.0);

	std::vector<Vertex> vec1;
	vec1.push_back(v1);
	vec1.push_back(v2);
	vec1.push_back(v3);
	vec1.push_back(v4);

	std::vector<Vertex> vec2;
	vec2.push_back(v5);
	vec2.push_back(v6);
	vec2.push_back(v7);
	vec2.push_back(v8);

	Polygon p1(vec1);
	Polygon p2(vec2);
	Polygon solution(vec2);
	Polygon output;

	IntersectionFind finder;
	VERIFY_TRUE(finder.getRectangleOverlap(p1, p2, output));
	VERIFY_EQ(solution, output);

	return true;

}
bool FO_RectangleUnitTests::diamondInSquare()
{
	Vertex v1(10.0, 10.0);
	Vertex v2(20.0, 20.0);
	Vertex v3(20.0, 10.0);
	Vertex v4(10.0, 20.0);

	Vertex v5(10.0, 15.0);
	Vertex v6(15.0, 20.0);
	Vertex v7(20.0, 15.0);
	Vertex v8(15.0, 10.0);

	std::vector<Vertex> vec1;
	vec1.push_back(v1);
	vec1.push_back(v2);
	vec1.push_back(v3);
	vec1.push_back(v4);

	std::vector<Vertex> vec2;
	vec2.push_back(v5);
	vec2.push_back(v6);
	vec2.push_back(v7);
	vec2.push_back(v8);

	Polygon p1(vec1);
	Polygon p2(vec2);
	Polygon solution(vec2);
	Polygon output;

	IntersectionFind finder;
	VERIFY_TRUE(finder.getRectangleOverlap(p1, p2, output));
	VERIFY_EQ(solution, output);

	return true;	
}

