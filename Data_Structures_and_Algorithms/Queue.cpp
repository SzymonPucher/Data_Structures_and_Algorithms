#include <iostream>
#include <string.h>
#include <string>
#include <sstream>

using namespace std;

struct Queue {
	int *arr;
	int size;
	int begin;
	int end;
};

void init(Queue& queue, int size) {
	queue.begin = 0;
	queue.end = 0;
	queue.arr = new int[size + 1];
	queue.size = size;
}

bool isEmpty(Queue& queue) {
	if (queue.end == 0)
		return true;
	else
		return false;
}
bool isFull(Queue& queue) {
	if (queue.end == queue.size)
		return true;
	else
		return false;
}

bool enqueue(Queue& queue, int value) {
	if (isFull(queue))
		return false;
	queue.arr[queue.end] = value;
	queue.end++;
	return true;
}

bool dequeue(Queue& queue, int &value) {
	if (isEmpty(queue))
		return false;
	value = queue.arr[0];
	for (int i = 0; i < queue.size; i++)
		queue.arr[i] = queue.arr[i + 1];
	queue.end--;
	return true;
}
bool swapFirstSecond(Queue& queue, int &value) {
	if (isEmpty(queue))
		return false; 
	value = queue.arr[0];
	if (queue.end == 1)
		return true;
	queue.arr[0] = queue.arr[1];
	queue.arr[1] = value;
	return true;
}

bool dequeue_2nd_elem(Queue& queue, int &value) {
	if (isEmpty(queue))
		return false;
	value = queue.arr[1];
	for (int i = 1; i < queue.size; i++)
		queue.arr[i] = queue.arr[i + 1];
	queue.end--;
	return true;
}

void show(Queue& queue) {
	for (int i = 0; i < queue.end; i++)
		cout << queue.arr[i] << ",";
	cout << endl;
}

void showBool(bool val) {
	if (val)
		cout << "true" << endl;
	else
		cout << "false" << endl;
}

bool isCommand(const string command, const char *mnemonic) {
	return command == mnemonic;
}

int main() {
	string line;
	string command;
	Queue *queue = NULL;
	int currentQ = 0;
	int value;
	cout << "START" << endl;
	while (true) {
		getline(cin, line);
		std::stringstream stream(line);
		stream >> command;
		if (line == "" || command[0] == '#')
		{
			// ignore empty line and comment
			continue;
		}

		// copy line on output with exclamation mark
		cout << "!" << line << endl;;

		// change to uppercase
		command[0] = toupper(command[0]);
		command[1] = toupper(command[1]);

		if (isCommand(command, "HA")) {
			cout << "END OF EXECUTION" << endl;
			break;
		}

		// zero-argument command
		if (isCommand(command, "EM"))
		{
			showBool(isEmpty(queue[currentQ]));
			continue;
		}
		if (isCommand(command, "FU"))
		{
			showBool(isFull(queue[currentQ]));
			continue;
		}
		if (isCommand(command, "SH"))
		{
			show(queue[currentQ]);
			continue;
		}
		if (isCommand(command, "DE"))
		{
			int ret;
			bool retBool = dequeue(queue[currentQ], ret);
			if (!retBool)
				cout << "false" << endl;
			else
				cout << ret << endl;
			continue;
		}

		if (isCommand(command, "DE2"))
		{
			int ret;
			bool retBool = dequeue_2nd_elem(queue[currentQ], ret);
			if (!retBool)
				cout << "false" << endl;
			else
				cout << ret << endl;
			continue;
		}

		if (isCommand(command, "FS"))
		{
			int ret;
			bool retBool = swapFirstSecond(queue[currentQ], ret);
			if (!retBool)
				cout << "false" << endl;
			else
				cout << ret << endl;
			continue;
		}

		// read next argument, one int value
		stream >> value;

		if (isCommand(command, "GO"))
		{
			queue = new Queue[value];
			continue;
		}
		if (isCommand(command, "CH"))
		{
			currentQ = value;
			continue;
		}

		if (isCommand(command, "IN"))
		{
			init(queue[currentQ], value);
			continue;
		}

		if (isCommand(command, "EN"))
		{
			bool retBool = enqueue(queue[currentQ], value);
			showBool(retBool);
			continue;
		}
		cout << "wrong argument in test: " << command << endl;
	}
}