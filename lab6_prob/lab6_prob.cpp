#include <iostream>

using namespace std;
typedef struct _nodABO {
	int cheie;
	_nodABO* st, * dr;
}nodABO;

nodABO* radN;

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

void copyAndDelPred(struct _nodABO** node, struct _nodABO* q) {
	while ((*node)->dr) node = &(*node)->dr;
	q->cheie = (*node)->cheie;
	q = *node;
	*node = (*node)->st;
	delete q;
}

void deleteNode(struct _nodABO** noteToDel, int key) {
	struct _nodABO* nodeToCopy;
	if (!(*noteToDel)) cout << "Nod negasit";
	else
		if (key < (*noteToDel)->cheie) { deleteNode(&(*noteToDel)->st, key); }
		else {
			if (key > (*noteToDel)->cheie) { deleteNode(&(*noteToDel)->dr, key); }
			else {
				nodeToCopy = (*noteToDel);
				if ((*noteToDel)->st == NULL) {
					*noteToDel = (*noteToDel)->dr;
					delete nodeToCopy;
				}
				else {
					if ((*noteToDel)->dr == NULL) {
						*noteToDel = (*noteToDel)->st;
						delete nodeToCopy;
					}
					else {
						copyAndDelPred(&(*noteToDel)->st, nodeToCopy);
					}
				}
			}
		}
}

int main()
{
	radN = NULL;
	int nr;
	int key;
	cout << "nr =: ";
	cin >> nr;
	while (nr != 0) {
		addNode(nr, &radN);
		cout << "nr =: ";
		cin >> nr;
	}
	printNodes(radN, 0);
	cout << "Intoduceti cheia nodului pe care vreti sa il stergeti: ";
	cin >> key;
	deleteNode(&radN, key);
	printNodes(radN, 0);
}
