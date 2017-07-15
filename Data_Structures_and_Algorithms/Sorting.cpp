#include<iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

void showArray(int array[], int size) {
	for (int i = 0; i < size; i++)
		cout << array[i] << ",";
	cout << endl;
}

void insertSort(int array[], int size) {

	int state, srch, val, slide;
	for (state = size - 2; state >= 0; state--) {
		srch = size - 1;
		val = array[state];
		while (srch > state && array[srch] > array[state])
			srch--;
		for (slide = state; slide < srch; slide++)
			array[slide] = array[slide + 1];
		array[srch] = val;

		for (int i = 0; i < size; i++)
			cout << array[i] << ",";
		cout << endl;
	}
}

void bubbleSort(int array[], int size) {

	int state, pos, val;
	for (state = 0; state < size - 1; state++) {
		for (pos = size - 1; pos > 0; pos--) {
			if (array[pos - 1]>array[pos]) {
				val = array[pos - 1];
				array[pos - 1] = array[pos];
				array[pos] = val;
			}
		}

		for (int i = 0; i < size; i++)
			cout << array[i] << ",";
		cout << endl;
	}
}

void mergeSortIter(int array[], int size) {
	
	int state, srch, val, slide, x, m = 2, r;
	while(m < 2 * size) {
		x = m - 1;
		while (x < size) {
			for (state = x; state >= x - m + 1; state--) {
				srch = x;
				val = array[state];
				while (srch > state && array[srch] > array[state])
					srch--;
				for (slide = state; slide < srch; slide++)
					array[slide] = array[slide + 1];
				array[srch] = val;
			}
			x += m;
		}

		r = size % m;
		if (r != 0) {
			for (state = size - 1; state >= size - r; state--) {
				srch = size - 1;
				val = array[state];
				while (srch > state && array[srch] > array[state])
					srch--;
				for (slide = state; slide < srch; slide++)
					array[slide] = array[slide + 1];
				array[srch] = val;
			}
		}
		m *= 2;
		for (int i = 0; i < size; i++)
			cout << array[i] << ",";
		cout << endl;
	}
}

int * loadArray(int size) {
	int *array = new int[size];
	for (int i = 0; i < size; i++)
		cin >> array[i];
	return array;
}

bool isCommand(const string command, const char *mnemonic) {
	return command == mnemonic;
}

int main() {
	string line;
	string command;
	int size = 0;
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

		// read next argument, one int size
		stream >> size;

		// one-argument command
		if (isCommand(command, "HA")) {
			cout << "END OF EXECUTION" << endl;
			break;
		}

		if (isCommand(command, "IS")) //*
		{
			int *arr = loadArray(size);
			showArray(arr, size);
			insertSort(arr, size);
			continue;
		}

		if (isCommand(command, "BS")) //*
		{
			int *arr = loadArray(size);
			showArray(arr, size);
			bubbleSort(arr, size);
			continue;
		}

		if (isCommand(command, "MI")) //*
		{
			int *arr = loadArray(size);
			showArray(arr, size);
			mergeSortIter(arr, size);
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
	}
	return 0;
}
