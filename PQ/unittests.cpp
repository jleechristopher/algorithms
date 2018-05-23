#include "unittests.h"
#include "pq.h"

Test_Registrar<PQUnitTests> PQUnitTests::registrar;

bool PQUnitTests::singleElement()
{
	PQ<int> pq;
	VERIFY_TRUE(pq.empty());
	VERIFY_TRUE(pq.insert(1));
	VERIFY_FALSE(pq.empty());
	VERIFY_EQ(pq.front(), 1);
	VERIFY_TRUE(pq.pop());
	VERIFY_TRUE(pq.empty());
	return true; 
}

bool PQUnitTests::ordering()
{
	PQ<int> pq;
	VERIFY_TRUE(pq.insert(1));
	VERIFY_TRUE(pq.insert(4));
	VERIFY_EQ(pq.front(), 4);
	VERIFY_TRUE(pq.insert(3));
	VERIFY_EQ(pq.front(), 4);
	VERIFY_TRUE(pq.pop());
	VERIFY_EQ(pq.front(), 3);
	VERIFY_TRUE(pq.insert(5));
	VERIFY_TRUE(pq.insert(6));
	VERIFY_EQ(pq.front(), 6);
	VERIFY_TRUE(pq.pop());
	VERIFY_EQ(pq.front(), 5);
	VERIFY_TRUE(pq.pop());
	VERIFY_EQ(pq.front(), 3);
	VERIFY_TRUE(pq.pop());
	VERIFY_EQ(pq.front(), 1);
	VERIFY_TRUE(pq.pop());
	VERIFY_FALSE(pq.pop());

	return true;
}
