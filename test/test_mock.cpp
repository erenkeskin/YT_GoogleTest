#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace std;
using ::testing::Return;

//
class UserInterface {
    public: 
        virtual ~UserInterface() {;}
        virtual void setName( string userName ) = 0;
        virtual void setAge( int userAge ) = 0;
        virtual string getName() = 0;
        virtual int getAge() = 0;
};

//
class MockUser : public UserInterface {
    public:
        MOCK_METHOD(void, setName, (string userName), (override));
        MOCK_METHOD(void, setAge, (int userAge), (override));
        MOCK_METHOD(string, getName, (), (override));
        MOCK_METHOD(int, getAge, (), (override));
};

//
class DataReminder {
    public: 
        DataReminder(UserInterface * user): user(user) {;}

        //
        void addNewUserName(string userName) {
            user->setName(userName);
        }
        //
        void addNewUserAge(int userAge) {
            user->setAge(userAge);
        }
        //
        string getUserName() {
            return user->getName();
        }
        //
        int getUserAge() {
            return user->getAge();
        }
    protected:
        UserInterface * user;
};

//
TEST(GmockTest, construct_test) {
    MockUser user_mock;
    DataReminder dataReminder(&user_mock);

    EXPECT_CALL(user_mock, setName("Hasan Eren Keskin"));
    EXPECT_CALL(user_mock, setAge(26));
    
    dataReminder.addNewUserName("Hasan Eren Keskin");
    dataReminder.addNewUserAge(26);
}

//
TEST(GmockTest, set_and_get_data) {
    MockUser user_mock;
    DataReminder dataReminder(&user_mock);

    EXPECT_CALL(user_mock, setName("Hasan Eren Keskin"));
    EXPECT_CALL(user_mock, setAge(26));

    EXPECT_CALL(user_mock, getName()).WillOnce(Return("Hasan Eren Keskin"));
    EXPECT_CALL(user_mock, getAge()).WillOnce(Return(26));

    dataReminder.addNewUserName("Hasan Eren Keskin");
    dataReminder.addNewUserAge(26);

    string user_name = dataReminder.getUserName();
    int user_age = dataReminder.getUserAge();

    ASSERT_STREQ("Hasan Eren Keskin", user_name.c_str());
    ASSERT_EQ(26, user_age);
}


