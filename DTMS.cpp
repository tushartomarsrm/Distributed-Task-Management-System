#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

enum class TaskPriority {
    LOW = 1,
    MEDIUM,
    HIGH
};

struct Task {
    int id;
    std::string description;
    TaskPriority priority;
    std::string deadline;
    bool completed;

    Task(int id, const std::string& description, TaskPriority priority, const std::string& deadline)
        : id(id), description(description), priority(priority), deadline(deadline), completed(false) {}
};

struct Worker {
    int id;
    std::string name;

    Worker(int id, const std::string& name) : id(id), name(name) {}
};

class TaskManager {
private:
    std::vector<Task> tasks;
    std::vector<Worker> workers;
    int nextTaskId = 1;
    int nextWorkerId = 1;

public:
    void addWorker(const std::string& name) {
        workers.emplace_back(nextWorkerId++, name);
    }

    void addTask(const std::string& description, TaskPriority priority, const std::string& deadline) {
        tasks.emplace_back(nextTaskId++, description, priority, deadline);
    }

    void assignTask(int taskId, int workerId) {
        auto taskIt = std::find_if(tasks.begin(), tasks.end(), [taskId](const Task& t) { return t.id == taskId; });
        auto workerIt = std::find_if(workers.begin(), workers.end(), [workerId](const Worker& w) { return w.id == workerId; });

        if (taskIt != tasks.end() && workerIt != workers.end()) {
            std::cout << "Task \"" << taskIt->description << "\" assigned to worker " << workerIt->name << ".\n";
        } else {
            std::cout << "Task or Worker not found.\n";
        }
    }

    void completeTask(int taskId, int workerId) {
        auto taskIt = std::find_if(tasks.begin(), tasks.end(), [taskId](const Task& t) { return t.id == taskId; });

        if (taskIt != tasks.end()) {
            taskIt->completed = true;
            std::cout << "Task \"" << taskIt->description << "\" marked as completed by worker ID " << workerId << ".\n";
        } else {
            std::cout << "Task not found.\n";
        }
    }

    void showTasks() const {
        std::cout << "Tasks:\n";
        for (const auto& task : tasks) {
            std::cout << "ID: " << task.id << ", Description: " << task.description
                      << ", Priority: " << static_cast<int>(task.priority) << ", Deadline: "
                      << task.deadline << ", Completed: " << (task.completed ? "Yes" : "No") << "\n";
        }
    }

    void showWorkers() const {
        std::cout << "Workers:\n";
        for (const auto& worker : workers) {
            std::cout << "ID: " << worker.id << ", Name: " << worker.name << "\n";
        }
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return;
        }

        for (const auto& task : tasks) {
            file << task.id << "," << static_cast<int>(task.priority) << "," << task.description << "," << task.deadline << "\n";
        }

        file.close();
        std::cout << "Tasks saved successfully to " << filename << std::endl;
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream ss(line);
            std::string idStr, priorityStr, description, deadline;

            std::getline(ss, idStr, ',');
            int id = std::stoi(idStr);

            std::getline(ss, priorityStr, ',');
            TaskPriority priority = static_cast<TaskPriority>(std::stoi(priorityStr));

            std::getline(ss, description, ',');

            std::getline(ss, deadline);

            addTask(description, priority, deadline); 
            tasks.back().id = id; 
        }

        file.close();
        std::cout << "Tasks loaded successfully from " << filename << std::endl;
    }
};

class UserInterface {
public:
    void showMenu() {
        TaskManager manager;
        int choice;
        do {
            std::cout << "\n--- Task Management System ---\n";
            std::cout << "1. Add Worker\n";
            std::cout << "2. Add Task\n";
            std::cout << "3. Assign Task\n";
            std::cout << "4. Complete Task\n";
            std::cout << "5. Show All Tasks\n";
            std::cout << "6. Show All Workers\n";
            std::cout << "7. Save to File\n";
            std::cout << "8. Load from File\n";
            std::cout << "9. Exit\n";
            std::cout << "Choose an option: ";
            std::cin >> choice;

            switch (choice) {
                case 1: addWorker(manager); break;
                case 2: addTask(manager); break;
                case 3: assignTask(manager); break;
                case 4: completeTask(manager); break;
                case 5: manager.showTasks(); break;
                case 6: manager.showWorkers(); break;
                case 7: saveToFile(manager); break;
                case 8: loadFromFile(manager); break;
                case 9: std::cout << "Exiting...\n"; break;
                default: std::cout << "Invalid choice, please try again.\n"; break;
            }
        } while (choice != 9);
    }

private:
    void addWorker(TaskManager& manager) {
        std::string name;
        std::cout << "Enter worker name: ";
        std::cin.ignore();
        std::getline(std::cin, name);
        manager.addWorker(name);
        std::cout << "Worker added successfully.\n";
    }

    void addTask(TaskManager& manager) {
        std::string description;
        std::string deadline;
        int priorityChoice;
        TaskPriority priority;

        std::cout << "Enter task description: ";
        std::cin.ignore();
        std::getline(std::cin, description);

        std::cout << "Enter task deadline (YYYY-MM-DD): ";
        std::getline(std::cin, deadline);

        std::cout << "Select task priority (1: Low, 2: Medium, 3: High): ";
        std::cin >> priorityChoice;

        switch (priorityChoice) {
            case 1: priority = TaskPriority::LOW; break;
            case 2: priority = TaskPriority::MEDIUM; break;
            case 3: priority = TaskPriority::HIGH; break;
            default: priority = TaskPriority::LOW; // Default to Low if invalid
        }

        manager.addTask(description, priority, deadline);
        std::cout << "Task added successfully.\n";
    }

    void assignTask(TaskManager& manager) {
        int taskId, workerId;
        std::cout << "Enter task ID to assign: ";
        std::cin >> taskId;
        std::cout << "Enter worker ID to assign the task to: ";
        std::cin >> workerId;
        manager.assignTask(taskId, workerId);
    }

    void completeTask(TaskManager& manager) {
        int taskId, workerId;
        std::cout << "Enter task ID to complete: ";
        std::cin >> taskId;
        std::cout << "Enter worker ID completing the task: ";
        std::cin >> workerId;
        manager.completeTask(taskId, workerId);
    }

    void saveToFile(TaskManager& manager) {
        std::string filename;
        std::cout << "Enter filename to save tasks: ";
        std::cin >> filename;
        manager.saveToFile(filename);
    }

    void loadFromFile(TaskManager& manager) {
        std::string filename;
        std::cout << "Enter filename to load tasks: ";
        std::cin >> filename;
        manager.loadFromFile(filename);
    }
};

int main() {
    UserInterface ui;
    ui.showMenu();
    return 0;
}
