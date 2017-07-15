#include<iostream>
#include <string>
#include <sstream>

using namespace std;


struct Heap {
	int *arr;
	int size;
	int pos;
};

void init(Heap& h, int size) {
	h.arr = new int[size];
	h.pos = 0;
	h.size = size;
}

void heapAdjustment(Heap &h) {
/*	int last = h.pos - 1;
	int parent = last / 2;
	for (int i = last / 2; i > 0; i--) {
		int child = 2 * parent;
		while (child <= last) {
			if (child + 1 <= last && h.arr[child + 1] > h.arr[child])
				child++;
			if (h.arr[child] > h.arr[parent]) {
				int temp = h.arr[child];
				h.arr[child] = h.arr[parent];
				h.arr[parent] = temp;
			}
			parent = child;
			child = 2 * parent;
		}

	}*/




	
	int a, child, temp;
	for (a = 0; a <= (h.pos-1)/2; a++) {
		int parent = a;
		while (parent >= 0) {
			child = 2 * parent + 1;

			if (h.arr[child] > h.arr[parent] && h.arr[child] >= h.arr[child + 1] && child < h.pos) {
				temp = h.arr[child];
				h.arr[child] = h.arr[parent];
				h.arr[parent] = temp;
			}
			if (h.arr[child + 1] > h.arr[parent] && child + 1 < h.pos) {
				temp = h.arr[child + 1];
				h.arr[child + 1] = h.arr[parent];
				h.arr[parent] = temp;
			}
			/*for (int i = 0; i < h.pos; i++)
				cout << h.arr[i] << ",";
			cout << endl;*/	
			parent--;
		}
	} 
}

void loadAndMakeHeap(Heap &h, int howMany) {
	int number = 0, index = 0;
	string str;
	if (howMany <= h.size) 
		h.pos = h.pos + howMany;
	else h.pos = h.size;

	getline(cin, str);
	for (int i = 0; i < str.length(); i++) {
		if (isdigit(str[i])) {
			number *= 10;
			number += ((int)str[i] - '0');
		}
		else {
			h.arr[index++] = number;
			number = 0;
		}
	}
	h.arr[index] = number;
}


void add(Heap &h, int value) {
	if (h.pos < h.size) {
		h.arr[h.pos] = value;
		h.pos++;

		int parent = (h.pos / 2) - 1;
		int child = h.pos - 1;
		while (true) {
			if (h.arr[child] > h.arr[parent]) {
				int temp = h.arr[parent];
				h.arr[parent] = h.arr[child];
				h.arr[child] = temp;
			}
			if (parent == 0)
				break;
			child = parent;
			parent = (child / 2);
			cout << child << "," << parent << endl;
			
		}

	}
	else cout << "Imposibruuu!" << endl;
}

void makeSorted(Heap& h) {
	int pos = h.pos - 1;
	for (pos; pos >= 0.; pos--) {
		int max = h.arr[0];
		h.arr[0] = h.arr[pos];
		h.arr[pos] = max;
		//----------------------------------------------------------
		int a, child, temp;
		for (a = 0; a < pos / 2; a++) {
			int parent = a;
			while (parent >= 0) {
				child = 2 * parent;

				if (h.arr[child] > h.arr[parent]) {
					temp = h.arr[child];
					h.arr[child] = h.arr[parent];
					h.arr[parent] = temp;
				}
				if (h.arr[child + 1] > h.arr[parent] && child + 1 <= pos) {
					temp = h.arr[child + 1];
					h.arr[child + 1] = h.arr[parent];
					h.arr[parent] = temp;
				}
				parent--;
			}
		}
	/*	for (int i = 0; i < h.pos; i++)
			cout << h.arr[i] << ",";
		cout << endl; */
		//---------------------------------------------------------------
	}
}

void show(Heap& h) {
	for (int i = 0; i<h.pos; i++)
	{
		cout << h.arr[i] << ",";
	}
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
	Heap *heap = NULL;
	int currentH = 0;
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

		// zero-argument command
		if (isCommand(command, "HA")) {
			cout << "END OF EXECUTION" << endl;
			break;
		}

		if (isCommand(command, "SH")) //*
		{
			show(heap[currentH]);
			continue;
		}

		if (isCommand(command, "MS")) //*
		{
			makeSorted(heap[currentH]);
			continue;
		}

		// read next argument, one int value
		stream >> value;

		if (isCommand(command, "IN")) //*
		{
			init(heap[currentH], value);
			continue;
		}

		if (isCommand(command, "LD"))
		{
			loadAndMakeHeap(heap[currentH], value);
			heapAdjustment(heap[currentH]);
			continue;
		}
		
		if (isCommand(command, "MS"))
		{
			loadAndMakeHeap(heap[currentH], value);
			makeSorted(heap[currentH]);
			continue;
		}

		if (isCommand(command, "AD"))
		{
			add(heap[currentH], value);
			continue;
		}

		if (isCommand(command, "CH"))
		{
			currentH = value;
			continue;
		}

		if (isCommand(command, "GO"))
		{
			heap = new Heap[value];
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
	}
	return 0;
}
