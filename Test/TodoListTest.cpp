#include "gtest/gtest.h"
#include "../TodoList.h"
#include "../Activity.h"
#include "MockObserver.h"
#include <iostream>

// Test serialization and deserialization of Activity
TEST(ActivityTest, SerializationAndDeserialization) {
    std::cout << "\nRunning SerializationAndDeserialization test...\n";

    std::time_t dueDate = 1700000000; // Example timestamp
    Activity activity("Test Activity", true, dueDate);
    std::string serialized = activity.serialize();
    Activity deserialized = Activity::deserialize(serialized);

    EXPECT_EQ(activity.getDescription(), deserialized.getDescription());
    EXPECT_EQ(activity.isCompleted(), deserialized.isCompleted());
    EXPECT_EQ(activity.getDueDate(), deserialized.getDueDate());

    std::cout << "SerializationAndDeserialization test PASSED!\n";
}

// Test adding and removing activities
TEST(TodoListTest, AddAndRemoveActivity) {
    std::cout << "\nRunning AddAndRemoveActivity test...\n";

    TodoList todoList;
    MockObserver observer;
    todoList.addObserver(&observer);

    Activity activity1("First Activity");
    Activity activity2("Second Activity");

    observer.updated = false;
    todoList.addActivity(activity1);
    EXPECT_TRUE(observer.updated);

    observer.updated = false;
    todoList.addActivity(activity2);
    EXPECT_TRUE(observer.updated);

    ASSERT_EQ(todoList.getActivities().size(), 2);

    observer.updated = false;
    todoList.removeActivity(0, true);
    EXPECT_TRUE(observer.updated);

    ASSERT_EQ(todoList.getActivities().size(), 1);

    std::cout << "AddAndRemoveActivity test PASSED!\n";
}

// Test marking an activity as completed
TEST(TodoListTest, MarkActivityAsCompleted) {
    std::cout << "\nRunning MarkActivityAsCompleted test...\n";

    TodoList todoList;
    MockObserver observer;
    todoList.addObserver(&observer);

    std::time_t dueDate = 1700000000;
    todoList.addActivity(Activity("Test Activity", false, dueDate));

    EXPECT_FALSE(todoList.getActivities()[0].isCompleted());
    EXPECT_TRUE(observer.updated);

    observer.updated = false;
    todoList.markActivityAsCompleted(0);

    EXPECT_TRUE(todoList.getActivities()[0].isCompleted());
    EXPECT_TRUE(observer.updated);

    std::cout << "MarkActivityAsCompleted test PASSED!\n";
}

// Test saving and loading activities from a file
TEST(TodoListTest, SaveAndLoadFromFile) {
    std::cout << "\nRunning SaveAndLoadFromFile test...\n";

    TodoList todoList;
    MockObserver observer;
    todoList.addObserver(&observer);

    std::time_t dueDate1 = 1700000000;
    std::time_t dueDate2 = 1700005000;

    todoList.addActivity(Activity("Activity 1", false, dueDate1));
    todoList.addActivity(Activity("Activity 2", true, dueDate2));

    std::string filename = "testfile.txt";
    todoList.saveToFile(filename);

    todoList.removeObserver(&observer);

    TodoList loadedList;
    loadedList.loadFromFile(filename);

    ASSERT_EQ(2, loadedList.getActivities().size());
    EXPECT_EQ("Activity 1", loadedList.getActivities()[0].getDescription());
    EXPECT_FALSE(loadedList.getActivities()[0].isCompleted());
    EXPECT_EQ(dueDate1, loadedList.getActivities()[0].getDueDate());

    EXPECT_EQ("Activity 2", loadedList.getActivities()[1].getDescription());
    EXPECT_TRUE(loadedList.getActivities()[1].isCompleted());
    EXPECT_EQ(dueDate2, loadedList.getActivities()[1].getDueDate());

    std::remove(filename.c_str());

    std::cout << "SaveAndLoadFromFile test PASSED!\n";
}

// Test removing an activity with an invalid index
TEST(TodoListTest, RemoveInvalidIndex) {
    std::cout << "\nRunning RemoveInvalidIndex test...\n";

    TodoList todoList;
    MockObserver observer;
    todoList.addObserver(&observer);

    todoList.addActivity(Activity("Test Activity"));
    EXPECT_EQ(todoList.getActivities().size(), 1);

    observer.updated = false;

    std::stringstream buffer;
    std::streambuf* oldCerr = std::cerr.rdbuf(buffer.rdbuf());

    todoList.removeActivity(10, true);

    std::cerr.rdbuf(oldCerr);

    EXPECT_EQ(todoList.getActivities().size(), 1);
    EXPECT_FALSE(observer.updated);
    EXPECT_NE(buffer.str().find("Invalid index!"), std::string::npos);

    std::cout << "RemoveInvalidIndex test PASSED!\n";
}

// Test loading from a non-existent file
TEST(TodoListTest, LoadNonExistentFile) {
    std::cout << "\nRunning LoadNonExistentFile test...\n";

    TodoList todoList;
    EXPECT_THROW(todoList.loadFromFile("nonexistent.txt"), std::runtime_error);

    std::cout << "LoadNonExistentFile test PASSED!\n";
}

// Test removing an observer
TEST(TodoListTest, RemoveObserver) {
    std::cout << "\nRunning RemoveObserver test...\n";

    TodoList todoList;
    MockObserver observer;
    todoList.addObserver(&observer);

    todoList.addActivity(Activity("Test Activity"));
    EXPECT_TRUE(observer.updated);

    observer.updated = false;
    todoList.removeObserver(&observer);

    todoList.addActivity(Activity("Another Activity"));
    EXPECT_FALSE(observer.updated);

    std::cout << "RemoveObserver test PASSED!\n";
}