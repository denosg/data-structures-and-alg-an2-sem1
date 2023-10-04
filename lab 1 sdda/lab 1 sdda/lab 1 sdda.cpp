#include <iostream>
#include <conio.h>
#include <string.h>
#include <fstream>
#pragma warning (disable : 4996)
using namespace std;
struct student_struct
{
	char nume[20];
	char prenume[20];
	int nota;
	student_struct* urm;
};
student_struct* prim, * p, * t;
int o;
void adauga_studenti()
{
	char nume[20], prenume[20];
	int nota;


	ifstream inputFile("date.txt");

	if (inputFile.is_open()) {
		while (true) {
			inputFile >> nume;
			inputFile >> prenume;
			inputFile >> nota;
			if (prim == NULL)
			{
				prim = new student_struct;
				strcpy(prim->nume, nume);
				strcpy(prim->prenume, prenume);
				prim->nota = nota;
				prim->urm = NULL;
			}
			else {
					p = prim;
					while (p->urm != NULL) p = p->urm;
					t = new student_struct;
					strcpy(t->nume, nume);
					strcpy(t->prenume, prenume);
					t->nota = nota;
					t->urm = NULL;
					p->urm = t;
			}
			if (inputFile.eof()) break;
		}
	}
	else {
		cout << "Error: Unable to open the file." << std::endl;
	}
	_getch();
}
void afis_lista()
{
	cout << "\n\nAfisare lista studenti\n\n";
	if (prim == NULL)
		cout << "Nu avem nici un student in lista";
	else
	{
		p = prim;
		while (p != NULL)
		{
			if (p->nota > 5) {
				cout << "\nNume: " << p->nume << "\nPrenume: " << p->prenume << "\nNota: " << p->nota;
			}
			p = p->urm;
		}
	}

}


int main() {
	do
	{
		cout << "\nMeniu\n";
		cout << "1.Adaugare student\n";
		cout << "2.Afisare lista studenti\n";
		cout << "3.Iesire\n\n";
		cout << "Alegeti optiunea : ";
		cin >> o;
		switch (o)
		{
		case 1:adauga_studenti(); break;
		case 2:afis_lista(); break;
		}
	} while (o != 3);
}
