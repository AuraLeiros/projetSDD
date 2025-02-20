#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "macros.h"
#include "benchmarking.h"

void menu();

void usage(char* nomProgramme);



/* Tests the input and returns the number of lines */
int testInputs(int argc, char** argv);

/* ----------------------*/
/* Fonctions de lecture */
/* ----------------------*/

/* Lire une ligne depuis le stdin */
void readStr(char* buffer, int max_buffer);

/* Lire un entier depuis le stdin */
int readInteger();

/* readAuteur et readTitre sont separes pour permettre de changer la taille de l'auteur ou le titre si besoin */

/* Lire un auteur depuis le stdin */
void readAuteur(char* auteur);

/* Lire un titre depuis le stdin */
void readTitre(char* titre);

/* Lire le numero, auteur et titre d'un livre */
void readIdLivre(int* num, char* auteur, char* titre);

void readNameBiblio(char * nom, int* n);

#endif