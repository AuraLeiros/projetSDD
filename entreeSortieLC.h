#ifndef ENTREESORTIELC_H
#define ENTREESORTIELC_H

#include "biblioLC.h"

#define MAX_LINE_LENGTH 256
#define MAX_TITRE_LENGTH 128
#define MAX_AUTEUR_LENGTH 128

// Charger n livres depuis le fichier
Biblio* charger_n_entrees(char* nomfic, int n);

// Enregistrer la bibliotheque dans un fichier
void enregistrer_biblio(Biblio *b, char* nomfic);

// Afficher un livre
void afficher_livre(Livre* l);

// Affichage bibliotheque
void afficher_biblio(Biblio* b);

// Recherche par numéro
Livre* recherche_numero(Biblio* b, int num);

// Recherche titre
Livre* recherche_titre(Biblio* b, char* titre);

// Recherche un livre par auteur
Biblio* recherche_auteur(Biblio* b, char* auteur);

// Supprime un ouvrage dans bibliotheque
Biblio* suppresion_ouvrage(Biblio* b, int num, char* titre, char* auteur);

// Fusion de deux bibliotheques
Biblio* fusion_bibliotheques(Biblio* b1, Biblio* b2);

// Recherche de tous les ouvrages avec plusieurs exemplaires
Livre* recherche_multiple(Biblio* b);




















#endif