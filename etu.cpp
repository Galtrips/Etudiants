#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include "TP4.h"

using namespace std;
const int N = 179;

struct Etudiant {
    int annee; //BUT 1, 2 ou 3
    int numero; //numero etudiant unique
    Etudiant* parrain = NULL; // pointe vers son parrain-NULL si pas de parrain
    char nom[30];
    char prenom[30];
};

void charger_liste_etudiants(const char nom_fichier[], Etudiant tab[]) {

    ifstream entree(nom_fichier, ios::in);
    char ligne[200];
    if (!entree) {
        cout << "Probleme d'ouverture" << endl;
    }
    else {
        int i = 0;
        while (!entree.eof()) {

            entree.getline(ligne, 200, ';');
            tab[i].numero = atoi(ligne);

            entree.getline(ligne, 200, ';');
            strcpy_s(tab[i].prenom, ligne);

            entree.getline(ligne, 200, ';');
            strcpy_s(tab[i].nom, ligne);

            entree.getline(ligne, 200);
            tab[i].annee = atoi(ligne);

            i++;
        }
    }
}

void compte(Etudiant* tab, int N, int* bu1, int* bu2, int* bu3) {

    for (int i = 0; i < N; i++) {

        if ((tab+i)->annee == 1 ) {
            *bu1 +=  1;
        }
        else if ((tab+i)->annee == 2) {
            *bu2 += 1;
        }
        else {
            *bu3 += 1;
        }

    }

}

Etudiant* trouver(int numero, Etudiant tab[]) {
    Etudiant* p1 = NULL;
    
    for (int i = 0; i < N; i++) {
        if (numero == tab[i].numero) {
            p1 = &tab[i];
            return p1;
        }
    }
    return p1;

}

void charger_parrain(const char nom_fichier[], Etudiant tab[]) {

    ifstream entree(nom_fichier, ios::in);
    char ligne[200];
    if (!entree) {
        cout << "Probleme d'ouverture" << endl;
    }
    else {
        int i = 0;
        while (!entree.eof()) {

            entree.getline(ligne, 200, ';');
            
            entree.getline(ligne, 200);
            
            if (ligne) {
                tab[i].parrain = trouver(atoi(ligne), tab);
            }

            
            i++;
        }
    }
}

void affiche_etu(Etudiant& etu) {
    cout << "Prenom: " << etu.prenom << " Nom: " << etu.nom << " Annee: " << etu.annee << " Numero: " << etu.numero << " Parrain: ";
    if (etu.parrain == NULL) {
        cout << "Non";
    }
    else {
        cout << "Oui";
    }
    cout << endl;
}

void affiche_parrain_1A(Etudiant tab[]) {

    for (int i = 0; i < N; i++) {

        if (tab[i].annee == 1) {
            cout << tab[i].prenom << " " << tab[i].nom << " a pour parrain/marraine " << tab[i].parrain->prenom << " " << tab[i].parrain->nom << endl;
        }

    }
    cout << endl;

}

void changerParrain(Etudiant& etu1, Etudiant& etu2) {

    Etudiant* tmp = etu1.parrain;
    etu1.parrain = etu2.parrain;
    etu2.parrain = tmp;
    
}

void affiche_filleuls_2A(Etudiant tab[]) {


    for (int i = 0; i < N; i++) {

        if (tab[i].annee == 2) {
            cout << tab[i].prenom << " " << tab[i].nom;
            bool filleul = false;
            for (int j = 0; j < N; j++) {
                if (tab[j].parrain != NULL) {
                    int num = tab[j].parrain->numero;
                    if (tab[i].numero == num) {
                        filleul = true;
                    }

                }
            }
            if (filleul == false) {
                cout << " n'a pas de filleul(e)";
            }
            else {
                int cmp = 1;
                cout << " a pour filleul(es) ";
                for (int j = 0; j < N; j++) {
                    if (tab[j].parrain != NULL) {
                        int num = tab[j].parrain->numero;
                        if (tab[i].numero == num) {
                            if (cmp >= 2) {
                                cout << ", " << tab[j].prenom << " " << tab[j].nom;
                                cmp++;
                            }
                            else {
                                cout << tab[j].prenom << " " << tab[j].nom;
                                cmp++;
                            }
                        }
                    }
                }
            }
            cout << endl;
        }

    }
    cout << endl;


}

void parrain_promo(Etudiant tab[]) {
    int cmp = 0;
    for (int i = 0; i < N; i++) {

        if (tab[i].parrain != NULL) {

            if (tab[i].parrain->annee == tab[i].annee) {

                cout << tab[i].parrain->prenom << " " << tab[i].parrain->nom << " est le parrain de " << tab[i].prenom << " " << tab[i].nom << " dans l'annee " << tab[i].annee << endl;
                cmp++;
            }

        }
    }
    if (cmp == 0) {
        cout << "Il n'y a pas d'etudiant qui ont des parrains dans la meme promotion..." << endl;
    }

    cout << endl;
}

int comptepf(Etudiant tab[]) {

    int compteur = 0;

    for (int i = 0; i < N; i++) {

        bool filleul = false;

        for (int j = 0; j < N; j++) {
            if (tab[j].parrain != NULL) {
                int num = tab[j].parrain->numero;
                if (tab[i].numero == num) {
                    filleul = true;
                }

            }
        }
        
        if (filleul == true && tab[i].parrain != NULL) {

            compteur++;

        }
    }
    return compteur;
}


int main() {
    Etudiant tab[N];
    charger_liste_etudiants("liste.csv", tab);
    charger_parrain("parrains.csv", tab);
    int bu1 = 0, bu2 = 0, bu3 = 0;

    compte(tab, N, &bu1, &bu2, &bu3);

    cout << bu1 << " " << bu2 << " " << bu3 << endl;

    affiche_parrain_1A(tab);

    affiche_filleuls_2A(tab);
    
    parrain_promo(tab);

    int total = comptepf(tab);

    cout << "Il y a " << total << " etudiants qui sont parrain et filleul..." << endl;

    return 0;
}
