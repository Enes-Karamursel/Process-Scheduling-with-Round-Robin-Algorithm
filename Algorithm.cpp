#include <iostream>
#include <queue>
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;

struct Process
{
    int PID;        // PID is the id of the process
    int duration;   // duration is the CPU time required by the process
    int R1, R2, R3; // Resource requirements 
};

// Comparator for the priority queue based on process duration
struct CompareProcesses
{
    bool operator()(const Process &p1, const Process &p2)
    {
        return p1.duration > p2.duration;
    }
};

int main()
{
    int PID = 0;
    srand(time(0));

    int currentResources[] = {10, 10, 10}; // Initial resource availability
    priority_queue<Process, vector<Process>, CompareProcesses> readyQueue;
    queue<Process> runningQueue;

    // Get user input for process durations and generate random resource requirements
   for (int i = 0; i < 3; ++i) {
    while (true) {
        Process userProcess;
        cout << "Enter duration for process " << i + 1 << " (between 1 and 7 inclusive): ";
        cin >> userProcess.duration;

        if (userProcess.duration >= 1 && userProcess.duration <= 7) {
            // If a valid value is entered, proceed with the process
            userProcess.R1 = rand() % 7 + 1;
            userProcess.R2 = rand() % 7 + 1;
            userProcess.R3 = rand() % 7 + 1;

            userProcess.PID = PID + 1; // Assign PID to the process
            PID += 1;

            readyQueue.push(userProcess); // Add the process to the ready queue
            break; // Exit the loop and move to the next process
        } else {
            cout << "Invalid input! Please enter a value between 1 and 7." << endl;
            // If an invalid value is entered, prompt the user again within the loop
        }
    }
}


    for (int timeUnit = 1; timeUnit < 31; ++timeUnit)
    {

        // Check if both queues are empty, if so, break the loop
        if (readyQueue.empty() && runningQueue.empty())
        {
            break;
        }

        // Schedule processes from the ready queue to the running queue based on available resources
        while (!readyQueue.empty())
        {
            int size = readyQueue.size();
            for (int i = 0; i < size; i++)
            {

                Process currentProcess = readyQueue.top();
                if (currentProcess.R1 <= currentResources[0] && currentProcess.R2 <= currentResources[1] && currentProcess.R3 <= currentResources[2])
                {
                    runningQueue.push(currentProcess);
                    // Allocate resources to the running process
                    currentResources[0] -= currentProcess.R1;
                    currentResources[1] -= currentProcess.R2;
                    currentResources[2] -= currentProcess.R3;
                    readyQueue.pop(); // Remove the process from the ready queue
                }
            }
            break;
        }

        // Display the state at the beginning of each time unit
        if (timeUnit==1)
        {
            cout << endl;
            cout << "Time Unit: " << timeUnit << endl;

            cout << "Running Queue Content: ";
            queue<Process> tempQueue3 = runningQueue;

            while (!tempQueue3.empty())
            {
                cout << "P" << tempQueue3.front().PID << " ";
                tempQueue3.pop();
            }
            cout << endl;

            cout << "Ready Queue Content: ";
            priority_queue<Process, vector<Process>, CompareProcesses> tempQueue2 = readyQueue;

            while (!tempQueue2.empty())
            {
                cout << "P" << tempQueue2.top().PID << " ";
                tempQueue2.pop();
            }

            cout << endl;

            cout << "Available Resources: {" << 10 << ", " << 10 << ", " << 10 << "}" << endl;
            
            timeUnit++;

        }

        // Simulate running processes
        if (!runningQueue.empty())
        {
            Process &runningProcess = runningQueue.front();
            runningProcess.duration--;
            cout << endl;
            cout << "Time Unit: " << timeUnit << endl;

            cout << "Running Queue Content: ";
            queue<Process> tempQueue3 = runningQueue;

            while (!tempQueue3.empty())
            {
                cout << "P" << tempQueue3.front().PID << " ";
                tempQueue3.pop();
            }
            cout << endl;

            cout << "Ready Queue Content: ";
            priority_queue<Process, vector<Process>, CompareProcesses> tempQueue2 = readyQueue;

            while (!tempQueue2.empty())
            {
                cout << "P" << tempQueue2.top().PID << " ";
                tempQueue2.pop();
            }

            cout << endl;

            if (runningProcess.duration != 0)
                cout << "Available Resources: {" << currentResources[0] << ", " << currentResources[1] << ", " << currentResources[2] << "}" << endl;


            cout << "Recently Executed Process: P" << runningProcess.PID << ":" << runningProcess.duration << " - R1: " << runningProcess.R1 << " R2: " << runningProcess.R2 <<" R3: "<<runningProcess.R3 << endl;

            
            runningQueue.pop();
            if (runningProcess.duration == 0 && timeUnit!=30)
            {
                // Release resources and generate a new process
                cout << "Recently Finished Process: P" << runningProcess.PID << endl;
                currentResources[0] = currentResources[0] + runningProcess.R1;
                currentResources[1] = currentResources[1] + runningProcess.R2;
                currentResources[2] = currentResources[2] + runningProcess.R3;
                cout << "Available Resources: {" << currentResources[0] << ", " << currentResources[1] << ", " << currentResources[2] << "}" << endl;
                Process newProcess;
                newProcess.PID = PID + 1;
                PID += 1;
                newProcess.duration = rand() % 7 + 1;
                newProcess.R1 = rand() % 7 + 1;
                newProcess.R2 = rand() % 7 + 1;
                newProcess.R3 = rand() % 7 + 1;
                readyQueue.push(newProcess);
                timeUnit++;
                cout << endl;
                cout << "Time Unit: " << timeUnit << " - P" << newProcess.PID <<" is generated and added to queue." << endl;
                
            }
            
            else
            {
                runningQueue.push(runningProcess);
            }
            
        }

    }

    return 0;
}
