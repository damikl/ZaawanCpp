#include <gtest/gtest.h>
#include <algorithm>
#include <stdexcept>
#include "todos.hpp"
using namespace std;

class TodosTest : public ::testing::Test {
 protected:
  TodosTest() :  	t1(1,"a","b","c","d"), 
					t2(2,"q","x","fd","m"),
					t3(3,"a","s","ds","n"),
					t4(4,"z","w","tr","b"),
					t5(5,"p","d","jh","v"),
					t6(6,"l","c","e]ds","c"),
					l0(),l1(),l2(),l3()
						{}
  virtual void SetUp() {
    l1.addTask(t1);
    l2.addTask(t2);
    l2.addTask(t3);
    l3.addTask(t4);
    l3.addTask(t5);
    l3.addTask(t6);
  }

  // virtual void TearDown() {}
  Task t1, t2, t3, t4, t5, t6;
  Todos l0,l1,l2,l3;
  
};

TEST_F(TodosTest,size)
{
	EXPECT_EQ(0,l0.size());
	EXPECT_EQ(1,l1.size());
	EXPECT_EQ(2,l2.size());
	EXPECT_EQ(3,l3.size());
}

TEST_F(TodosTest,iterators)
{
	EXPECT_EQ(0,distance(l0.begin(),l0.end()));
	EXPECT_EQ(1,distance(l1.begin(),l1.end()));
	EXPECT_EQ(2,distance(l2.begin(),l2.end()));
	EXPECT_EQ(3,distance(l3.begin(),l3.end()));
}

TEST_F(TodosTest,nextId)
{
	EXPECT_FALSE(l1.existTask( l1.nextId() ));
	EXPECT_FALSE(l2.existTask( l2.nextId() ));
	EXPECT_FALSE(l3.existTask( l3.nextId() ));
}

TEST_F(TodosTest,nextId_excesive)
{
	for(int i = 0; i < 50; ++i)
	{
		int next = l3.nextId();
		int size = l3.size();
		EXPECT_FALSE( l3.existTask( next ) );
		EXPECT_TRUE( l3.addTask( Task(next,"a" ) ) );
		l3.sort(compareById);
		unique(l3.begin(),l3.end(),equalById);// no change
		
		EXPECT_EQ(size+1,l3.size());
		EXPECT_TRUE(l3.existTask( next ));
	}
}

TEST_F(TodosTest,existTask)
{
	EXPECT_TRUE(l1.existTask(1));
	EXPECT_TRUE(l2.existTask(2));
	EXPECT_TRUE(l2.existTask(3));
	EXPECT_TRUE(l3.existTask(4));
	EXPECT_TRUE(l3.existTask(5));
	EXPECT_TRUE(l3.existTask(6));
	
	EXPECT_FALSE(l1.existTask(0));
	EXPECT_FALSE(l1.existTask(2));
	
	EXPECT_FALSE(l2.existTask(1));
	EXPECT_FALSE(l2.existTask(4));
	EXPECT_FALSE(l2.existTask(6));
	
	EXPECT_FALSE(l3.existTask(3));
	EXPECT_FALSE(l3.existTask(7));
	EXPECT_FALSE(l3.existTask(1));
}

TEST_F(TodosTest,getTask)
{
	EXPECT_EQ(1,l1.getTask(1).getId());
	EXPECT_EQ(2,l2.getTask(2).getId());
	EXPECT_EQ(3,l2.getTask(3).getId());
	EXPECT_EQ(4,l3.getTask(4).getId());
	EXPECT_EQ(5,l3.getTask(5).getId());
	EXPECT_EQ(6,l3.getTask(6).getId());
	
	EXPECT_THROW(l1.getTask(0).getId(),invalid_argument);
	EXPECT_THROW(l1.getTask(2).getId(),invalid_argument);
	
	EXPECT_THROW(l2.getTask(1).getId(),invalid_argument);
	EXPECT_THROW(l2.getTask(4).getId(),invalid_argument);
	EXPECT_THROW(l2.getTask(6).getId(),invalid_argument);
	
	EXPECT_THROW(l3.getTask(3).getId(),invalid_argument);
	EXPECT_THROW(l3.getTask(7).getId(),invalid_argument);
	EXPECT_THROW(l3.getTask(1).getId(),invalid_argument);
}




