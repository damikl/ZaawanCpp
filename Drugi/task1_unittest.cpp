#include <gtest/gtest.h>
#include "task.hpp"
using namespace std;
 
 class TaskTest : public ::testing::Test {
 protected:
  TaskTest() :  title("   Wycieczka            "), title2("Wycieczka"),
						desc("  Wycieczka   w   bieszczady  "), desc2("Wycieczka w bieszczady"),
						priority(" Higth  "), priority2("Higth"),
						severity("   Serious  "), severity2("Serious"),
						t1_(2,title,desc,priority,severity), t2_(3,title2,desc2,priority2,severity2)
						{}
  virtual void SetUp() {
    
  }
  
  virtual void setDateTime()
  {
	  t2_.setDate(22,5,2010);
	  t2_.setTime(14,40,25);
  }

  // virtual void TearDown() {}
  string title;
  string desc;
  string priority;
  string severity;
  string title2;
  string desc2;
  string priority2;
  string severity2;
  
//  Task t0_;
  Task t1_;
  Task t2_;
  
};
 /*
 TEST_F(TaskTest, IsEmptyInitially) {
  EXPECT_TRUE(q0_.getTitle().empty());
  EXPECT_TRUE(q0_.getDescription().empty());
  EXPECT_TRUE(q0_.getPriority().empty());
  EXPECT_TRUE(q0_.getSeverity().empty());
}
*/
TEST_F(TaskTest, initNormalValues) {

  EXPECT_EQ("Wycieczka", t2_.getTitle());
  EXPECT_EQ("Wycieczka w bieszczady", t2_.getDescription());
  EXPECT_EQ("Higth", t2_.getPriority());
  EXPECT_EQ("Serious", t2_.getSeverity());

}

TEST_F(TaskTest, doInitialTrim) {
  

  // EXPECT_EQ() evaluates its arguments exactly once, so they
  // can have side effects.

  EXPECT_EQ(t1_.getTitle(), t2_.getTitle());
  EXPECT_EQ(t1_.getDescription(), t2_.getDescription());
  EXPECT_EQ(t1_.getPriority(), t2_.getPriority());
  EXPECT_EQ(t1_.getSeverity(), t2_.getSeverity());

}

TEST_F(TaskTest, setValidDate) {
  
  ASSERT_FALSE(t1_.setDate(8,0,2000));
  ASSERT_FALSE(t1_.setDate(8,13,2000));
  
  ASSERT_FALSE(t1_.setDate(32,1,2000));
  ASSERT_FALSE(t1_.setDate(0,1,2000));
  
  //Leap Year
  ASSERT_FALSE(t1_.setDate(29,2,2011));
  ASSERT_TRUE(t1_.setDate(29,2,2012));
  
  ASSERT_TRUE(t1_.setDate(1,1,2012));
  ASSERT_TRUE(t1_.setDate(31,3,2012));
  ASSERT_TRUE(t1_.setDate(1,1,2012));
  ASSERT_TRUE(t1_.setDate(31,12,2012));
  
 
}

TEST_F(TaskTest, setValidTime) {
	
  ASSERT_FALSE(t1_.setTime(24,5,3));
  ASSERT_FALSE(t1_.setTime(-1,5,3));
  ASSERT_FALSE(t1_.setTime(22,60,3));
  ASSERT_FALSE(t1_.setTime(22,-1,3));
  ASSERT_FALSE(t1_.setTime(22,4,60));
  ASSERT_FALSE(t1_.setTime(22,4,-1));
  
  ASSERT_TRUE(t1_.setTime(23,59,59));
  ASSERT_TRUE(t1_.setTime(0,0,0));
  ASSERT_TRUE(t1_.setTime(12,30,20));
  ASSERT_TRUE(t1_.setTime(6,40));
  ASSERT_TRUE(t1_.setTime(4));
  
}

TEST_F(TaskTest, getProperTime) {
  setDateTime();
  EXPECT_EQ(t2_.getTime(), "Sat May 22 14:40:25 2010\n");
  
}




