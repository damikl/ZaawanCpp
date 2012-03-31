#include <gtest/gtest.h>
#include <algorithm>
#include "datamanager.hpp"
using namespace std;

class DataManagerTest : public ::testing::Test {
 protected:
  DataManagerTest() : datam(DataManager::instanceOf())
						{}
  virtual void SetUp() {
    t1 = datam->addTask("t1");
    t2 = datam->addTask("t2");
    t3 = datam->addTask("t3");
    t4 = datam->addTask("t4");
    t5 = datam->addTask("t5");
    t6 = datam->addTask("t6");
  }

  // virtual void TearDown() {}
  DataManager* datam;
  int t1, t2, t3, t4, t5, t6;
};

TEST_F(DataManagerTest,auth)
{
	ASSERT_FALSE(datam->auth_required());
	ASSERT_TRUE(datam->auth(""));
	datam->setPasscode("","qwerty");
	ASSERT_FALSE(datam->auth("zxcv"));
	ASSERT_TRUE(datam->auth("qwerty"));
	ASSERT_TRUE(datam->auth_required());
}

TEST_F(DataManagerTest,find)
{
	EXPECT_EQ(t1,datam->find(t1)->getId());
	EXPECT_EQ(t2,datam->find(t2)->getId());
	EXPECT_EQ(t3,datam->find(t3)->getId());
	EXPECT_EQ(t4,datam->find(t4)->getId());
	EXPECT_EQ(t5,datam->find(t5)->getId());
	EXPECT_EQ(t6,datam->find(t6)->getId());
	EXPECT_TRUE(datam->find(-1) == datam->getList().end() );
}
