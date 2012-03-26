#include <gtest/gtest.h>
#include "task.hpp"
using namespace std;
 
// Tests the putDigit() method.
TEST(Task, getTitle) {
  string title = "Wycieczka            ";
  string desc = "Wycieczka   w   bieszczady  ";
  string priority = "Higth";
  string severity = "Serious";
  Task t = Task(2,title,desc,priority,severity);
  t.setDate(14,8,2012);
  t.setTime(18,50,40);

  // EXPECT_EQ() evaluates its arguments exactly once, so they
  // can have side effects.

  EXPECT_EQ("Wycieczka", t.getTitle());
  EXPECT_EQ("Higth", t.getPriority());
  EXPECT_EQ("Serious", t.getSeverity());
  ASSERT_FALSE(t.setDate(8,0,2000));
  ASSERT_FALSE(t.setDate(29,2,2011));
  ASSERT_FALSE(t.setDate(32,1,2000));
}
