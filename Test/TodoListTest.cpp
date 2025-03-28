#include "gtest/gtest.h"
#include "../TodoList.h"
#include "../Activity.h"
#include "MockObserver.h"
#include <iostream>

TEST(ActivityTest, Serialization) {
    std::cout << "\nRunning Serialization test...\n";

    std::time_t dueDate = 1700000000;
    Activity activity("Test Activity", true, dueDate);

    std::string serialized = activity.serialize();
    EXPECT_FALSE(serialized.empty());

    std::cout << "Serialization test PASSED!\n";
}

TEST(ActivityTest, Deserialization) {
    std::cout << "\nRunning Deserialization test...\n";

    std::string serialized = "Test Activity;1;1700000000";
    std::cout << "Serialized input: " << serialized << std::endl;

    EXPECT_NO_THROW({
        Activity deserialized = Activity::deserialize(serialized);
        EXPECT_EQ(deserialized.getDescription(), "Test Activity");
        EXPECT_TRUE(deserialized.isCompleted());
        EXPECT_EQ(deserialized.getDueDate(), 1700000000);
    });

    std::cout << "Deserialization test PASSED!\n";
}

// Test adding activities from the TodoList
TEST(TodoListTest, AddActivity) {
    std::cout << "\nRunning AddActivity test...\n";

    TodoList todoList("TestList");
    MockObserver observer;
    todoList.addObserver(&observer);

    observer.updated = false;
    todoList.addActivity(Activity("Task 1"));
    EXPECT_TRUE(observer.updated);
    EXPECT_EQ(todoList.getTotalActivities(), 1);

    observer.updated = false;
    todoList.addActivity(Activity("Task 2"));
    EXPECT_TRUE(observer.updated);
    EXPECT_EQ(todoList.getTotalActivities(), 2);

    std::cout << "AddActivity test PASSED!\n";
}

TEST(TodoListTest, RemoveActivity) {
    std::cout << "\nRunning RemoveActivity test...\n";

    TodoList todoList("TestList");
    todoList.addActivity(Activity("Task A"));
    todoList.addActivity(Activity("Task B"));
    todoList.addActivity(Activity("Task C"));

    // Remove by index (valid)
    EXPECT_NO_THROW(todoList.removeActivity("1", true));
    EXPECT_EQ(todoList.getTotalActivities(), 2);

    // Remove by name (valid)
    EXPECT_NO_THROW(todoList.removeActivity("Task C", true));
    EXPECT_EQ(todoList.getTotalActivities(), 1);

    std::cout << "RemoveActivity test PASSED!\n";
}

TEST(TodoListTest, RemoveInvalidActivity) {
    std::cout << "\nRunning RemoveInvalidActivity test...\n";

    TodoList todoList("TestList");
    MockObserver observer;
    todoList.addObserver(&observer);

    // Expect exceptions for invalid removals
    EXPECT_THROW(todoList.removeActivity("10", true), std::out_of_range);
    EXPECT_THROW(todoList.removeActivity("999", true), std::out_of_range);
    EXPECT_THROW(todoList.removeActivity("-1", true), std::out_of_range);
    EXPECT_THROW(todoList.removeActivity("Nonexistent Task", true), std::out_of_range);

    std::cout << "RemoveInvalidActivity test PASSED!\n";
}

TEST(TodoListTest, MarkActivityAsCompleted) {
    std::cout << "\nRunning MarkActivityAsCompleted test...\n";

    TodoList todoList("TestList");

    // Add two activities, both initially not completed
    todoList.addActivity(Activity("Task A", false));
    todoList.addActivity(Activity("Task B", false));

    // At the beginning: 2 total activities, 2 pending
    EXPECT_EQ(todoList.getTotalActivities(), 2);
    EXPECT_EQ(todoList.getPendingActivities(), 2);

    EXPECT_NO_THROW(todoList.markActivityAsCompleted("Task A"));
    EXPECT_EQ(todoList.getPendingActivities(), 1);  // One pending activity left

    EXPECT_NO_THROW(todoList.markActivityAsCompleted("Task B"));
    EXPECT_EQ(todoList.getPendingActivities(), 0);  // All activities completed

    EXPECT_EQ(todoList.getTotalActivities() - todoList.getPendingActivities(), 2); // 2 activities completed

    std::cout << "MarkActivityAsCompleted test PASSED!\n";
}

TEST(TodoListTest, MarkInvalidActivity) {
    std::cout << "\nRunning MarkInvalidActivity test...\n";

    TodoList todoList("TestList");
    todoList.addActivity(Activity("Task Y", false));

    // Expect exceptions for invalid marks
    EXPECT_THROW(todoList.markActivityAsCompleted("99"), std::out_of_range);
    EXPECT_THROW(todoList.markActivityAsCompleted("Nonexistent Task"), std::out_of_range);

    // Ensure the existing activity is still uncompleted
    EXPECT_FALSE(todoList.getActivities()[0].isCompleted());

    std::cout << "MarkInvalidActivity test PASSED!\n";
}

TEST(TodoListTest, EditActivity) {
    std::cout << "\nRunning EditActivity test...\n";

    TodoList todoList("TestList");

    std::time_t originalDate = 1700000000;
    std::time_t newDate = 1700500000;

    // Add initial activity
    todoList.addActivity(Activity("Initial Task", false, originalDate));

    // Edit description only
    bool result1 = todoList.editActivity("1", "Updated Task", false, false, false, 0);
    EXPECT_TRUE(result1);
    EXPECT_EQ(todoList.getActivities()[0].getDescription(), "Updated Task");
    EXPECT_FALSE(todoList.getActivities()[0].isCompleted());
    EXPECT_EQ(todoList.getActivities()[0].getDueDate(), originalDate);

    // Edit completion status only
    bool result2 = todoList.editActivity("1", "", true, true, false, 0);
    EXPECT_TRUE(result2);
    EXPECT_TRUE(todoList.getActivities()[0].isCompleted());

    // Edit due date only
    bool result3 = todoList.editActivity("1", "", false, false, true, newDate);
    EXPECT_TRUE(result3);
    EXPECT_EQ(todoList.getActivities()[0].getDueDate(), newDate);

    // Edit all fields
    bool result4 = todoList.editActivity("1", "Final Task", true, false, true, originalDate);
    EXPECT_TRUE(result4);
    EXPECT_EQ(todoList.getActivities()[0].getDescription(), "Final Task");
    EXPECT_FALSE(todoList.getActivities()[0].isCompleted());
    EXPECT_EQ(todoList.getActivities()[0].getDueDate(), originalDate);

    // Invalid identifier (non-existent index)
    bool result5 = todoList.editActivity("99", "Should Fail", false, false, false, 0);
    EXPECT_FALSE(result5);

    // Invalid identifier (non-existent name)
    bool result6 = todoList.editActivity("Nonexistent", "Should Fail", false, false, false, 0);
    EXPECT_FALSE(result6);

    std::cout << "EditActivity test PASSED!\n";
}

TEST(TodoListTest, CountActivities) {
    std::cout << "\nRunning CountActivities test...\n";

    TodoList todoList("TestList");
    todoList.addActivity(Activity("Task 1", false));
    todoList.addActivity(Activity("Task 2", true));
    todoList.addActivity(Activity("Task 3", false));

    EXPECT_EQ(todoList.getTotalActivities(), 3);
    EXPECT_EQ(todoList.getPendingActivities(), 2);

    std::cout << "CountActivities test PASSED!\n";
}

TEST(TodoListTest, ToString) {
    std::cout << "\nRunning ToString test...\n";

    TodoList todoList("TestList");
    todoList.addActivity(Activity("Task 1", false));
    todoList.addActivity(Activity("Task 2", true));
    todoList.addActivity(Activity("Task 3", false));

    std::string expectedOutput =
        "--- Todo List: TestList ---\n"
        "1. Task 1 [Not Done] (Due: Thu Jan 01 01:00:00 1970)\n"
        "2. Task 2 [Done] (Due: Thu Jan 01 01:00:00 1970)\n"
        "3. Task 3 [Not Done] (Due: Thu Jan 01 01:00:00 1970)\n";

    EXPECT_EQ(todoList.toString(), expectedOutput);

    std::cout << "ToString test PASSED!\n";
}

TEST(TodoListTest, FindActivitiesByName) {
    std::cout << "\nRunning FindActivitiesByName test...\n";

    TodoList todoList("TestList");

    // Add two activities with the same name and one with a different name
    todoList.addActivity(Activity("Workout", false));
    todoList.addActivity(Activity("Workout", true));
    todoList.addActivity(Activity("Shopping", false));

    // Case 1: Matching name
    auto result = todoList.findActivitiesByName("Workout");
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0].getDescription(), "Workout");
    EXPECT_EQ(result[1].getDescription(), "Workout");

    // Case 2: Name not found
    auto emptyResult = todoList.findActivitiesByName("Nonexistent");
    EXPECT_TRUE(emptyResult.empty());  // Should return an empty vector

    std::cout << "FindActivitiesByName test PASSED!\n";
}

TEST(TodoListTest, FindActivitiesByDueDate) {
    std::cout << "\nRunning FindActivitiesByDueDate test...\n";

    TodoList todoList("TestList");
    std::time_t date1 = 1700000000;
    std::time_t date2 = 1700005000;
    std::time_t nonexistentDate = 1800000000;  // No activity has this due date

    // Add activities with two different due dates
    todoList.addActivity(Activity("Task 1", false, date1));
    todoList.addActivity(Activity("Task 2", false, date2));
    todoList.addActivity(Activity("Task 3", false, date1)); // Same date as Task 1

    // Case 1: Match on date1 (2 tasks expected)
    auto result = todoList.findActivitiesByDueDate(date1);
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0].getDueDate(), date1);
    EXPECT_EQ(result[1].getDueDate(), date1);

    // Case 2: No task with the given date
    auto emptyResult = todoList.findActivitiesByDueDate(nonexistentDate);
    EXPECT_TRUE(emptyResult.empty());

    std::cout << "FindActivitiesByDueDate test PASSED!\n";
}

// Test saving and loading activities from a file
TEST(TodoListTest, SaveAndLoadFromFile) {
    std::cout << "\nRunning SaveAndLoadFromFile test...\n";

    TodoList todoList("TestList");
    MockObserver observer;
    todoList.addObserver(&observer);

    std::time_t dueDate1 = 1700000000;
    std::time_t dueDate2 = 1700005000;

    todoList.addActivity(Activity("Activity 1", false, dueDate1));
    todoList.addActivity(Activity("Activity 2", true, dueDate2));

    // Save activities to a test file
    std::string filename = "testfile.txt";
    todoList.saveToFile(filename);

    todoList.removeObserver(&observer); // Avoid unnecessary updates in tests

    // Load activities from the file into a new TodoList instance
    TodoList loadedList("LoadedList");
    loadedList.loadFromFile(filename);

    // Verify that both activities were loaded correctly
    ASSERT_EQ(2, loadedList.getActivities().size());
    EXPECT_EQ("Activity 1", loadedList.getActivities()[0].getDescription());
    EXPECT_FALSE(loadedList.getActivities()[0].isCompleted());
    EXPECT_EQ(dueDate1, loadedList.getActivities()[0].getDueDate());

    EXPECT_EQ("Activity 2", loadedList.getActivities()[1].getDescription());
    EXPECT_TRUE(loadedList.getActivities()[1].isCompleted());
    EXPECT_EQ(dueDate2, loadedList.getActivities()[1].getDueDate());

    // Remove the test file to clean up
    std::remove(filename.c_str());

    std::cout << "SaveAndLoadFromFile test PASSED!\n";
}

// Test loading from a non-existent file
TEST(TodoListTest, LoadNonExistentFile) {
    std::cout << "\nRunning LoadNonExistentFile test...\n";

    TodoList todoList("TestList");

    // Ensure loading a non-existent file throws an exception
    EXPECT_THROW(todoList.loadFromFile("nonexistent.txt"), std::runtime_error);

    std::cout << "LoadNonExistentFile test PASSED!\n";
}

// Test removing an observer and ensuring it no longer receives updates
TEST(TodoListTest, RemoveObserver) {
    std::cout << "\nRunning RemoveObserver test...\n";

    TodoList todoList("TestList");
    MockObserver observer;
    todoList.addObserver(&observer);

    todoList.addActivity(Activity("Test Activity"));
    EXPECT_TRUE(observer.updated); // Observer should be notified

    observer.updated = false;
    todoList.removeObserver(&observer); // Remove observer

    todoList.addActivity(Activity("Another Activity"));
    EXPECT_FALSE(observer.updated); // Observer should NOT be notified after removal

    std::cout << "RemoveObserver test PASSED!\n";
}

// Test creating multiple TodoLists and switching between them
TEST(MultipleTodoListsTest, CreateAndSwitchLists) {
    std::cout << "\nRunning CreateAndSwitchLists test...\n";

    std::map<std::string, TodoList> todoLists;
    todoLists["Work"] = TodoList("Work");
    todoLists["Personal"] = TodoList("Personal");

    EXPECT_EQ(todoLists["Work"].getName(), "Work");
    EXPECT_EQ(todoLists["Personal"].getName(), "Personal");

    std::cout << "CreateAndSwitchLists test PASSED!\n";
}

// Test renaming a TodoList
TEST(MultipleTodoListsTest, RenameTodoList) {
    std::cout << "\nRunning RenameTodoList test...\n";

    TodoList todoList("OldName");
    EXPECT_EQ(todoList.getName(), "OldName");

    todoList.setName("NewName");
    EXPECT_EQ(todoList.getName(), "NewName");

    std::cout << "RenameTodoList test PASSED!\n";
}

// Test adding activities to different lists
TEST(MultipleTodoListsTest, AddActivitiesToMultipleLists) {
    std::cout << "\nRunning AddActivitiesToMultipleLists test...\n";

    std::map<std::string, TodoList> todoLists;
    todoLists["Work"] = TodoList("Work");
    todoLists["Personal"] = TodoList("Personal");

    todoLists["Work"].addActivity(Activity("Complete report"));
    todoLists["Personal"].addActivity(Activity("Buy groceries"));

    EXPECT_EQ(todoLists["Work"].getActivities().size(), 1);
    EXPECT_EQ(todoLists["Personal"].getActivities().size(), 1);

    EXPECT_EQ(todoLists["Work"].getActivities()[0].getDescription(), "Complete report");
    EXPECT_EQ(todoLists["Personal"].getActivities()[0].getDescription(), "Buy groceries");

    std::cout << "AddActivitiesToMultipleLists test PASSED!\n";
}

// Test saving and loading multiple lists
TEST(MultipleTodoListsTest, SaveAndLoadMultipleLists) {
    std::cout << "\nRunning SaveAndLoadMultipleLists test...\n";

    std::map<std::string, TodoList> todoLists;
    todoLists["Work"] = TodoList("Work");
    todoLists["Personal"] = TodoList("Personal");

    todoLists["Work"].addActivity(Activity("Prepare presentation"));
    todoLists["Personal"].addActivity(Activity("Read book"));

    todoLists["Work"].saveToFile("work_tasks.txt");
    todoLists["Personal"].saveToFile("personal_tasks.txt");

    TodoList loadedWork("Work");
    TodoList loadedPersonal("Personal");

    loadedWork.loadFromFile("work_tasks.txt");
    loadedPersonal.loadFromFile("personal_tasks.txt");

    EXPECT_EQ(loadedWork.getActivities().size(), 1);
    EXPECT_EQ(loadedWork.getActivities()[0].getDescription(), "Prepare presentation");

    EXPECT_EQ(loadedPersonal.getActivities().size(), 1);
    EXPECT_EQ(loadedPersonal.getActivities()[0].getDescription(), "Read book");

    std::cout << "SaveAndLoadMultipleLists test PASSED!\n";
}