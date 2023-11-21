#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>


using namespace std;

const int m = 100;

typedef struct Liste {
    string Info;
    Liste* Suiv;
} Liste;

typedef Liste* Pliste;

typedef struct Eliste {
    int NbElem;
    Liste* PL;
} Eliste;

Eliste TTHash[m];

string GererIdentifier() {
    string identifier = "";
    int length = rand() % 29 + 2; // longueur aléatoire entre 2 et 30
    for (int i = 0; i < length; i++) {
        if (rand() % 3 == 0) { // 1/3 de chance de générer un chiffre
            identifier += rand() % 10 + '0';
        } else { // 2/3 de chance de générer une lettre majuscule
            identifier += rand() % 26 + 'A';
        }
    }
    return identifier;
}

void Creer_Fichier(char chemin[20]) {
    srand(time(NULL)); // initialisation du générateur de nombres aléatoires
    ofstream fichier(chemin, ios::out | ios::trunc); // ouverture du fichier
    if (fichier) {
        for (int i = 0; i < 10000; i++) { // générer 10000 identifiants
            string identifier = GererIdentifier();
            fichier << identifier << endl; // écrire l'identifiant dans le fichier
        }
        fichier.close(); // fermeture du fichier
    } else {
        cout << "Erreur : impossible d'ouvrir le fichier de sortie !" << endl;
    }
}

int Fonc_Hashcode(string ligne, int typeF) {
    int code = 0;
    int l = ligne.length();
    switch (typeF) { // modifier pour tester les différentes fonctions de hashage
        case 1: // fonction de hashage de base
            for (int i = 0; i < l; i++) {
                if (ligne[i] >= '0' && ligne[i] <= '9') {
                    code += ligne[i] - '0';
                } else {
                    code += ligne[i] - 'A';
                }
            }
            return code % m;
        
        case 2: // fonction de hashage 2 
            for (int i = 0; i < l; i++) {
                if (ligne[i] >= '0' && ligne[i] <= '9') {
                    code += pow((ligne[i] - '0'), 2);
                } else if (ligne[i] >= 'A' && ligne[i] <= 'Z') {
                    code += pow((ligne[i] - 'A'), 2);
                } 
            }
            return code % m;;
        case 3: // fonction de hashage 3 // algorithme de Dan Bernstein
            for (int i = 0; i < l; i++) {
                code = ((code << 5) + code) + ligne[i]; // l'opération bit à bit appelée
            }											// "décalage de bits"
            return abs(code) % m;
        case 4: // fonction de hashage 4
            for (int i = 0; i < l; i++) {
                code = 31 * code + ligne[i]; // algorithme de Java
            }
            return abs(code) % m;
        case 5: // fonction de hashage 5
            for (int i = 0; i < l; i++) {
                code = code * 33 + ligne[i]; // algorithme de Bob Jenkins
            }
            return abs(code) % m;
    }
}


void Ajouter_liste(Pliste& L, string element) {
    // création d'un nouveau nœud contenant l'élément à ajouter
    Pliste nouveau = new Liste;
    nouveau->Info = element;
    nouveau->Suiv = NULL;
    
    // si la liste est vide, le nouveau nœud devient la tête de la liste
    if (L == NULL) {
        L = nouveau;
    } else {
        // sinon, on parcourt la liste pour trouver l'endroit où insérer le nouveau nœud
        Pliste precedent = NULL;
        Pliste courant = L;
        while (courant != NULL && courant->Info < element) {
            precedent = courant;
            courant = courant->Suiv;
        }
        // insertion du nouveau nœud
        if (precedent == NULL) {
            nouveau->Suiv = L;
            L = nouveau;
        } else {
            nouveau->Suiv = precedent->Suiv;
            precedent->Suiv = nouveau;
        }
    }
}

int menuFonc(){
	int typeF;
	cout<<"1: // fonction de hashage de base "<<endl;
	cout<<"2: // fonction de hashage 2 "<<endl;
	cout<<"3: // algorithme de Dan Bernstein "<<endl;
	cout<<"4: // algorithme de Java "<<endl;
	cout<<"5: // algorithme de Bob Jenkins "<<endl;
	cin>>typeF;
	return typeF;
}

void Ajouter_Thash(Eliste TTHash[m], string ligne,int typeF) {
    int indice = Fonc_Hashcode(ligne,typeF);
    Ajouter_liste(TTHash[indice].PL, ligne);
    TTHash[indice].NbElem = TTHash[indice].NbElem + 1;
}

void Creer_Thash(Eliste TTHash[m], char chemin[20]) {
    string ligne;
 	
	for (int i = 0; i < m; i++) {
    TTHash[i].NbElem = 0;
    TTHash[i].PL = NULL;
	}
	
	int typeF;
	cout<<" Fonction Hashcode : "<<endl;
	typeF=menuFonc();
	ifstream fichier(chemin, ios::in);
	if (fichier) {
	    while (getline(fichier, ligne)) {
	        Ajouter_Thash(TTHash, ligne,typeF);
	    }
	    fichier.close();
	} else {
	    cerr << "Erreur : impossible d'ouvrir le fichier !" << endl;
	}
}



void Afficher_Nbelem(Eliste TTHash[m]){
	int p=0;
	for(int j=0;j<5;j++){
		
		for(int i=p;i<p+20;i++){
		cout<<"|"<<TTHash[i].NbElem;	
		}
		cout<<"|"<<	endl;
		p+=20;	
	}
}

int main() {
//Creer_Fichier("identifiants.txt");
Creer_Thash(TTHash, "identifiants.txt");
Afficher_Nbelem(TTHash);

return 0;
}


