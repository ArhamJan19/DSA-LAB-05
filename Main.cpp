#include <iostream>
#include <sstream>
#include <string>

using namespace std;


class PriorityQueue {
    string* queue;
    int maxSize;
    int front;
    int rear;

public:
 
    PriorityQueue(int size) {
        maxSize = size;
        queue = new string[maxSize];
        front = -1;
        rear = -1;
    }


    ~PriorityQueue() {
        delete[] queue;
    }


    bool isFull() {
        return rear == maxSize - 1;
    }

    bool isEmpty() {
        return front == -1 || front > rear;
    }

    void insert(const string& item) {
        if (isFull()) {
            cout << "Queue is full, cannot insert more items.\n";
        } else {
            if (front == -1) front = 0;
            queue[++rear] = item;
        }
    }

    void remove(string& item) {
        if (isEmpty()) {
            cout << "Queue is empty, no items to remove.\n";
        } else {
            item = queue[front++];
        }
    }


    int getSize() {
        return rear - front + 1;
    }
};

int getValidIntInput(const string& prompt) {
    string input;
    int value;
    while (true) {
        cout << prompt;
        getline(cin, input);
        stringstream ss(input);
        if (ss >> value && ss.eof()) {
            return value;
        }
        cout << "Invalid input, please enter a valid number.\n";
    }
}

int main() {
  
    cout << "Priority Queue Management\n";
    int queueSize = getValidIntInput("Enter the max size for the queue: ");
    PriorityQueue pq(queueSize);

    string* admins = new string[queueSize];
    string* faculty = new string[queueSize];
    string* students = new string[queueSize];

    int adminCount = 0, facultyCount = 0, studentCount = 0;

    bool running = true;
    while (running) {
 
        cout << "\n----- Main Menu -----\n";
        cout << "1. Insert Members\n";
        cout << "2. Remove Members\n";
        cout << "3. Exit\n";
        int choice = getValidIntInput("Enter your choice (1-3): ");

        if (choice == 1) {
            int memberCount = getValidIntInput("How many members do you want to add? ");
            
            for (int i = 0; i < memberCount; i++) {
                int memberType = getValidIntInput("\n1. Admin\n2. Faculty\n3. Student\nSelect the type of member (1-3): ");
                
                if (memberType == 1) {
                    admins[adminCount++] = "Admin" + to_string(adminCount);
                } else if (memberType == 2) {
                    faculty[facultyCount++] = "Faculty" + to_string(facultyCount);
                } else if (memberType == 3) {
                    students[studentCount++] = "Student" + to_string(studentCount);
                } else {
                    cout << "Invalid member type selected.\n";
                }
            }

            int totalMembers = adminCount + facultyCount + studentCount;
            if (totalMembers > queueSize) {
                cout << "Queue Overflow! Too many members.\n";
            } else {
                for (int i = 0; i < adminCount; i++) {
                    pq.insert(admins[i]);
                }
                for (int i = 0; i < facultyCount; i++) {
                    pq.insert(faculty[i]);
                }
                for (int i = 0; i < studentCount; i++) {
                    pq.insert(students[i]);
                }
                cout << "Items inserted successfully!\n";
            }
        } else if (choice == 2) {
            if (pq.isEmpty()) {
                cout << "The queue is empty.\n";
            } else {
                int removeCount = getValidIntInput("How many members do you want to remove? ");
                if (removeCount > pq.getSize()) {
                    cout << "You cannot remove more members than are in the queue.\n";
                } else {
                    for (int i = 0; i < removeCount; i++) {
                        string item;
                        pq.remove(item);
                        cout << "Removed: " << item << endl;
                    }
                }
            }
        } else if (choice == 3) {
            running = false;
            cout << "Exiting the program.\n";
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }


    delete[] admins;
    delete[] faculty;
    delete[] students;

    return 0;
}
