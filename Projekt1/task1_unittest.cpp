#include <gtest/gtest.h>
#include <stdexcept>
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
  
  Task t1_;
  Task t2_;
  
};

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
  
  EXPECT_THROW(t1_.setDate(8,0,2000),invalid_argument);
  EXPECT_THROW(t1_.setDate(8,13,2000),invalid_argument);
  
  EXPECT_THROW(t1_.setDate(32,1,2000),invalid_argument);
  EXPECT_THROW(t1_.setDate(0,1,2000),invalid_argument);
  
  //Leap Year
  EXPECT_THROW(t1_.setDate(29,2,2001),invalid_argument);
  EXPECT_TRUE(t1_.setDate(29,2,2000));
  
  EXPECT_TRUE(t1_.setDate(1,1,2000));
  EXPECT_TRUE(t1_.setDate(31,3,2000));
  EXPECT_TRUE(t1_.setDate(1,1,2000));
  EXPECT_TRUE(t1_.setDate(31,12,2000));
  
 
}

TEST_F(TaskTest, setValidTime) {
	
  ASSERT_THROW(t1_.setTime(24,5,3),invalid_argument);
  ASSERT_THROW(t1_.setTime(-1,5,3),invalid_argument);
  ASSERT_THROW(t1_.setTime(22,60,3),invalid_argument);
  ASSERT_THROW(t1_.setTime(22,-1,3),invalid_argument);
  ASSERT_THROW(t1_.setTime(22,4,60),invalid_argument);
  ASSERT_THROW(t1_.setTime(22,4,-1),invalid_argument);
  
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
TEST_F(TaskTest, timeOrder) {
  
  EXPECT_TRUE(t1_.timeOrder(t2_));
  
}

TEST_F(TaskTest, convert) {
   Task tmp = Task::convert(		t1_.convert());

   EXPECT_EQ(tmp.getId(), 			t1_.getId());
   EXPECT_EQ(tmp.getTitle(),		t1_.getTitle());
   EXPECT_EQ(tmp.getDescription(),	t1_.getDescription());
   EXPECT_EQ(tmp.getTime(),			t1_.getTime());
   EXPECT_EQ(tmp.getPriority(),		t1_.getPriority());
   EXPECT_EQ(tmp.getSeverity(),		t1_.getSeverity());
   
   tmp = Task::convert(		t2_.convert());

   EXPECT_EQ(tmp.getId(), 			t2_.getId());
   EXPECT_EQ(tmp.getTitle(),		t2_.getTitle());
   EXPECT_EQ(tmp.getDescription(),	t2_.getDescription());
   EXPECT_EQ(tmp.getTime(),			t2_.getTime());
   EXPECT_EQ(tmp.getPriority(),		t2_.getPriority());
   EXPECT_EQ(tmp.getSeverity(),		t2_.getSeverity());
}




