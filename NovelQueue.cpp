#include <iostream>
using namespace std;



// Class representing a CPU Job
class CPUJob {
public:
    int job_id;              // Unique identifier for the job
    int priority;            // Priority level of the job
    int job_type;            // Job type
    int cpu_time_consumed;   // Total CPU time consumed
    int memory_consumed;     // Total memory consumed so far

    CPUJob(int id, int prio, int type, int cpu_time, int memory) // Constructor
        : job_id(id), priority(prio), job_type(type), 
          cpu_time_consumed(cpu_time), memory_consumed(memory) {}

    // Method to display the job details
    void display() const {
        cout << "Job ID: " << job_id
             << ", Priority: " << priority
             << ", Job Type: " << job_type
             << ", CPU Time Consumed: " << cpu_time_consumed
             << ", Memory Consumed: " << memory_consumed << endl;
    }
};

// Class for Queue Nodes, specifically holding CPUJob pointers
class QueueNode {
public:
    CPUJob* jobPointer;       // Pointer to a CPUJob
    QueueNode* next;          // Pointer to the next node in the queue

    // Constructor
    QueueNode(CPUJob* job) : jobPointer(job), next(nullptr) {}
};

// Class for NovelQueue, a queue of CPUJob pointers
class NovelQueue {
public:
    QueueNode* front;        // Front of the queue
    QueueNode* rear;         // Rear of the queue
    QueueNode** NodePtrs;    // Array of pointers to Queue nodes
    int size;                // Number of elements in the queue
    int capacity;            // Capacity of the NodePtrs array

   NovelQueue(int capacity) : front(nullptr), rear(nullptr), size(0), capacity(capacity) {
        NodePtrs = new QueueNode*[capacity];  // Create NodePtrs array with the specified capacity
    }

    ~NovelQueue() { // Destructor
        delete[] NodePtrs;
    }


    // Add (Enqueue) operation
    void Add(CPUJob* job) {
    // Check if job with same ID already exists
    for (int i = 0; i < size; ++i) {
        if (NodePtrs[i]->jobPointer->job_id == job->job_id) {
            cout << "Job ID " << job->job_id << " already exists!" << endl;
            return;  // Exit without adding the job
        }
    }
    
    // Add the job to the queue
    QueueNode* newNode = new QueueNode(job);
    if (!rear) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    
    size++;
    
    updatePointers();
    
    // Print the newly added job and the state of the queue after adding
    cout << "Enqueued Job:" << endl;
    job->display();
    cout << "Jobs after enqueue:" << endl;
    display();
}

    // Sort the NodePtrs array by job_id
    void sortNodePtrs() {
        for (int i = 0; i < size - 1; ++i) {
            for (int j = i + 1; j < size; ++j) {
                if (NodePtrs[i]->jobPointer->job_id > NodePtrs[j]->jobPointer->job_id) {
                    QueueNode* temp = NodePtrs[i];
                    NodePtrs[i] = NodePtrs[j];
                    NodePtrs[j] = temp;
                }
            }
        }
    }

    // Remove (Dequeue) operation
    CPUJob* Remove() {
        if (!front) return nullptr; 
        QueueNode* temp = front; // Remove the front node
        front = front->next; // Update the front pointer
        if (!front) rear = nullptr;
        CPUJob* job = temp->jobPointer;  // Get the job pointer
        delete temp;
        size--;
        updatePointers();
        return job;
    }

    // Modify operation
    void modify(int job_id, int new_priority, int new_job_type, int new_cpu_time_consumed, int new_memory_consumed) {
    QueueNode* current = front;  // Start from the front of the queue

    // Traverse the queue to find the job with the specified ID
    while (current) {
        if (current->jobPointer->job_id == job_id) {
            // Modify the job attributes
            current->jobPointer->priority = new_priority;
            current->jobPointer->job_type = new_job_type;
            current->jobPointer->cpu_time_consumed = new_cpu_time_consumed;
            current->jobPointer->memory_consumed = new_memory_consumed;

            // Print the confirmation of modification
            cout << "Modified Job ID " << job_id << ":" << endl;
            current->jobPointer->display();  // Display the modified job

            // After modification, display the entire queue
            cout << "Jobs after modification:" << endl;
            display();  // Call display to show the entire queue
            return;  // Exit after the job is found and modified
        }
        current = current->next;  // Move to the next node in the queue
    }

    // If job ID not found, print an error message
    cout << "Job with ID " << job_id << " not found in the queue." << endl;
}


    // Change job values operation
// Change job values operation
// Change job values operation
void changeJobValues(int job_id, int field_index, int new_value) {
    QueueNode* current = front; // Start from the front of the queue
    bool jobFound = false;      // A flag to track if the job is found

    // Traverse the queue to find the job with the given ID
    while (current) {
        if (current->jobPointer->job_id == job_id) {
            jobFound = true; // Job is found, update the flag

            // Modify the specific field based on field_index
            switch (field_index) {
                case 1: 
                    current->jobPointer->priority = new_value; 
                    cout << "Changed Job ID " << job_id << " field " << field_index << " to " << new_value << ":\n";
                    break;
                case 2: 
                    current->jobPointer->job_type = new_value; 
                    cout << "Changed Job ID " << job_id << " field " << field_index << " to " << new_value << ":\n";
                    break;
                case 3: 
                    current->jobPointer->cpu_time_consumed = new_value; 
                    cout << "Changed Job ID " << job_id << " field " << field_index << " to " << new_value << ":\n";
                    break;
                case 4: 
                    current->jobPointer->memory_consumed = new_value; 
                    cout << "Changed Job ID " << job_id << " field " << field_index << " to " << new_value << ":\n";
                    break;
                default: 
                    cout << "Invalid field index!" << endl;
                    return; // Stop execution if an invalid field is provided
            }

            // Display the updated job
            current->jobPointer->display();

            // After updating the field, show the queue state
            cout << "Jobs after changing field:" << endl;
            display(); // Display the queue after change
            return; // Exit the function once the change is made
        }
        current = current->next; // Move to the next node in the queue
    }

    // If the job wasn't found, print the error message
    if (!jobFound) {
        cout << "Job with ID " << job_id << " not found in the queue." << endl;
    }
}


    

// Promote operation
void promote(int job_id, int positions) {
    QueueNode* current = front;
    QueueNode* previous = nullptr;
    int index = 0;

    // Find the job with the given ID
    while (current) {
        if (current->jobPointer->job_id == job_id) {
            if (previous == nullptr) {
                front = front->next;
            } else {
                previous->next = current->next;
            }

            if (current == rear) {
                rear = previous;
            }

            size--;

            // Calculate the new position
            int newPosition = max(0, index - positions);
            QueueNode* temp = front;
            QueueNode* prevNode = nullptr;

            // Find the position where the job should be reinserted
            for (int i = 0; i < newPosition && temp != nullptr; ++i) {
                prevNode = temp;
                temp = temp->next;
            }

            // Insert the job at the new position
            if (prevNode == nullptr) {
                current->next = front;
                front = current;
            } else {
                current->next = prevNode->next;
                prevNode->next = current;
            }

            if (current->next == nullptr) {
                rear = current;
            }

            size++;

            // Output the promoted job details
            cout << "Promoted Job ID " << job_id << " by " << positions << " Position(s):" << endl;
            current->jobPointer->display();

            return;
        }
        previous = current;
        current = current->next;
        index++;
    }
    cout << "Job with ID " << job_id << " not found." << endl;
    }



    // Reorder operation
   void reorder(int attribute) {
    // If the queue is empty or has only one element, nothing to reorder
    if (front == nullptr || front->next == nullptr) {
        return;
    }

    // Bubble sort implementation based on the attribute chosen
    bool swapped;
    QueueNode* current;
    QueueNode* last = nullptr;

    do {
        swapped = false;
        current = front;

        while (current->next != last) {
            bool condition = false;

            switch (attribute) {
                case 1: // Reorder by Job ID
                    condition = current->jobPointer->job_id > current->next->jobPointer->job_id;
                    break;
                case 2: // Reorder by Priority
                    condition = current->jobPointer->priority > current->next->jobPointer->priority;
                    break;
                case 3: // Reorder by Job Type
                    condition = current->jobPointer->job_type > current->next->jobPointer->job_type;
                    break;
                case 4: // Reorder by CPU Time Consumed
                    condition = current->jobPointer->cpu_time_consumed > current->next->jobPointer->cpu_time_consumed;
                    break;
                case 5: // Reorder by Memory Consumed
                    condition = current->jobPointer->memory_consumed > current->next->jobPointer->memory_consumed;
                    break;
                default:
                    cout << "Invalid attribute for reorder." << endl;
                    return;
            }

            if (condition) {
                // Swap the jobs between two nodes
                CPUJob* tempJob = current->jobPointer;
                current->jobPointer = current->next->jobPointer;
                current->next->jobPointer = tempJob;
                swapped = true;
            }

            current = current->next;
        }

        last = current;
    } while (swapped);
}




    // Display operation
    void display() {
        QueueNode* temp = front; // Display all jobs in the queue
        while (temp) { // Display all jobs in the queue
            temp->jobPointer->display(); // Display the job details
            temp = temp->next;
        }
    }

    // Count operation
    int count() const {
        return size;
    }

    // List jobs in sorted order of job IDs
    void listJobs() {
    updatePointers();  // Ensure the jobs are sorted by job ID before listing them
    for (int i = 0; i < size; ++i) {
        NodePtrs[i]->jobPointer->display();  // Display the job details in sorted order
    }
}


private:
    // Helper method to update the sorted array of pointers
    void updatePointers() {
        
    QueueNode* temp = front;
    int index = 0;

    while (temp) {
        NodePtrs[index++] = temp;
        temp = temp->next;
    }

    // Sort the NodePtrs array by job ID
    for (int i = 0; i < size - 1; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (NodePtrs[i]->jobPointer->job_id > NodePtrs[j]->jobPointer->job_id) {
                QueueNode* tempNode = NodePtrs[i];
                NodePtrs[i] = NodePtrs[j];
                NodePtrs[j] = tempNode;
            }
        }
    }
    }
};

// Main function
int main() {
    int n; // Number of commands
    cin >> n; // Read the number of commands

    // Instantiate a NovelQueue for CPUJob pointers
    NovelQueue* myNovelQueue = new NovelQueue(n);

    char command; // Variable to store the command type
    // Variables for job attributes
    int job_id, priority, job_type, cpu_time_consumed, memory_consumed;
    // Variables for modifying a job
    int new_priority, new_job_type, new_cpu_time_consumed, new_memory_consumed;
    int field_index, new_value;
    // Variable for the number of positions in the 'Promote' command
    int positions;
    int attribute_index; // Variable for the 'Reorder' command

    for (int i = 0; i < n; ++i) {
        cin >> command; // Read the command type
        switch (command) {
            case 'A': { // Add a job (enqueue)
                cin >> job_id >> priority >> job_type >> cpu_time_consumed >> memory_consumed;
                CPUJob* job = new CPUJob(job_id, priority, job_type, cpu_time_consumed, memory_consumed);
                myNovelQueue->Add(job);  // Call the Add function
                break;
            }
            case 'R': { // Remove a job (dequeue)
                CPUJob* removedJob = myNovelQueue->Remove();
                if (removedJob != nullptr) {
                    cout << "Dequeued Job: " << endl; //For testing
                    removedJob->display();
                    delete removedJob;
                    cout << "Jobs after dequeue:" << endl; //For testing
                    myNovelQueue->display();
                } else {
                    cout << "No job to dequeue!" << endl; //For testing
                }
                break;
            }
            case 'M': { // Modify a job
                cin >> job_id >> new_priority >> new_job_type >> new_cpu_time_consumed >> new_memory_consumed;
                myNovelQueue->modify(job_id, new_priority, new_job_type, new_cpu_time_consumed, new_memory_consumed);
                break;
            }
            case 'C': { // Change a job value
                cin >> job_id >> field_index >> new_value;
                myNovelQueue->changeJobValues(job_id, field_index, new_value);
                break;
            }
            case 'P': { // Promote a job
                cin >> job_id >> positions;
                myNovelQueue->promote(job_id, positions);
                cout << "Jobs after promotion:" << endl;
                myNovelQueue->display(); // Display the queue after promotion
                break;
            }
            case 'O': { // Reorder the queue
                int attribute;
                cin >> attribute;
                myNovelQueue->reorder(attribute);
                cout << "Reordered Queue by attribute " << attribute << ":" << endl;
                myNovelQueue->display(); // Display the queue after reordering
                break;
            }
            case 'D': { // Display the queue
                cout << "Displaying all jobs in the queue:" << endl;
                myNovelQueue->display();
                break;
            }
            case 'N': { // Count the number of jobs
                cout << "Number of elements in the queue: " << myNovelQueue->count() << endl;
                break;
            }
            case 'L': { // List the job IDs
                cout << "List of jobs sorted by job IDs:" << endl;
                myNovelQueue->listJobs();
                break;
            }
            default:
                cout << "Invalid command!" << endl;
        }
    }

    delete myNovelQueue; // Clean up the NovelQueue after all operations
    return 0;
};