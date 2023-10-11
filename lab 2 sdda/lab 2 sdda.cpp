#include <iomanip>
#include <iostream>
#include <conio.h>
#define nrMaxN 20
using namespace std;

typedef struct _nod {
	int cheie;
	int parinte;
}nod;
nod A[nrMaxN];
int nrEl;

void AdaugFii(int idxParinte, int cheie, int niv) {
	int i, j, idx, nrFii;
	//adaugarea nodului
	idx = nrEl;  //retinem indicele noului nod
	A[nrEl].cheie = cheie;
	A[nrEl].parinte = idxParinte;
	nrEl++;
	nrFii = 0;  //inca nu are fii
	do {  //adaugarea fiilor
		for (i = -1; i < niv; i++) cout << "   ";
		cout << "Fiul " << ++nrFii << " al lui  " << cheie << "  este ";
		cin >> j;
		if (j) AdaugFii(idx, j, niv + 1);
	} while (j);
}
void CreareAG() {
	int i;
	nrEl = 0;
	cout << "Radacina arborelui: ";
	cin >> i;
	if (i) AdaugFii(-1, i, 0);
}
void Afisare() {
	int i;
	cout << "\nIndice:  ";
	for (i = 0; i < nrEl; i++)
		cout << setw(4) << i;//se foloseste in locul printf("%3d", i)
	cout << "\nCheie:   ";
	for (i = 0; i < nrEl; i++) cout << setw(4) << A[i].cheie;
	cout << "\nParinte: ";
	for (i = 0; i < nrEl; i++)
		cout << setw(4) << A[i].parinte;
}
//parcurgere in preordine
void AfisareAG(int idx, int niv) {
	int i;
	//prelucrarea nodului
	cout << "\n";
	if (niv % 2 == 1)
		cout << A[idx].cheie;
	//parcurgerea fiilor
	for (i = idx + 1; i < nrEl; i++) //fiii au indici mai mari
		if (A[i].parinte == idx) AfisareAG(i, niv + 1);
}
int main() {
	CreareAG();
	cout << "Afisarea ca tablou:\n";
	Afisare();
	_getch();
	cout << "\n\nAfisarea ca arbore:";
	AfisareAG(0, 0);
	_getch();
}