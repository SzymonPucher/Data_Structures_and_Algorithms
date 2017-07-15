#include<iostream>
#include <string>
#include <sstream>
// BST
using namespace std;

struct Element {
	int key;
	int value;
};

struct Node {
	Element elem;
	Node *parent;
	Node *left;
	Node *right;
};

struct BST {
	Node *root;
};

void init(BST & tree) {
	tree.root = new Node;
	tree.root = NULL;
}

bool insertElem(BST & tree, Element elem) {
	Node *nowy = new Node;
	Node *srch = tree.root;
	nowy->elem.key = elem.key;
	nowy->elem.value = elem.value;
	nowy->left = NULL;
	nowy->right = NULL;
	nowy->parent = NULL;

	if (srch == NULL) {
		nowy->parent = NULL;
		tree.root = nowy;
	}
	else {
		while (true) {
			if (nowy->elem.key == srch->elem.key)
				return false;
			if (nowy->elem.key < srch->elem.key) {
				nowy->parent = srch;
				srch = srch->left;
				if (srch == NULL) {
					nowy->parent->left = nowy;
					break;
				}
			}
			else {
				nowy->parent = srch;
				srch = srch->right;
				if (srch == NULL) {
					nowy->parent->right = nowy;
					break;
				}
			}
		}
	}
	return true;
}


void showInorder2(Node * n) {
	if (n != NULL) {
		showInorder2(n->left);
		cout << n->elem.key << "(" << n->elem.value << "),";
		showInorder2(n->right);
	}
}

void showInorder(BST & tree) {
	if (tree.root != NULL) {
		showInorder2(tree.root);
		cout << endl;
	}
}

void showPreorder2(Node * n) {
	if (n != NULL) {
		cout << n->elem.key << "(" << n->elem.value << "),";
		showPreorder2(n->left);
		showPreorder2(n->right);
	}
}

void showPreorder(BST & tree) {
	if (tree.root != NULL) {
		showPreorder2(tree.root);
		cout << endl;
	}
}

void showPostorder2(Node * n) {
	if (n != NULL) {
		showPostorder2(n->left);
		showPostorder2(n->right);
		cout << n->elem.key << "(" << n->elem.value << "),";
	}
}

void showPostorder(BST & tree) {
	if (tree.root != NULL) {
		showPostorder2(tree.root);
		cout << endl;
	}
}

Node *findNode(Node *node, int key) {
	return NULL;
}

bool findKey(BST & tree, int key, Element &elem) {
	Node *srch = tree.root;
	if (tree.root == NULL)
		return false;
	while (true) {
		if (key == srch->elem.key) {
			cout << srch->elem.key << '(' << srch->elem.value << ')' << endl;
			return true;
		}
		if (key < srch->elem.key) {
			srch = srch->left;
			if (srch == NULL)
				return false;
		}
		else {
			srch = srch->right;
			if (srch == NULL)
				return false;
		}
	}
}

Node *minimalNode(Node *node) {
	return NULL;
}

Node * findSuccesor(Node * node) {
	if (node->right != NULL)
		return minimalNode(node->right);
	int key = node->elem.key;
	do {
		node = node->parent;
	} while (node->elem.key <key);

	return node;
}



bool removeKey(BST & tree, int key, Element &elem) {

	Node *srch = tree.root;

	if (tree.root == NULL)
		return false;

	while (true) {
		if (key == srch->elem.key) {
			int value = srch->elem.value;
			// 1 element tree
			if (srch->left == NULL && srch->right == NULL && srch->parent == NULL)
				tree.root = NULL;
			// key is tree.root
			else if (srch->parent == NULL && tree.root != NULL) {
				if (srch->right == NULL) {
					tree.root = srch->left;
					srch->left->parent = NULL;
				}
				else if (srch->left != NULL) {

					Node *srch2 = srch->right;
					if (srch2->left != NULL)
						srch2 = srch2->left;
					else if (srch2->right != NULL)
						srch2 = srch2->right;
					while (true) {
						if (srch2->left == NULL || srch2->right == NULL) {
							if (srch2->left == NULL && srch2->right == NULL) {}
							else if (srch2->left == NULL) {
								srch2->right->parent = srch2->parent;
								srch2->parent->left = srch2->right;
							}
							else if (srch2->right == NULL) {
								srch2->left->parent = srch2->parent;
								srch2->parent->left = srch2->left;
							}
							srch2->parent = NULL;
							srch->left->parent = srch2;
							srch->right->parent = srch2;
							srch2->left = srch->left;
							srch2->right = srch->right;
							tree.root = srch2;
							break;
						}
						srch2 = srch2->left;
					}
				}
				else {
					tree.root = srch->right;
					srch->right->parent = NULL;
				}
			}

			// no children
			else if (srch->left == NULL && srch->right == NULL) {
				if (srch->elem.key > srch->parent->elem.key)
					srch->parent->right = NULL;
				else srch->parent->left = NULL;
			}
			// 1 child right
			else if (srch->left == NULL && srch->right != NULL) {
				if (srch->elem.key > srch->parent->elem.key) {
					srch->right->parent = srch->parent;
					srch->parent->right = srch->right;
				}
				else {
					srch->right->parent = srch->parent;
					srch->parent->left = srch->right;
				}
			}
			// 1 child left
			else if (srch->left != NULL && srch->right == NULL) {
				if (srch->elem.key > srch->parent->elem.key) {
					srch->left->parent = srch->parent;
					srch->parent->right = srch->left;
				}
				else {
					srch->left->parent = srch->parent;
					srch->parent->left = srch->left;
				}
			}
			// 2 children
			else if (srch->left != NULL && srch->right != NULL) {
				Node *srch2 = srch->right;
				while (true) {
					if (srch2->left != NULL)
						srch2 = srch2->left;
					else break;
				}

				if (srch2->right != NULL) {
					srch2->parent->left = srch2->right;
					srch2->right->parent = srch2->parent;
				}
				else {
					srch2->parent->left = NULL;
					srch2->parent = NULL;
				}

				srch->elem.key = srch2->elem.key;
				srch->elem.value = srch2->elem.value;

				delete srch2;
			}
			cout << key << '(' << value << ')' << endl;
			return true;
		}


		if (key < srch->elem.key) {
			srch = srch->left;
			if (srch == NULL)
				return false;
		}
		else {
			srch = srch->right;
			if (srch == NULL)
				return false;
		}
	}
}


void clear(Node *node) {

}

void clear(BST & tree) {
	//tree.root = NULL;

	Node *srch = tree.root;

	while (tree.root != NULL) {
		srch = tree.root;
		if (srch->left == NULL && srch->right == NULL)
			tree.root = NULL;
		if (tree.root != NULL) {
			if (srch->right == NULL) {
				tree.root = srch->left;
				srch->left->parent = NULL;
			}
			else if (srch->left == NULL) {
				tree.root = srch->right;
				srch->right->parent = NULL;
			}
			else if (srch->left != NULL) {
				Node *srch2 = srch->right;
				while (true) {
					if (srch2->left == NULL) {
						srch->left->parent = srch2;
						srch2->left = srch->left;
						break;
					}
					srch2 = srch2->left;
				}
				tree.root = srch->right;
				srch->right->parent = NULL;
			}
		}
	}
}

int countLeaves(Node* node)
{
	int c = 0;
	if (node != NULL) {
		if (node->left == NULL && node->right != NULL || node->left != NULL && node->right == NULL) {
			c++;
			return c;
		}
		else return countLeaves(node->left) + countLeaves(node->right);
	}
	else return 0;
}

int countLeaves(BST & tree) {
	return countLeaves(tree.root);
}

int sameValue(Node* node)
{
	if (node != NULL) {
		if (node->left->elem.value == node->right->elem.value) {
			return 1;
		}
		else return sameValue(node->left) + sameValue(node->right);
	}
	else return 0;
}

int sameValue(BST & tree) {
	return sameValue(tree.root);
}

int numberOfNodes(Node* node) {
	if (!node)
		return 0;

	int count = 0;

	count += numberOfNodes(node->left);
	count++;
	count += numberOfNodes(node->right);
	return count;
}

int numberOfNodes(BST & tree) {
	return numberOfNodes(tree.root);
}

int OneChild(Node* node) {
	if (!node)
		return 0;

	/*int count = 0;
	count += OneChild(node->left);
	if (node->left == NULL && node->right != NULL || node->left != NULL && node->right == NULL) {
	count++;
	}
	count += OneChild(node->right);
	return OneChild(node->left) + OneChild(node->right); */

	return ((node->left == NULL && node->right != NULL || node->left != NULL && node->right == NULL) ? 1 : 0) + OneChild(node->left) + OneChild(node->left);
	
}

int OneChild(BST & tree) {
	return OneChild(tree.root);
}

int height(Node *node)
{
	if (!node)
		return 0;

	int h = 0;
	h++;

	int left = height(node->left);
	int right = height(node->right);

	(left > right) ? h += left : h += right;
	return h;
}

int height(BST & tree) {
	return height(tree.root);
}

int functionA(BST & tree) {
	return -1;
}

int functionB(BST & tree, int key) {
	return -1;
}

bool functionC(BST & tree, int key, Element &elem) {
	return false;
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
	BST *tree = NULL;
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

		if (isCommand(command, "SI"))
		{
			showInorder(tree[currentT]);
			continue;
		}

		if (isCommand(command, "SP"))
		{
			showPreorder(tree[currentT]);
			continue;
		}

		if (isCommand(command, "SQ"))
		{
			showPostorder(tree[currentT]);
			continue;
		}

		if (isCommand(command, "CL"))
		{
			clear(tree[currentT]);
			continue;
		}

		if (isCommand(command, "IN"))
		{
			init(tree[currentT]);
			continue;
		}

		if (isCommand(command, "NN"))
		{
			cout << numberOfNodes(tree[currentT]) << endl;
			continue;
		}

		if (isCommand(command, "OC"))
		{
			cout << OneChild(tree[currentT]) << endl;
			continue;
		}

		if (isCommand(command, "LC"))
		{
			cout << countLeaves(tree[currentT]) << endl;
			continue;
		}

		if (isCommand(command, "SV"))
		{
			cout << sameValue(tree[currentT]) << endl;
			continue;
		}

		if (isCommand(command, "HE"))
		{
			cout << height(tree[currentT]) << endl;
			continue;
		}

		if (isCommand(command, "FA"))
		{
			cout << functionA(tree[currentT]) << endl;
			continue;
		}

		// read next argument, one int value
		stream >> value;


		if (isCommand(command, "IE"))
		{
			int variable2;
			stream >> variable2;
			Element elem;
			elem.key = value;
			elem.value = variable2;
			showBool(insertElem(tree[currentT], elem));
			continue;
		}

		if (isCommand(command, "FK"))
		{
			Element elem;
			bool ret = findKey(tree[currentT], value, elem);
			if (ret) {}
			else
				cout << "false" << endl;
			continue;
		}

		if (isCommand(command, "RK"))
		{
			Element elem;
			bool ret = removeKey(tree[currentT], value, elem);
			if (ret) {

			}
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
			tree = new BST[value];
			continue;
		}

		if (isCommand(command, "FB"))
		{
			cout << functionB(tree[currentT], value) << endl;
			continue;
		}

		if (isCommand(command, "FC"))
		{
			Element elem;
			bool ret = functionC(tree[currentT], value, elem);
			if (ret)
				cout << elem.key << '(' << elem.value << ')' << endl;
			else
				cout << "false" << endl;
			continue;
		}
		cout << "wrong argument in test: " << command << endl;
	}
	return 0;
}
