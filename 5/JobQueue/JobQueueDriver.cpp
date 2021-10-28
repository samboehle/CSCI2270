/****************************************************************/
/*                Job Queue Driver File                 */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "JobQueue.hpp"
#include <iostream>
#include <string>
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
    cout << "1. Add jobs into the queue" << endl;
	cout << "2. Dispatch jobs from the queue" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}
// Use getline for reading
JobQueue queue;
string s_input;
int input;
int main(int argc, char const *argv[])
{
	bool quit = false;

	while(!quit)
	{
		menu();
		cin >> input;

		switch(input)
		{
			case 1:
				{
					int x;
					string jobs;
					cout << "Enter the number of jobs to be created:" << endl;
					cin >> x;
					for (int i = 0; i < x; i++)
					{
						cout << "job" << i + 1 << ":" << endl;
						cin >> jobs;
						queue.enqueue(jobs);
					}
				}
				break;
			case 2:
				int y;
				cout << "Enter the number of jobs to be dispatched:" << endl;
				cin >> y;

				if(y > queue.queueSize())
				{
					for(int i = 0; i < y -1; i++)
					{
						cout << "Dispatched: " << queue.peek() << endl;
						queue.dequeue();
					}
					cout<< "No more jobs to be dispatched from queue" << endl;
					break;
				}
				else
				{
					for(int i = 0; i < y; i++)
					{
						cout << "Dispatched: " << queue.peek() << endl;
						queue.dequeue();
					}
					break;
				}
				break;
			case 3:
				cout << "Number of jobs in the queue:" << queue.queueSize() << endl;
				quit = true;
				break;
		}

	}
}
