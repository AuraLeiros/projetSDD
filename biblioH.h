// Structure

#ifndef BIBLIOH_H
#define BIBLIOH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct livreh {
    int cle;
    int num;
    char *titre;
    char *auteur;
    struct livreh *suivant;
} LivreH;

typedef struct table{
    int nE; /*nombre d’elements contenus dans la table de hachage */
    int m; /*taille de la table de hachage */
    LivreH** T; /*table de hachage avec resolution des collisions par chainage */
} BiblioH;


/* FONCTIONS */

//Creation de cle par hachage
int fonction_cle(char* auteur);

//Fonction de hachage
int fonction_hachage(int cle, int m);

// Creation d'un livre
LivreH* creer_livre(int num,char* titre,char* auteur);

// Libération de la mémoire
void liberer_livre(LivreH* l);

// Créer une bibliotheque
BiblioH* creer_biblio(int m);

// Liberer une bibliotheque
void liberer_biblio(BiblioH* b);

// Insertion en tete d'un nouveau livre
void inserer(BiblioH* b, int num, char* titre, char* auteur);









#endif