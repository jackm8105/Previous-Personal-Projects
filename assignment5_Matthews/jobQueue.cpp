#include "jobQueue.hpp"
#include <iostream>
#include <string>

using namespace std;

JobQueue::JobQueue()
{
	counter = 0;
	queueFront = 0;
	queueEnd = 0;
}

bool JobQueue::isEmpty()
{
	if(counter == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool JobQueue::isFull()
{
	if(counter == SIZE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void JobQueue::enqueue(std::string job)
{
	if(isFull())
	{
		cout << "Queue full, cannot add new job" << endl;
		return;
	}
	else if(isEmpty())
	{
		queue[queueEnd] = job;
		queue[queueFront] = job;
		counter++;
	}
	else
	{
		queueEnd = (queueEnd + 1) % SIZE;
		queue[queueEnd] = job;
		counter++;
	}
}


void JobQueue::dequeue()
{
	if(isEmpty())
	{
		cout << "Queue empty, cannot dequeue a job" << endl;
		return;
	}
	else
	{
		queueFront = (queueFront + 1) % SIZE;
		counter--;
	}
}

string JobQueue::peek()
{
	string fJob = "";
	if(isEmpty())
	{
		cout << "Queue empty, cannot peek" << endl;
	}
	else
	{
		fJob = queue[queueFront];
	}
	return fJob;
}

int JobQueue::queueSize()
{
	return counter;
}