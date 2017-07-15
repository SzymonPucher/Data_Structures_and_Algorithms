#include<iostream>
#include<string.h>
#include <string>
#include <sstream>

using namespace std;

struct Element {
	int key;
	Element *next;
};

struct List {
	Element *head;
	Element *tail;
};

void init(List& l) {
	l.head = new Element;
	l.head = NULL;
	l.tail = new Element;
	l.tail = NULL;
}

void insertHead(List& l, int x) {
	Element *newEl = new Element;
	newEl->key = x;
	newEl->next = l.head;  // {} [][][]
	l.head = newEl;
	if (l.head->next == NULL) {
		l.tail = l.head;
	}
}
void swapFirstLast(List& l) {
	if (l.head != NULL) {
		if (l.head == l.tail) {
			return;
		}
		Element *p = l.head;
		Element *p2 = l.head;

		while (p->next != l.tail) {
			p = p->next;
		}
		if (p->next == l.tail) {
			l.head = l.tail;
			l.tail = p2;
			p->next = l.tail;
			return;
		}
		l.tail->next = p2->next;
		l.head = l.tail;
		l.tail = p2;
		p->next = l.tail;
		l.tail->next = NULL;
		
	}
}

bool deleteHead(List& l, int &oldHead) {
	if (l.head != NULL) {
		Element *p = l.head;
		oldHead = p->key;
		if (l.head == l.tail) {
			l.head = NULL;
			l.tail = NULL;
			delete p;
			return true;
		}
		l.head = p->next;
		delete p;
		return true;
	}
	return false;
}



void insertTail(List& l, int x) {
	if (l.head == NULL) {
		insertHead(l, x);
		return;
	}
	Element *newEl = new Element;
	newEl->key = x;
	newEl->next = NULL;
	l.tail->next = newEl;
	l.tail = newEl;
}

bool deleteTail(List& l, int &oldTail) {
	if (l.head != NULL) {
		if (l.head == l.tail) {
			deleteHead(l, oldTail);
			return true;
		}
		oldTail = l.tail->key;
		Element *p = l.head;
		while (p->next != l.tail) {
			p = p->next;
		}
		p->next = NULL;
		l.tail = p;
		return true;
	}
	return false;
}

int findPosOfValue(List& l, int value) {
	if (l.head != NULL) {
		Element *p = l.head;
		int pos = 0;
		while (p->next != NULL && p->key != value) {
			p = p->next;
			pos++;
		}
		if (p->key == value)
			return pos;
		return -1;
	}
	return -1;
}

bool deleteValue(List& l, int value) {
	if (l.head != NULL) {
		Element *p = l.head;
		if (l.head->key == value) {
			deleteHead(l, value);
			return true;
		}
		while (p->next != NULL && p->next->key != value) {
			p = p->next;
		}
		if (p->next == l.tail) {
			deleteTail(l, value);
			return true;
		}
		if (p->next == NULL)
			return false;
		Element *temp = p->next;
		p->next = temp->next;
		delete temp;
		return true;
	}
	return false;
}
// additional
bool deleteValue_2(List& l, int value) {
	if (l.head != NULL) {
		Element *p = l.head;
		if (p->next == l.tail) {
			deleteTail(l, value);
			return true;
		}
		if (p->next == NULL)
			return false;
		Element *temp = p->next;
		p->next = temp->next;
		delete temp;
		return true;
	}
	return false;
}

bool atPosition(List& l, int pos, int &value) {
	if (l.head != NULL) {
		Element *p = l.head;
		value = 0;
		while (p != NULL && value != pos) {
			p = p->next;
			value++;
		}
		if (value == pos) {
			value = p->key;
			return true;
		}
		return false;
	}
	return false;
}

void showListFromHead(List& l) {
	if (l.head != NULL) {
		Element *p = l.head;
		while (p != NULL) {
			cout << p->key << ",";
			p = p->next;
		}
	}
	cout << endl;
}

void clearList(List& l) {
	if (l.head != NULL) {
		Element *p = l.head;
		while (p->next != NULL) {
			Element *temp = p;
			p = temp->next;
			l.head = p;
			delete temp;
		}
		l.head = NULL;
		l.tail = NULL;
		delete p;
	}
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
	List *list;
	int currentL = 0;
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
		if (isCommand(command, "DH"))
		{
			int retValue;
			bool retBool = deleteHead(list[currentL], retValue);
			if (retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
		}
		if (isCommand(command, "DT"))
		{
			int retValue;
			bool retBool = deleteTail(list[currentL], retValue);
			if (retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
		}

		if (isCommand(command, "SH"))
		{
			showListFromHead(list[currentL]);
			continue;
		}
		if (isCommand(command, "FL"))
		{
			swapFirstLast(list[currentL]);
			continue;
		}

		if (isCommand(command, "CL"))
		{
			clearList(list[currentL]);
			continue;
		}

		if (isCommand(command, "IN"))
		{
			init(list[currentL]);
			continue;
		}

		// read next argument, one int value
		stream >> value;

		if (isCommand(command, "FP"))
		{
			int ret;
			ret = findPosOfValue(list[currentL], value);
			cout << ret << endl;
			continue;
		}

		if (isCommand(command, "DV"))
		{
			showBool(deleteValue(list[currentL], value));
			continue;
		}

		if (isCommand(command, "DV2"))
		{
			showBool(deleteValue_2(list[currentL], value));
			continue;
		}

		if (isCommand(command, "AT"))
		{
			int retValue;
			bool retBool = atPosition(list[currentL], value, retValue);
			if (retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
		}

		if (isCommand(command, "CH"))
		{
			currentL = value;
			continue;
		}

		if (isCommand(command, "IH"))
		{
			insertHead(list[currentL], value);
			continue;
		}

		if (isCommand(command, "IT"))
		{
			insertTail(list[currentL], value);
			continue;
		}

		if (isCommand(command, "GO"))
		{
			list = new List[value];
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
	}
}