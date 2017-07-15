#include<iostream>
#include<string.h>
#include <sstream>

using namespace std;

#define INFINITY 10000000

struct Element {
	int key;
	double weight;
};

struct ElementLL {
	Element elem;
	ElementLL *next;
};

struct List2W {
	ElementLL *head;
};

struct Node
{
	int index;
	int color;
	int value;
	Node *parent;
};

struct Graph {
	List2W *graph;
	int size;
	double **matrix;
	Node **set;
};

void insertEdge(Graph &g, int u, int v, double weight) {
	if (u > g.size - 1)
	{
		cout << "VERTEX OUT OF BOUNDS! \n";
		return;
	}
	if (v > g.size - 1)
	{
		cout << "VERTEX OUT OF BOUNDS! \n";
		return;
	}
	if (u == v)
	{
		cout << "YOU SHALL NOT POINT TO SAME VERTEX! \n";
		return;
	}
	ElementLL *bufor;
	ElementLL *inserter = new ElementLL();
	inserter->elem.key = v;
	inserter->elem.weight = weight;

	if (g.graph[u].head == NULL)			// pusty wiersz, insert head
	{
		inserter->next = NULL;
		g.graph[u].head = inserter;
	}
	else
	{
		bufor = g.graph[u].head;
		if (bufor->elem.key > inserter->elem.key)
		{
			inserter->next = bufor;
			g.graph[u].head = inserter;
			return;
		}
		while (bufor->next != NULL)
		{
			if (bufor->elem.key == inserter->elem.key)
			{
				bufor->elem.weight = inserter->elem.weight;
				return;
			}
			if (bufor->next->elem.key == inserter->elem.key)
			{
				bufor->next->elem.weight = inserter->elem.weight;
				return;
			}
			if (bufor->next->elem.key > inserter->elem.key) break;
			bufor = bufor->next;
		}
		if (bufor->next == NULL)
		{
			inserter->next = NULL;
			bufor->next = inserter;
		}
		if (bufor->next->elem.key > inserter->elem.key)
		{
			inserter->next = bufor->next;
			bufor->next = inserter;
			return;
		}

	}
}

void insertEdge2(Graph &g, int u, int v, double weight)
{
	insertEdge(g, v, u, weight);
	if (u > g.size - 1)
	{
		cout << "VERTEX OUT OF BOUNDS! \n";
		return;
	}
	if (v > g.size - 1)
	{
		cout << "VERTEX OUT OF BOUNDS! \n";
		return;
	}
	if (u == v)
	{
		cout << "YOU SHALL NOT POINT TO SAME VERTEX! \n";
		return;
	}
	ElementLL *bufor;
	ElementLL *inserter = new ElementLL();
	inserter->elem.key = v;
	inserter->elem.weight = weight;

	if (g.graph[u].head == NULL)			// pusty wiersz, insert head
	{
		inserter->next = NULL;
		g.graph[u].head = inserter;
	}
	else
	{
		bufor = g.graph[u].head;
		if (bufor->elem.key > inserter->elem.key)
		{
			inserter->next = bufor;
			g.graph[u].head = inserter;
			return;
		}
		while (bufor->next != NULL)
		{
			if (bufor->elem.key == inserter->elem.key)
			{
				bufor->elem.weight = inserter->elem.weight;
				return;
			}
			if (bufor->next->elem.key == inserter->elem.key)
			{
				bufor->next->elem.weight = inserter->elem.weight;
				return;
			}
			if (bufor->next->elem.key > inserter->elem.key) break;
			bufor = bufor->next;
		}
		if (bufor->next == NULL)
		{
			inserter->next = NULL;
			bufor->next = inserter;
		}
		if (bufor->next->elem.key > inserter->elem.key)
		{
			inserter->next = bufor->next;
			bufor->next = inserter;
			return;
		}

	}
}

void loadGraph(Graph &g, int n, int m) {
	g.size = n;
	g.graph = new List2W[n];
	for (int i = 0; i < n; i++)
	{
		g.graph[i].head = NULL;
	}

	for (int i = 0; i < m; i++)
	{
		int start, end, weight;
		cin >> start;
		cin >> end;
		cin >> weight;
		insertEdge(g, start, end, weight);
	}
}

bool findEdge(Graph &g, int u, int v, double &weight) {
	ElementLL *bufor = g.graph[u].head;
	if (bufor == NULL) return false;
	if (bufor->elem.key == v)
	{
		weight = bufor->elem.weight;
		return true;
	}
	while (bufor->next != NULL)
	{
		if (bufor->next->elem.key == v)
		{
			weight = bufor->next->elem.weight;
			return true;
		}
		bufor = bufor->next;
	}

	return false;
}

void showAsMatrix(Graph &g) {
	ElementLL *bufor;
	g.matrix = new double*[g.size];
	for (int i = 0; i < g.size; ++i)
		g.matrix[i] = new double[g.size];

	for (int i = 0; i < g.size; i++)
	{
		for (int j = 0; j < g.size; j++)
		{
			if (i == j)
				g.matrix[i][j] = 0;
			else
				g.matrix[i][j] = -1;
		}
	}

	for (int i = 0; i < g.size; i++)
	{
		bufor = g.graph[i].head;
		if (bufor == NULL) continue;
		while (bufor->next != NULL)
		{
			g.matrix[i][bufor->elem.key] = bufor->elem.weight;
			bufor = bufor->next;

		}
		g.matrix[i][bufor->elem.key] = bufor->elem.weight;
	}
	// printing out

	for (int i = 0; i < g.size; i++)
	{
		for (int j = 0; j < g.size; j++)
		{
			if (g.matrix[i][j] == -1) cout << "-,";
			else cout << g.matrix[i][j] << ",";
		}
		cout << endl;
	}
}

void showAsArrayOfLists(Graph &g) {
	ElementLL *bufor;
	for (int i = 0; i < g.size; i++)
	{
		bufor = g.graph[i].head;
		cout << i << ":";
		while (bufor != NULL)
		{
			cout << bufor->elem.key << "(" << bufor->elem.weight << "),";
			bufor = bufor->next;
		}
		cout << endl;
	}
}

void BFSinside(Graph &g, int index, int value)
{

	g.set[index]->color = 2;
	//g.set[index]->value = value;
	cout << "BLACKENING " << index << "(" << g.set[index]->value << ")" << endl;//" AND SETTING ITS VALUE TO "<<value+1<<"\n";

	for (int i = 0; i < g.size; i++)
	{
		if (g.matrix[index][i] > 0)
		{

			cout << "FOUND A CONNECTION " << index << " - " << i;
			if (g.set[i]->parent == g.set[index]) { cout << ", BUT IT'S MY PARENT!" << endl; continue; }
			if (g.set[i]->color == 1) { cout << ", BUT ITS GREY!" << endl; continue; }
			if (g.set[i]->color == 2) { cout << ", BUT ITS BLACK!" << endl; continue; }
			cout << ", AND IM GOING IN!" << endl;
			g.set[i]->parent = g.set[index];
			g.set[i]->value = value + 1;
			g.set[i]->color = 1;

			//BFSinside(g,i,value+1);
		}
	}
}
void BFS(Graph &g, int start)
{
	g.set = new Node*[g.size];
	ElementLL *bufor;

	for (int i = 0; i < g.size; i++)
	{
		g.set[i] = NULL;
	}

	for (int i = 0; i < g.size; i++)
	{

		bufor = g.graph[i].head;
		while (bufor != NULL)
		{
			g.set[i] = new Node();
			g.set[i]->color = 0;
			g.set[i]->index = i;
			g.set[i]->parent = NULL;
			g.set[i]->value = INT_MAX;

			g.set[bufor->elem.key] = new Node();
			g.set[bufor->elem.key]->color = 0;
			g.set[bufor->elem.key]->index = i;
			g.set[bufor->elem.key]->parent = NULL;
			g.set[bufor->elem.key]->value = INT_MAX;

			bufor = bufor->next;
		}
	}
	for (int i = 0; i < g.size; i++)	
	{
		if (g.set[i] != NULL)cout << "NODE " << i << " REPORTING IN\n";
	}
	g.set[start]->value = 0;
	for (int i = 0; i < g.size; i++)
	{
		for (int j = 0; j < g.size; j++)
		{
			if (g.set[j]->value == i) BFSinside(g, j, i);
		}
	}
	cout << "REPORTING VALUES:" << endl;
	for (int i = 0; i < g.size; i++)
	{
		cout << "NODE " << i << " EQUALS " << g.set[i]->value << endl;
	}
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

		cout << "wrong argument in test: " << command << endl;
		return 1;
	}
}

