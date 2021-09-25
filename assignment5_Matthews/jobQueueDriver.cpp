#include <iostream>
#include <string>
#include "jobQueue.hpp"
using namespace std;


void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
    cout << "1. Add jobs into the queue" << endl;
	cout << "2. Dispatch jobs from the queue" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}


int main(int argc, char const *argv[])
{
    JobQueue jQueue;
    menu();
	int option = 0;
	string op;

    getline(cin, op);
    option = stoi(op);

	while(option >= 1 && option <= 3)
    {        
		switch (option)
		{
			case 1:
			{
				cout << "Enter the number of jobs to be created" << endl;
				string numJobs_string;
				getline(cin, numJobs_string);
				int numJobs = stoi(numJobs_string);
                for(int i = 1; i <= numJobs; i++)
                {
                    cout << "Job" << i << ":" << endl;
                    string jobName;
                    getline(cin, jobName);
				    jQueue.enqueue(jobName);
                }
                break;
			}
			
			case 2:
			{
				cout << "Enter the number of jobs to be dispatched:" << endl;
                string numJobs_string;
				getline(cin, numJobs_string);
				int numJobs = stoi(numJobs_string);
                for(int i = 1; i <= numJobs; i++)
                {
                    cout << "Dispatched: " << jQueue.peek() << endl;
                    jQueue.dequeue();
                }
                break;
			}

			case 3:
			{
				cout << "The number of jobs in the queue: " << jQueue.queueSize() << endl;
                break;
			}
		}
        menu();
        getline(cin, op);
        option = stoi(op);
	}
}