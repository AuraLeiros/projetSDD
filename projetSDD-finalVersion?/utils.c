#include "utils.h"

/* Fonction auxiliaire pour afficher le menu */
void menu(){
    printf("\n");
    printf("----- Options -----\n");
    printf("0 - Sortie du programme\n");
    printf("1 - Affichage\n");
    printf("2 - Inserer un ouvrage\n");
    printf("3 - Recherche par numero\n");
    printf("4 - Recherche par titre\n");
    printf("5 - Recherche par auteur\n");
    printf("6 - Suppression d'un ouvrage\n");
    printf("7 - Fusion des bibliotheques\n");
    printf("8 - Recherche multiple\n");
    printf("9 - Enregister bibliotheque courant\n");
    printf("10 - Temps d'execution des fonctions de recherche\n");
    printf("11 - Temps d'execution de recherche_multiple\n");
    printf("-------------------\n\n");
    printf("Veuillez selectionner une option :\n");

}

/* Fonction auxiliaire pour montrer l'usage du programme */
void usage(char* nomProgramme){
    fprintf(stderr, "Probleme avec les parametres\n");
    printf("Usage : %s <nom_fichier> <nombre_lignes>", nomProgramme);
    exit(1);
}

/* Fonction auxiliaire pour lire des nombres */
int readInteger(){
    char buffer[MAX_INT_BUFF];
    char extra;
    int i = 0;

    readStr(buffer, MAX_INT_BUFF);

    if (sscanf(buffer, "%d%c", &i, &extra) != 1){
        fprintf(stderr, "L'input n'est pas un nombre. Veuillez reesayer.\n");
        return -2;
    }

    return i;
}

/* Fonction auxiliaire pour lire des chaines des characteres*/
void readStr(char* buffer, int max_buffer){

    if (!fgets(buffer, max_buffer, stdin)){
        fprintf(stderr, "Erreur dans la lecture depuis le stdin\n");
    }

    buffer[strcspn(buffer, "\n")] = '\0';
}

/* Lire le nom d'un auteur depuis le stdin*/
void readAuteur(char* auteur){
    char buffer[MAX_AUTEUR_LENGTH];

    printf("Veuillez ecrire le nom de l'autor :\n");
    readStr(buffer, MAX_AUTEUR_LENGTH);

    if (sscanf(buffer, "%s", auteur) != 1){
        fprintf(stderr, "Erreur dans la lecture\n");
    }
}

/* Lire le titre depuis le stdin*/
void readTitre(char* titre){
    char buffer[MAX_TITRE_LENGTH];

    printf("Veuillez ecrire le titre:\n");
    readStr(buffer, MAX_TITRE_LENGTH);

    if (sscanf(buffer, "%s", titre) != 1){
        fprintf(stderr, "Erreur dans la lecture\n");
    }
}

int testInputs(int argc, char** argv){

    if (argc != 3) usage(argv[0]);

    int n = atoi(argv[2]);

    if (n <= 0 || (access(argv[1], F_OK) == -1)) usage(argv[0]);

    return n;
}

void readIdLivre(int* num, char* auteur, char* titre){
    
    printf("Veuillez ecrire le numero:\n");
    *num = readInteger();

    readAuteur(auteur);
    readTitre(titre);

}

void readFilename(char* filename){
    char buffer[MAX_FILENAME_LENGTH];

    printf("Veuillez inserer le chemin du fichier : \n");
    readStr(buffer, MAX_FILENAME_LENGTH);

    buffer[strcspn(buffer, "\n")] = '\0';

    if (access(buffer, F_OK) != 0) {
        fprintf(stderr, "Erreur dans la lecture du nouveau fichier\n");
    } else {
        strcpy(filename, buffer);
    }

    return;
}


/* --------------------------*/
/* Fonctions de Benchmarking */
/* -------------------------*/


void benchmark(double* time) {
    struct timespec ts;

    if (*time == 0.0) {
        clock_gettime(CLOCK_MONOTONIC, &ts);
        *time = (double)ts.tv_sec * 1e6 + (double)ts.tv_nsec / 1e3; 
    } else {
        clock_gettime(CLOCK_MONOTONIC, &ts);
        double current_time = (double)ts.tv_sec * 1e6 + (double)ts.tv_nsec / 1e3; 
        *time = current_time - *time; 
    }
}

double* newArray(int n){
    double* array = (double*)calloc((n), sizeof(double));
    if (!array){
        fprintf(stderr, "Erreur dans la creation d'un nouveau tableau\n");
        return NULL;
    }

    return array;
}

void addElementArray(double* array, int* size, double elem, int maxSize) {
    if (!array) {
        fprintf(stderr, "Le tableau en parametre n'existe pas\n");
        return;
    }

    if (*size < maxSize) {
        array[*size] = elem;
        (*size)++;
    } else {
        fprintf(stderr, "Erreur, le tableau est complet");
    }
}


int comparaisonDouble(const void *a, const void *b){
        double num1 = *((double*)a);
        double num2 = *((double*)b);
    
        if (num1 < num2) return -1;
        if (num1 > num2) return 1;
        return 0;
}


double mediane(double* array, int nElem){
    if ((nElem % 2) == 0){
        return (array[nElem / 2 - 1] + array[nElem / 2]) / 2.0;
    } else {
        return array[nElem / 2];
    }

}