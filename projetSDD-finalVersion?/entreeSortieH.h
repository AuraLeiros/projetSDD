#ifndef ENTREESORTIEH_H
#define ENTREESORTIEH_H

#include "biblioH.h"
#include "macros.h"
#include "utils.h"

// Charger n livres depuis le fichier
BiblioH* charger_n_entrees(char* nomfic, int n);

// Enregistrer la bibliotheque dans un fichier
void enregistrer_biblio(BiblioH *b, char* nomfic);

// Afficher un livre
void afficher_livre(LivreH* l);

// Afficher une liste chainee de livres
void auxAfficherListeLivres(LivreH* l);

// Affichage bibliotheque
void afficher_biblio(BiblioH* b);

// Recherche par numéro
LivreH* recherche_numero(BiblioH* b, int num);

// Recherche titre
LivreH* recherche_titre(BiblioH* b, char* titre);

// Recherche un livre par auteur
LivreH* recherche_auteur(BiblioH* b, char* auteur);

// Supprime un ouvrage dans bibliotheque
BiblioH* suppresion_ouvrage(BiblioH* b, int num, char* titre, char* auteur);

// Fusion de deux bibliotheques
void fusion_bibliotheques(BiblioH* b1, BiblioH* b2);

// Recherche de tous les ouvrages avec plusieurs exemplaires
LivreH* recherche_multiple(BiblioH* b);

/* Fonction auxiliaire a inserer pour trouver tous les livres d'un meme auteur */
void auxRechercheAll(LivreH* lcourant, LivreH** head, LivreH** tail);


/* --------------------------*/
/* Fonctions de Benchmarking */
/* -------------------------*/

void executionRecherche(BiblioH* b, int ite, int num, char* titre, char* auteur);

void executionRechercheNumero(BiblioH* b, int ite, int numero);

void executionRechercheMultiple(char* nomfic);


#endif