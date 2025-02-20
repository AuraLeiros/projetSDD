// Structure

#ifndef BIBLIOLC_H
#define BIBLIOLC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"

typedef struct livre {
    int num;
    char *titre;
    char *auteur;
    struct livre* suiv;
} Livre;

typedef struct {
    Livre* L;
} Biblio;


/* FONCTIONS */


// Creation d'un livre
Livre* creer_livre(int num,char* titre,char* auteur);

// Libération de la mémoire
void liberer_livre(Livre* l);

// Créer une bibliotheque
Biblio* creer_biblio();

// Liberer une bibliotheque
void liberer_biblio(Biblio* b);

// Insertion en tete d'un nouveau livre
void inserer_en_tete(Biblio* b, int num, char* titre, char* auteur);


#endif