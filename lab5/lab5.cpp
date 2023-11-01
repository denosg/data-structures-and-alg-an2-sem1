#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning (disable : 4996)
#define nrEx 3
using namespace std;
typedef struct _nodABO {
	char nume[100]; // aici am schimbat
	int note[nrEx];
	float media;
	_nodABO* st, * dr;
}nodABO;

nodABO* radN, * radM;

ifstream f;

char s[100];
float vMin, vMax;
int note[nrEx];
//adaugarea in arbore alfabetic
void AdaugNodNume(nodABO** p) {
	int i;
	if (*p) {//nu am ajuns la locul noului nod
		if (strcmp(s, (*p)->nume) < 0)
			AdaugNodNume(&(*p)->st);
		else AdaugNodNume(&(*p)->dr);
	}
	else {//am ajuns => adaugarea lui
		*p = new nodABO;
		//initializarea campurilor de date
		strcpy((*p)->nume, s);
		for (i = 0; i < nrEx; i++) (*p)->note[i] = note[i];
		//initializarea campurilor de legatura
		(*p)->st = (*p)->dr = NULL;
	}
}
//adaugare in arbore dupa medii
void AdaugNodMedii(nodABO** p, nodABO* q) {
	if (*p) {//nu am ajuns la locul noului nod
		if (q->media < (*p)->media)
			AdaugNodMedii(&(*p)->st, q);
		else AdaugNodMedii(&(*p)->dr, q);
	}
	else {//am ajuns
		*p = new nodABO;
		**p = *q;
		(*p)->st = (*p)->dr = NULL;
	}
}
//crearea arborelui binar ordonat dupa nume din fisier
void CreareABONumeFis(void) {
	int nr, i, j;
	f >> nr;
	for (i = 0; i < nr; i++) {
		f >> s;
		for (j = 0; j < nrEx; j++) f >> note[j];

		AdaugNodNume(&radN);//adaugarea nodului in arborele initial
	}
}
//calcularea mediei si construirea arborelui ordonat dupa medii
void ParcurgereABONume(nodABO* p) {//inordine, pentru adaugarea alfabetica
	int i;
	if (p) {
		ParcurgereABONume(p->st);
		//prelucrarea nodului
		p->media = 0;//calculul mediei
		for (i = 0; i < nrEx; i++) p->media += p->note[i];
		p->media /= nrEx;
		AdaugNodMedii(&radM, p);//si adaugarea unui nou nod in noul arbore
		ParcurgereABONume(p->dr);
	}
}
//cauta si afiseaza alfabetic pe cei cu mediile intre cele doua valori
void CautaAB(nodABO* p) {//parcurgere in inordine
	if (p) {
		CautaAB(p->st);
		if (p->media >= vMin && p->media <= vMax)
			cout << "\n" << p->nume << "  " << p->media << endl;
		CautaAB(p->dr);
	}
}
//cauta si afiseaza in ordinea mediilor pe cei cu mediile intre cele doua valori
void CautaABO(nodABO* p) {//parcurgere in inordine
	if (p) {
		if (p->media >= vMin) CautaABO(p->st);
		if (p->media >= vMin && p->media <= vMax)
			cout << "\n" << p->nume << "  " << p->media << endl;
		if (p->media <= vMax) CautaABO(p->dr);
	}
}
//afisarea unui arbore
void Afisare(nodABO* p, int niv) {//parcurgere in inordine inversa (D, R, S)
	int i;
	if (p) {
		Afisare(p->dr, niv + 1);
		for (i = 0; i < niv; i++) cout << "   ";
		cout << "\n" << p->nume << "  " << p->media;
		Afisare(p->st, niv + 1);
	}
}
//stergerea subarborelui cu radacina indicata de p
void StergABO(nodABO* p) {
	if (p) {//traversare in postordine

		StergABO(p->st);
		StergABO(p->dr);

		delete p;
	}
}

int main() {
	radN = radM = NULL;
	f = ifstream("medii.txt");
	if (!f.is_open()) {
		cout << "Eroare la deschiderea fisierului.";
		return 1;
	}
	CreareABONumeFis();
	f.close();

	ParcurgereABONume(radN);
	cout << "ARBORELE ORDONAT ALFABETIC:\n";
	Afisare(radN, 0);
	cout << "\nARBORELE ORDONAT DUPA MEDII:\n";
	Afisare(radM, 0);
	cout << "\nValoarea minima: "; cin >> vMin;
	cout << "Valoarea maxima: "; cin >> vMax;

	cout << "Lista din arborele alfabetic: "; CautaAB(radN);
	cout << "\nLista din arborele pe medii: "; CautaABO(radM);

	StergABO(radN);	//stergerea arborelui ordonat dupa nume
	StergABO(radM); //stergerea arborelui ordonat dupa medii

	return 0;
}