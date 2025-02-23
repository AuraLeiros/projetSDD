#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


#include "macros.h"


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

/* Lire le nom d'un fichier et garantir les droits d'access */
void readFilename(char* filename);

/* --------------------------*/
/* Fonctions de Benchmarking */
/* -------------------------*/

/* Fonction pour faire le calcul (en ms) d'execution d'une fonction
    Notre implementation ne fonctionne que sur systemes UNIX !!
*/
void benchmark(double* time);

/* Fonction pour allouer et initialiser un tableau de double */
double* newArray(int n);

/* Fonction pour ajouter un element à un array */
void addElementArray(double* array, int* size, double elem, int maxSize);

/* Fonction auxiliaire a qsort pour comparer deux doubles */
int comparaisonDouble(const void *a, const void *b);

/* Fonction pour calculer la mediane d'un tableau */
double mediane(double* array, int nElem);


#endif