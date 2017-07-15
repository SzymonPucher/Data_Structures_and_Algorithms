#include<iostream>
#include<string.h>
#include <sstream>

using namespace std;

#define INFINITY 10000000

struct Graph {
	double** adjM;
	int size;
};

struct Element {
	int key;
	int value;
};

struct ElementLL {
	Element elem;
	ElementLL *next, *prev;
};


struct List2W {
	ElementLL *sentinel;
};

void insertEdge(Graph &g, int u, int v, double weight) {
	while (u == v) {
		cout << "Error: points to itself" << endl;
		cin >> u >> v >> weight;
		break;
	}
	while (u > g.size - 1) {
		cout << "Error: Out" << endl;
		cin >> u >> v >> weight;
	}
	while (v > g.size - 1) {
		cout << "Error: Out" << endl;
		cin >> u >> v >> weight;
	}
	g.adjM[u][v] = weight;
}

void loadGraph(Graph &g, int n, int m) {
	g.size = n;
	int u, v;
	double w;
	g.adjM = new double*[n];

	for (int i = 0; i < n; ++i)	//	creating adjM
		g.adjM[i] = new double[n];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j)
				g.adjM[i][i] = 0;	// filling main diagonal with 0
			else g.adjM[i][j] = INT_MAX;
		}
	}

	for (int i = 0; i < m; i++) {	// inputing m values (filling all edges)
		cin >> u >> v >> w;
		insertEdge(g, u, v, w);
	}
}

bool findEdge(Graph &g, int u, int v, double &weight) {
	if (g.adjM[u][v] != 0 && g.adjM[u][v] != INT_MAX) {
		if (u <= g.size - 1 && v <= g.size - 1) {
			weight = g.adjM[u][v];
			return true;
		}
	}
	else return false;
}

void showAsMatrix(Graph &g) {
	for (int i = 0; i < g.size; i++) {
		for (int j = 0; j < g.size; j++) {
			if (g.adjM[i][j] == INT_MAX)
				cout << "-" << ",";
			else cout << g.adjM[i][j] << ",";
		}
		cout << endl;
	}
}

void showAsArrayOfLists(Graph &g) {
	for (int i = 0; i < g.size; i++) {
		cout << i << ":";
		for (int j = 0; j < g.size; j++) {
			if (g.adjM[i][j] != 0 && g.adjM[i][j] != INT_MAX)
				cout << j << "(" << g.adjM[i][j] << ")" << ",";
		}
		cout << endl;
	}
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

int* SSSP(Graph &g, int s) {
	l.sentinel = new ElementLL();
	l.sentinel->next = l.sentinel;
	l.sentinel->prev = l.sentinel;


	for (int j = 0; j < g.size; j++) {
		if (g.adjM[s][j] != 0 && g.adjM[s][j] != INT_MAX) {

		}
	}
}

bool isCommand(const string command, const char *mnemonic) {
	return command == mnemonic;
}


int main() {
	string line;
	string command;
	Graph *graph = NULL;
	List2W *list = NULL;
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

		cout << "wrong argument in test: " << command << endl;
		return 1;
	}
}

