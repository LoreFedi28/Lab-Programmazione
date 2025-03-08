#include "gtest/gtest.h"
#include "../TodoList.h"
#include "../Activity.h"

// Test serialization and deserialization of Activity
TEST(ActivityTest, SerializationAndDeserialization) {
    // Create an activity and serialize it
    Activity activity("Test Activity", true);
    std::string serialized = activity.serialize();

    // Deserialize the string back into an Activity object
    Activity deserialized = Activity::deserialize(serialized);

    // Check if the data is the same after serialization and deserialization
    EXPECT_EQ(activity.getDescription(), deserialized.getDescription());
    EXPECT_EQ(activity.isCompleted(), deserialized.isCompleted());
}

TEST(TodoListTest, AddAndRemoveActivity) {
    TodoList todoList;

    // Add two activities
    Activity activity1("First Activity");
    Activity activity2("Second Activity");
    todoList.addActivity(activity1);
    todoList.addActivity(activity2);

    // Verify that two activities have been added
    ASSERT_EQ(2, todoList.getActivities().size());
    EXPECT_EQ("First Activity", todoList.getActivities()[0].getDescription());
    EXPECT_EQ("Second Activity", todoList.getActivities()[1].getDescription());

    // Remove the first activity (skip confirmation in tests)
    todoList.removeActivity(0, true);

    // Verify that only one activity remains, and it's the correct one
    ASSERT_EQ(1, todoList.getActivities().size());
    EXPECT_EQ("Second Activity", todoList.getActivities()[0].getDescription());
}

// Test saving and loading activities from a file
TEST(TodoListTest, SaveAndLoadFromFile) {
    TodoList todoList;

    // Add two activities
    todoList.addActivity(Activity("Activity 1"));
    todoList.addActivity(Activity("Activity 2", true));

    // Save activities to a test file
    todoList.saveToFile("testfile.txt");

    // Load activities from the file into a new TodoList instance
    TodoList loadedList;
    loadedList.loadFromFile("testfile.txt");

    // Verify that both activities were loaded correctly
    ASSERT_EQ(2, loadedList.getActivities().size());
    EXPECT_EQ("Activity 1", loadedList.getActivities()[0].getDescription());
    EXPECT_FALSE(loadedList.getActivities()[0].isCompleted());
    EXPECT_EQ("Activity 2", loadedList.getActivities()[1].getDescription());
    EXPECT_TRUE(loadedList.getActivities()[1].isCompleted());
}