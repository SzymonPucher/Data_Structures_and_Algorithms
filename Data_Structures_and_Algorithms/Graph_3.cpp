#include<iostream>
#include<string.h>
#include <sstream>
#include "list.h"
#include "Queue.h"

using namespace std;

#define INFINITY 10000000

static int time = 0;

struct Graph {
	list *arr;
	int size;
};


void insertEdge(Graph &g, int u, int v, double weight) {
	Element elem;
	elem.key = v;
	elem.value = weight;
	g.arr[u].insertElem(elem, u);
}

void loadGraph(Graph &g, int n, int m) {
	g.size = n;
	g.arr = new list[n];
	int u, v;
	double weight;
	for (int i = 0; i < m; i++) {
		cin >> u >> v >> weight;
		insertEdge(g, u, v, weight);
	}
}

bool findEdge(Graph &g, int u, int v, double &weight) {
	Element elem;
	if (g.arr[u].findKey(v, elem)) {
		weight = elem.value;
		return true;
	}
	return false;
}

void showAsMatrix(Graph &g) {
	for (int i = 0; i<g.size; i++) {
		for (int j = 0; j<g.size; j++) {
			Element elem;
			if (g.arr[i].findKey(j, elem))
				cout << elem.value << ",";
			else
				if (i == j)
					cout << "0,";
				else
					cout << "-,";
		}
		cout << endl;
	}
}

void showAsArrayOfLists(Graph &g) {
	for (int i = 0; i<g.size; i++) {
		cout << i << ": ";
		g.arr[i].showListFromHead();
	}
}

void BFS(Graph &g, int s) {
	Queue Q(g.size);
	for (int i = 0; i < g.size; i++) {
		g.arr[i].c = white;
		g.arr[i].t = 0;
		g.arr[i].parent = 0;
	}
	Q.enqueue(s);
	while (!Q.isEmpty()) {
		int u;
		Q.dequeue(u);
		int i = 0;
		while (i < g.size) {
			Element elem;
			if (g.arr[u].findKey(i, elem))
				if (g.arr[i].c == white) {
					g.arr[i].c = grey;
					g.arr[i].t = g.arr[u].t + 1;
					g.arr[i].parent = u;
					Q.enqueue(i);
				}
			i++;
		}
		g.arr[u].c = black;
	}
	cout << endl;
}

void printPath(Graph &g, int s, int v) {
	if (s == v)
		cout << s << ",";
	else if (g.arr[v].parent == NULL)
		cout << "no path from " << s << " to " << v << " exists";
	else {
		printPath(g, s, g.arr[v].parent);
		cout << v;
	}
}

void DFS_visit(Graph &g, int u) {
	g.arr[u].c = grey;
	time++;
	g.arr[u].t = time;
	cout << g.arr[u].sentinel->elem.key << ",";
	int i = 0;
	while (i < g.size) {
		Element elem;
		if (g.arr[u].findKey(i, elem))
			if (g.arr[i].c == white) {
				g.arr[i].parent = u;
				DFS_visit(g, i);
			}
		i++;
	}
	g.arr[u].c = black;
	g.arr[u].f = ++time;
}

void DFS(Graph &g, int s) {
	for (int i = 0; i < g.size; i++) {
		g.arr[i].c = white;
		g.arr[i].parent = NULL;
	}
	time = 0;
	DFS_visit(g, g.arr[s].sentinel->elem.key);
	cout << endl;
}

bool isCommand(const string command, const char *mnemonic) {
	return command == mnemonic;
}


int main() {
	string line;
	string command;
	Graph *graph = NULL;
	int currentT = 0;
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
		// zero-argument command
		if (isCommand(command, "SM"))
		{
			showAsMatrix(graph[currentT]);
			continue;
		}

		if (isCommand(command, "SA"))
		{
			showAsArrayOfLists(graph[currentT]);
			continue;
		}


		// read next argument, one int value
		stream >> value;

		if (isCommand(command, "LG"))
		{
			int m;
			stream >> m;
			loadGraph(graph[currentT], value, m);
			continue;
		}

		if (isCommand(command, "IE"))
		{
			int v;
			double w;
			stream >> v >> w;
			insertEdge(graph[currentT], value, v, w);
			continue;
		}

		if (isCommand(command, "FE"))
		{
			int v;
			stream >> v;
			double w;
			bool ret = findEdge(graph[currentT], value, v, w);

			if (ret)
				cout << w << endl;
			else
				cout << "false" << endl;
			continue;
		}


		if (isCommand(command, "CH"))
		{
			currentT = value;
			continue;
		}

		if (isCommand(command, "GO"))
		{
			graph = new Graph[value];
			continue;
		}

		if (isCommand(command, "BF"))
		{
			BFS(graph[currentT], value);
			continue;
		}

		if (isCommand(command, "DF"))
		{
			DFS(graph[currentT], value);
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
		return 1;
	}
}

