# Task Management System

## Overview

The Task Management System is a C++ console application designed to help users manage tasks and workers efficiently. Users can add workers, create tasks with different priorities, assign tasks to workers, and mark them as completed. The system also supports saving tasks to a file and loading tasks from a file, ensuring that data is persistent across sessions.

## Features

- **Add Workers:** Create and manage workers with unique IDs and names.
- **Add Tasks:** Create tasks with descriptions, priorities (Low, Medium, High), and deadlines.
- **Assign Tasks:** Assign tasks to specific workers based on their IDs.
- **Complete Tasks:** Mark tasks as completed.
- **Display Information:** Show all tasks and workers in the system.
- **File Operations:** Save tasks to a file and load tasks from a file for data persistence.

### Compilation

To compile the application, use the following command in your terminal:

```bash
g++ -o task_manager task_manager.cpp
```

### Running the Application

After compiling, run the executable:

```bash
./task_manager
```

## Usage Instructions

Once the application is running, you will see a menu with the following options:

1. **Add Worker:** Enter the name of the worker to add a new worker.
2. **Add Task:** Enter a description, deadline, and priority level (1 for Low, 2 for Medium, 3 for High) to add a new task.
3. **Assign Task:** Enter the task ID and worker ID to assign a specific task to a worker.
4. **Complete Task:** Enter the task ID and worker ID to mark a task as completed.
5. **Show All Tasks:** Display all tasks along with their details.
6. **Show All Workers:** Display all workers along with their details.
7. **Save to File:** Enter a filename to save the current tasks to a file.
8. **Load from File:** Enter a filename to load tasks from a file.
9. **Exit:** Exit the application.

## Example Workflow

1. **Add Workers:**
   - Enter names for new workers as prompted.
   
2. **Add Tasks:**
   - Create tasks with descriptions, deadlines, and priorities.

3. **Assign Tasks:**
   - Assign created tasks to the respective workers.

4. **Complete Tasks:**
   - Mark tasks as completed when they are finished.

5. **Save and Load Tasks:**
   - Save the current tasks to a file to maintain data integrity.
   - Load previously saved tasks from a file.

## Code Structure

The main components of the application are:

- **TaskManager:** Handles the creation and management of tasks and workers.
- **UserInterface:** Provides a console-based interface for user interactions.
- **TaskPriority (enum):** Enum class representing task priority levels.
- **Task (struct):** Struct to define a task's properties.
- **Worker (struct):** Struct to define a worker's properties.
