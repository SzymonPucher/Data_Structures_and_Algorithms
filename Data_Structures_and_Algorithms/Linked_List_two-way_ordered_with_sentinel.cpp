#include<iostream>
#include <string>
#include <sstream>

using namespace std;


struct Element {
	int key;
	int value;
};

struct ElementLL {
	Element elem;
	ElementLL *next, *prev;
};

// Two-way ordered cycled list with sentinel
struct List2W {
	ElementLL *sentinel;
};

void init(List2W& l) {
	l.sentinel = new ElementLL();
	l.sentinel->next = l.sentinel;
	l.sentinel->prev = l.sentinel;
}

void insertElem(List2W & l, Element elem) {
	ElementLL *sent = l.sentinel;
	ElementLL *newe = new ElementLL;
	ElementLL *srch = l.sentinel->next;
	newe->elem.key = elem.key;
	newe->elem.value = elem.value;

	if (sent->next == sent) {
		newe->next = sent;
		newe->prev = sent;
		sent->next = newe;
		sent->prev = newe;
	}
	else {
		while (srch->elem.key <= newe->elem.key && srch != sent)
			srch = srch->next;
		newe->next = srch;
		newe->prev = srch->prev;
		newe->next->prev = newe;
		newe->prev->next = newe;
	}
}

bool findKey(List2W & l, int key, Element &elem) {
	ElementLL *srch = l.sentinel->next;
	ElementLL *sent = l.sentinel;
	while (srch != sent) {
		if (srch->elem.key == key) {
			elem = srch->elem;
			return true;
		}
		srch = srch->next;
	}
	return false;
}

void removeAllKeys(List2W& l, int key) {
	ElementLL *srch = l.sentinel->next;
	ElementLL *sent = l.sentinel;
	ElementLL *temp;
	while (srch != sent) {
		if (srch->elem.key == key) {
			temp = srch;
			srch = srch->next;
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			delete temp;
			continue;
		}
		srch = srch->next;
	}
}

void showListFromHead(List2W& l) {
	ElementLL *srch = l.sentinel->next;
	ElementLL *sent = l.sentinel;
	while (srch != sent) {
		cout << srch->elem.key << "(" << srch->elem.value << "),";
		srch = srch->next;
	}
	cout << endl;
}

void showListFromTail(List2W& l) {
	ElementLL *srch = l.sentinel->prev;
	ElementLL *sent = l.sentinel;
	while (srch != sent) {
		cout << srch->elem.key << "(" << srch->elem.value << "),";
		srch = srch->prev;
	}
	cout << endl;
}

void clearList(List2W& l) {
	ElementLL *srch = l.sentinel->next;
	ElementLL *sent = l.sentinel;
	ElementLL *temp;
	while (srch != sent) {
		temp = srch;
		srch = srch->next;
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		delete temp;
	}
}

void makeUnique(List2W& l) {
	ElementLL *srch = l.sentinel->next;
	ElementLL *sent = l.sentinel;
	ElementLL *temp;
	if (srch == sent)
		return;

	while (srch != sent) {
		if (srch->elem.key == srch->next->elem.key) {
			temp = srch->next;
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			delete temp;
			srch = srch->next;
			continue;
		}
		srch = srch->next;
	}
}

void largestSegDifferent(List2W& l) {
	ElementLL *srch = l.sentinel->next;
	ElementLL *sent = l.sentinel;
	int count = 1, a = 0;
	
	if (sent->next == sent)
		count = 0;

	while (srch != sent) {
		if (srch->elem.key != srch->next->elem.key && srch->next != sent) {
			count++;
		}
		if (srch->elem.key != srch->prev->elem.key && srch->next == sent && srch->prev != sent)
			count++;

		if (count > a) {
			a = count;
			count = 1;
		}

		srch = srch->next;
	}
	cout << a << endl;
	
}

void addList(List2W& l1, List2W& l2) {
	if (l1.sentinel != l2.sentinel && l2.sentinel != l2.sentinel->next) {
		ElementLL *srch1 = l1.sentinel->next;
		ElementLL *sent1 = l1.sentinel;
		ElementLL *srch2 = l2.sentinel->next;
		ElementLL *sent2 = l2.sentinel;
		ElementLL *temp;

		if (sent1 == sent1->next) {
			sent1->next = sent2->next;
			sent1->prev = sent2->prev;
			sent1->next->prev = sent1;
			sent1->prev->next = sent1;
			sent2->next = sent2;
			sent2->prev = sent2;
		}
		else {
			while (srch2 != sent2) {
				temp = srch2;
				srch2 = srch2->next;
				while (temp->elem.key >= srch1->elem.key && srch1 != sent1)
					srch1 = srch1->next;
				temp->next = srch1;
				temp->prev = srch1->prev;
				temp->next->prev = temp;
				temp->prev->next = temp;
			}
			sent2->next = sent2;
			sent2->prev = sent2;
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
	List2W *list = NULL;
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

		// zero-argument command
		if (isCommand(command, "HA")) {
			cout << "END OF EXECUTION" << endl;
			break;
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

		if (isCommand(command, "MU")) //*
		{
			makeUnique(list[currentL]);
			continue;
		}

		if (isCommand(command, "LD")) //*
		{
			largestSegDifferent(list[currentL]);
			continue;
		}

		if (isCommand(command, "IN")) //*
		{
			init(list[currentL]);
			continue;
		}

		// read next argument, one int value
		stream >> value;

		if (isCommand(command, "FK"))
		{
			Element elem;
			bool ret = findKey(list[currentL], value, elem);
			if (ret)
				cout << elem.key << '(' << elem.value << ')' << endl;
			else
				cout << "false" << endl;
			continue;
		}

		if (isCommand(command, "RK"))
		{
			removeAllKeys(list[currentL], value);
			continue;
		}

		if (isCommand(command, "CH"))
		{
			currentL = value;
			continue;
		}

		if (isCommand(command, "IE"))
		{
			int variable2;
			stream >> variable2;
			Element elem;
			elem.key = value;
			elem.value = variable2;
			insertElem(list[currentL], elem);
			continue;
		}

		if (isCommand(command, "GO"))
		{
			list = new List2W[value];
			continue;
		}

		if (isCommand(command, "AD"))
		{
			addList(list[currentL], list[value]);
			continue;
		}
		cout << "wrong argument in test: " << command << endl;
	}
	return 0;
}
