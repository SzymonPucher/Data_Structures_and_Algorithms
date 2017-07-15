#include <iostream>
#include <string>
#include <sstream>


using namespace std;

// Two-way unordered cycled list without sentinel
struct Element {
	int key;
	Element *next;
	Element *previous;
};

struct List2W {
	Element *head;
};

void init(List2W& l) {
	l.head = new Element;
	l.head = NULL;
}

void insertHead(List2W& l, int x) {
	Element *nowy = new Element;
	Element *p = l.head;
	nowy->key = x;
	if (p == NULL) {
		nowy->next = nowy;
		nowy->previous = nowy;
	}
	else {
		nowy->next = l.head;
		nowy->previous = nowy->next->previous;
		nowy->previous->next = nowy;
		nowy->next->previous = nowy;
	}
	l.head = nowy;
}

bool deleteHead(List2W& l, int &value) {
	Element *p = l.head;
	if (p == NULL) 
		return false;
	Element *temp;
	temp = l.head;
	value = temp->key;
	if (l.head == p->next)
		l.head = NULL;
	else {
		p->next->previous = p->previous;
		p->previous->next = p->next;
		l.head = p->next;
	}
	delete temp;
	return true;
}

void insertTail(List2W& l, int x) {
	Element *nowy = new Element;
	Element *p = l.head;
	nowy->key = x;
	if (p == NULL) {
		nowy->next = nowy;
		nowy->previous = nowy;
		l.head = nowy;
	}
	else {
		p = p->previous;
		nowy->next = p->next;
		nowy->previous = p;
		p->next = nowy;
		nowy->next->previous = nowy;
	}
}

bool deleteTail(List2W& l, int &value) {
	Element *p = l.head;
	if (p == NULL) return false;
	p = p->previous;
	Element *temp;
	temp = p;
	value = temp->key;
	if (l.head == p)
		l.head = NULL;
	else
	{
		p->next->previous = p->previous;
		p->previous->next = p->next;
	}
	delete temp;
	return true;
}

int findValue(List2W& l, int value) {
	Element *p = l.head;
	int counter = 0;
	if (p != NULL)
		while (true)
		{
			if (p->key == value)
				return counter;
			p = p->next;
			if (p == l.head)
				break;
			counter++;
		}
	return -1;
}

void removeAllValue(List2W& l, int value) {
	if (l.head != NULL) {
		bool isBreak = true;
		Element *p = l.head;
		Element *temp;
		if (p != NULL)
			while (true)
			{
				if (p->key == value) {
					temp = p;
					if (p == l.head) {
						if (p->next == p) {
							l.head = NULL;
							delete p;
							break;
						}
						else {
							l.head = p->next;
							isBreak = false;
						}
					}

					p->next->previous = p->previous;
					p->previous->next = p->next;
					p = p->next;
					delete temp;
				}
				else
				{
					p = p->next;
				}
				if (p == l.head && isBreak)
					break;
				else
					isBreak = true;
			}
	}
}

void showListFromHead(List2W& l) {
	Element *p = l.head;
	if (p != NULL)
		while (true)
		{
			cout << p->key << ",";
			p = p->next;
			if (p == l.head) break;
		}
	cout << endl;
}

void showListFromTail(List2W& l) {
	Element *p = l.head;
	if (p != NULL)
	{
		p = p->previous;
		while (true)
		{
			cout << p->key << ",";
			if (p == l.head) break;
			p = p->previous;
		}
	}
	cout << endl;
}

void clearList(List2W& l) {
	if (l.head != NULL)
	{
		Element *p = l.head;
		int v;
		while (p != NULL)
		{
			deleteHead(l, v);
			if (l.head->next == l.head)
			{
				deleteHead(l, v);
				break;
			}
			p = p->next;
		}
	}
}

void addList(List2W& l1, List2W& l2) {
	if (l1.head == NULL)
	{
		l1 = l2;
		l2.head = NULL;
	}
	else if (l2.head == NULL)
	{
		return;
	}
	else if (l1.head == l2.head)
	{
		return;
	}
	else
	{
		Element *last1 = l1.head->previous;
		Element *last2 = l2.head->previous;
		last1->next = l2.head;
		l2.head->previous = last1;
		last2->next = l1.head;
		l1.head->previous = last2;

		l2.head = NULL;
	}
}

void removeOddPos(List2W& l) {
	if (l.head != NULL) {
		bool isBreak = true;
		Element *p = l.head;
		Element *temp;

		p->next->previous = p->previous;
		p->previous->next = p->next;
		l.head = p->next;

		if (p != NULL)
			while (true)
			{
				if (l.head == NULL)
					break;
				temp = p;

				p->next->previous = p->previous;
				p->previous->next = p->next;
				p = p->next;
				p = p->next;
				delete temp;

				if (p == l.head && isBreak)
					break;
				else
					isBreak = true;
			}
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
	List2W *list;
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
		// additional
		
		// zero-argument command
		if (isCommand(command, "DH")) //*
		{
			int retValue;
			bool retBool = deleteHead(list[currentL], retValue);
			if (retBool) {
				cout << retValue << endl;
			}
			else {
				showBool(retBool);
			}
			continue;
		}
		if (isCommand(command, "DT")) //*
		{
			int retValue;
			bool retBool = deleteTail(list[currentL], retValue);
			if (retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
		}

		if (isCommand(command, "SH")) //*
		{
			showListFromHead(list[currentL]);
			continue;
		}

		if (isCommand(command, "ST")) //*
		{
			showListFromTail(list[currentL]);
			continue;
		}

		if (isCommand(command, "CL")) //*
		{
			clearList(list[currentL]);
			continue;
		}

		if (isCommand(command, "IN")) //*
		{
			init(list[currentL]);
			continue;
		}

		// read next argument, one int value
		stream >> value;

		if (isCommand(command, "FV")) //*
		{
			int ret;
			ret = findValue(list[currentL], value);
			cout << ret << endl;
			continue;
		}

		if (isCommand(command, "RV")) //*
		{
			removeAllValue(list[currentL], value);
			continue;
		}

		if (isCommand(command, "RO")) //*
		{
			removeOddPos(list[currentL]);
			continue;
		}


		if (isCommand(command, "AD")) //*
		{
			addList(list[currentL], list[value]);
			continue;
		}

		if (isCommand(command, "CH")) //*
		{
			currentL = value;
			continue;
		}

		if (isCommand(command, "IH")) //*
		{
			insertHead(list[currentL], value);
			continue;
		}

		if (isCommand(command, "IT")) //*
		{
			insertTail(list[currentL], value);
			continue;
		}

		if (isCommand(command, "GO")) //*
		{
			list = new List2W[value];
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
	}
}
