#include <iostream>
#include <stdlib.h> 
#define LIMIT 100 // Specifying the maximum limit of the queue
using namespace std;

/* Global declaration of variables */
int queue[LIMIT]; // Array implementation of queue
int front, rear; // To insert and delete the data elements in the queue respectively
int i; // To traverse the loop to while displaying the stack
int choice; // To choose either of the 3 stack operations
void insert(); // Function used to insert an element into the queue
void delet(); // Function used to delete an element from the queue
void display(); // Function used to display all the elements in the queue according to FIFO rule

int main()
{
	cout << "Welcome to DataFlair tutorials!" << endl << endl;
	cout << "ARRAY IMPLEMENTATION OF QUEUES " << endl << endl;;
	front = rear = -1; // Initializing front and rear to -1 indicates that it is empty
	do
	{

		cout << "1. Insert\n2. Delete\n3. Display\n4. Exit\n\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			insert();
			break;
		case 2:
			delet();
			break;
		case 3:
			display();
			break;
		case 4:
			exit(0);
			break;
		default:
			printf("Sorry, invalid choice!\n");
			break;
		}
	} while (choice != 4);
	return 0;
}
void insert()
{
	int element;
	if (rear == LIMIT - 1)
		cout << "Queue Overflow\n";
	else
	{
		if (front == -1)
			front = 0;
		cout << "Enter the element to be inserted in the queue: ";
		cin >> element;
		rear++;
		queue[rear] = element;
	}
}
void delet()
{
	if (front == -1 || front > rear)
	{
		cout << "Queue Underflow \n";
	}
	else
	{
		cout << "The deleted element in the queue is: " << queue[front] << endl;
		front++;
	}
}
void display()
{
	int i;
	if (front == -1)
	{
		cout << "Queue underflow\n";
	}
	else
	{
		cout << "The elements of the queue are:\n" << endl;
		for (i = front; i <= rear; i++)
			cout << queue[i] << endl;
	}
}