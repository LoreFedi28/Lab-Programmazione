#include "gtest/gtest.h"
#include "../TodoList.h"
#include "../Activity.h"

TEST(ActivityTest, SerializationAndDeserialization) {
    Activity activity("Test Activity", true);
    std::string serialized = activity.serialize();
    Activity deserialized = Activity::deserialize(serialized);

    EXPECT_EQ(activity.getDescription(), deserialized.getDescription());
    EXPECT_EQ(activity.isCompleted(), deserialized.isCompleted());
}

TEST(TodoListTest, AddAndRemoveActivity) {
    TodoList todoList;
    Activity activity1("First Activity");
    Activity activity2("Second Activity");

    todoList.addActivity(activity1);
    todoList.addActivity(activity2);

    ASSERT_EQ(2, todoList.getActivities().size());
    EXPECT_EQ("First Activity", todoList.getActivities()[0].getDescription());
    EXPECT_EQ("Second Activity", todoList.getActivities()[1].getDescription());

    todoList.removeActivity(0);
    ASSERT_EQ(1, todoList.getActivities().size());
    EXPECT_EQ("Second Activity", todoList.getActivities()[0].getDescription());
}

TEST(TodoListTest, SaveAndLoadFromFile) {
    TodoList todoList;
    todoList.addActivity(Activity("Activity 1"));
    todoList.addActivity(Activity("Activity 2", true));

    todoList.saveToFile("testfile.txt");

    TodoList loadedList;
    loadedList.loadFromFile("testfile.txt");

    ASSERT_EQ(2, loadedList.getActivities().size());
    EXPECT_EQ("Activity 1", loadedList.getActivities()[0].getDescription());
    EXPECT_FALSE(loadedList.getActivities()[0].isCompleted());
    EXPECT_EQ("Activity 2", loadedList.getActivities()[1].getDescription());
    EXPECT_TRUE(loadedList.getActivities()[1].isCompleted());
}