#include "unittests.h"
#include "limitedMap.h"

Test_Registrar<LimitedMapTests> LimitedMapTests::registrar;

// basic functions 
bool LimitedMapTests::singleElementTest() 
{
	LimitedMap<int, int> map(1);
	VERIFY_TRUE(map.set(1, 2));
	VERIFY_EQ(map.get(1), 2);
	VERIFY_TRUE(map.set(1, 3));
	VERIFY_NOT_EQ(map.get(1), 2);
	VERIFY_EQ(map.get(1), 3);
	VERIFY_TRUE(map.remove(1));
	VERIFY_FALSE(map.remove(1));

	return true;
}

// verify O(1) for large datasets
bool LimitedMapTests::thousandElementTest() 
{
	int numElements = 1000;
	LimitedMap<int, int> map(numElements);
	Timer t;
	int insertCount = 0;
	int getCount = 0;
	int removeCount = 0;
	int holder;
	double insertBaseline = 0.0;
	double getBaseline = 0.0;
	double removeBaseline = 0.0;

	for (int i = 0; i < 10; ++i) 
	{
		t.reset();
		map.set(i, i);
		insertBaseline += t.elapsed();
	}
	insertBaseline = insertBaseline / 10;

	for (int i = 0; i < 10; ++i) 
	{
		t.reset();
		holder = map.get(i);
		getBaseline += t.elapsed();
	}
	getBaseline = getBaseline / 10;

	for (int i = 0; i < 10; ++i) 
	{
		t.reset();
		map.remove(i);
		removeBaseline += t.elapsed();
	}
	removeBaseline = removeBaseline / 10;

	for (int i = 0; i < numElements; ++i) 
	{
		t.reset();
		map.set(i, i);
		if (t.elapsed() < insertBaseline * 2) // multiply by 2 to allow for some variance
		{
			++insertCount;
		}
	}
	insertBaseline = insertBaseline / 10;

	for (int i = 0; i < numElements; ++i) 
	{
		t.reset();
		holder = map.get(i);
		if (t.elapsed() < getBaseline * 2) // multiply by 2 to allow for some variance
		{
			++getCount;
		}
	}

	for (int i = 0; i < numElements; ++i) 
	{
		t.reset();
		map.remove(i);
		if (t.elapsed() < removeBaseline * 2) // multiply by 2 to allow for some variance
		{
			++removeCount;
		}
	}

	VERIFY_EQ(insertCount, numElements);
	VERIFY_EQ(removeCount, numElements);
	VERIFY_EQ(getCount, numElements);

	return true;
}

bool LimitedMapTests::replaceTest() 
{
	LimitedMap<int, int> map(3);
	VERIFY_TRUE(map.set(1, 2));
	VERIFY_TRUE(map.set(2, 3));
	VERIFY_TRUE(map.set(3, 4));
	VERIFY_TRUE(map.set(4, 5));
	VERIFY_TRUE(map.set(5, 6));
	VERIFY_TRUE(map.set(6, 7));
	VERIFY_EQ(map.get(4), 5);
	VERIFY_EQ(map.get(5), 6);
	VERIFY_EQ(map.get(6), 7);
	VERIFY_FALSE(map.remove(1));
	VERIFY_FALSE(map.remove(2));
	VERIFY_FALSE(map.remove(3));

	return true;
}

bool LimitedMapTests::removeTest() 
{
	LimitedMap<int, int> map(3);
	VERIFY_TRUE(map.set(1, 2));
	VERIFY_TRUE(map.set(2, 3));
	VERIFY_TRUE(map.set(3, 4));
	VERIFY_TRUE(map.remove(2));
	VERIFY_TRUE(map.set(4, 5));
	VERIFY_TRUE(map.set(5, 6));
	VERIFY_FALSE(map.remove(1));
	VERIFY_FALSE(map.remove(2));
	VERIFY_TRUE(map.remove(3));
	VERIFY_TRUE(map.remove(4));
	VERIFY_TRUE(map.remove(5));

	return true;
}

bool LimitedMapTests::relevanceTest() 
{
	LimitedMap<int, int> map(2);
	VERIFY_TRUE(map.set(1, 2));
	VERIFY_TRUE(map.set(2, 3));
	VERIFY_EQ(map.get(1), 2);
	VERIFY_TRUE(map.set(3, 4));
	VERIFY_EQ(map.get(1), 2);
	VERIFY_FALSE(map.remove(2));
	VERIFY_TRUE(map.remove(1));
	VERIFY_TRUE(map.remove(3));

	return true;
}