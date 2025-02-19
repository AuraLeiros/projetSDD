#ifndef ENTREESORTIEH_H
#define ENTREESORTIEH_H

#include "biblioH.h"

#define MAX_LINE_LENGTH 256
#define MAX_TITRE_LENGTH 128
#define MAX_AUTEUR_LENGTH 128
#define MAX_HACHAGE_LENGTH 300

// Charger n livres depuis le fichier
BiblioH* charger_n_entrees(char* nomfic, int n);

// Enregistrer la bibliotheque dans un fichier
void enregistrer_biblio(BiblioH *b, char* nomfic);

// Afficher un livre
void afficher_livre(LivreH* l);

// Affichage bibliotheque
void afficher_biblio(BiblioH* b);

// Recherche par numéro
LivreH* recherche_numero(BiblioH* b, int num);

// Recherche titre
LivreH* recherche_titre(BiblioH* b, char* titre);

// Recherche un livre par auteur
BiblioH* recherche_auteur(BiblioH* b, char* auteur);

// Supprime un ouvrage dans bibliotheque
BiblioH* suppresion_ouvrage(BiblioH* b, int num, char* titre, char* auteur);

// Fusion de deux bibliotheques
BiblioH* fusion_bibliotheques(BiblioH* b1, BiblioH* b2);

// Recherche de tous les ouvrages avec plusieurs exemplaires
LivreH* recherche_multiple(BiblioH* b);


#endif