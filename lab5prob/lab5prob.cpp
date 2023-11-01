#include <iostream>

using namespace std;
typedef struct _nodABO {
	int cheie;
	_nodABO* st, * dr;
}nodABO;

nodABO* radN;
nodABO* radBiggerKey;

void addNode(int nr, nodABO** node) {
	if (*node) {
		if (nr < (*node)->cheie) {
			addNode(nr, &((*node)->st));
		}
		else {
			addNode(nr, &((*node)->dr));
		}
	}
	else
	{
		(*node) = new nodABO;
		(*node)->cheie = nr;
		(*node)->st = NULL;
		(*node)->dr = NULL;
	}
}

void printNodes(nodABO* node, int niv) {
	if (node != NULL) {
		printNodes(node->st, niv + 1);
		cout << "\n" << node->cheie;
		printNodes(node->dr, niv + 1);
	}
}

void printNodesForLevel(nodABO* node, int niv, int searchedLevel) {
	if (node != NULL) {
		if (searchedLevel == niv) {
			cout << "\n" << node->cheie;
		}
		printNodesForLevel(node->st, niv + 1, searchedLevel);
		printNodesForLevel(node->dr, niv + 1, searchedLevel);
	}
}

//TODO: add the found nodes in a new node struct to show them in inordine
void addNodesForBiggerKey(nodABO* node, int key) {
	if (node != NULL) {
		if (node->cheie > key) {
			addNode(node->cheie, &radBiggerKey);
		}
		addNodesForBiggerKey(node->st, key);
		addNodesForBiggerKey(node->dr, key);
	}
}

int main()
{
	radN = NULL;
	int nr;
	int searchedLevel;
	int key;
	cout << "nr =: ";
	cin >> nr;
	while (nr != 0) {
		addNode(nr, &radN);
		cout << "nr =: ";
		cin >> nr;
	}
	printNodes(radN, 0);
	cout << "\n" << "nivel cautat =: ";
	cin >> searchedLevel;
	printNodesForLevel(radN, 0, searchedLevel);
	cout << "\n" << "key =: ";
	cin >> key;
	addNodesForBiggerKey(radN, key);
	printNodes(radBiggerKey, 0);
}
