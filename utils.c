#include "utils.h"

/* Fonction auxiliaire pour afficher le menu */
void menu(){
    printf("----- Options -----\n");
    printf("0 - Sortie du programme\n");
    printf("1 - Affichage\n");
    printf("2 - Inserer ouvrage\n");
    printf("3 - Rechercher par numéro\n");
    printf("4 - Rechercher par titre\n");
    printf("5 - Rechercher par auteur\n");
    printf("6 - Suppression\n");
    printf("7 - Fusion de deux bibliothèques\n");
    printf("8 - Recherche de multiples\n");
    printf("-------------------\n");
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
    ssize_t input = read(STDIN_FILENO, buffer, (MAX_INT_BUFF - 1));
    if (input > 0){
        buffer[input] = '\0';
        return atoi(buffer);
    } else {
        return -2;
    }
}

/* Fonction auxiliaire pour lire des chaines des characteres*/
void readStr(char* buffer, int max_buffer){

    if (!fgets(buffer, max_buffer, stdin)){
        fprintf(stderr, "Erreur dans la lecture depuis le stdin\n");
    }

}

/* Lire le nom d'un auteur depuis le stdin*/
void readAuteur(char* auteur){
    char buffer[MAX_AUTEUR_LENGTH];

    readStr(buffer, MAX_AUTEUR_LENGTH);

    if (sscanf(buffer, "%s", auteur) != 1){
        fprintf(stderr, "Erreur dans la lecture\n");
    }
}

/* Lire le titre depuis le stdin*/
void readTitre(char* titre){
    char buffer[MAX_TITRE_LENGTH];

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
    printf("Veuillez ecrire l'auteur:\n");
    readAuteur(auteur);
    printf("Veuillez ecrire le titre:\n");
    readTitre(titre);

}

void readNameBiblio(char * nom, int* n){
    char buffer[MAX_FILENAME_LENGTH];

    printf("Veuillez ecrire le nom du fichier contenant la deuxième bibliothèque, ainsi que le nombre de livres à fusionner:\n");
    readStr(buffer, MAX_FILENAME_LENGTH);

    if (sscanf(buffer, "%s", nom) != 1){
        fprintf(stderr, "Erreur dans la lecture\n");
    }
    
    *n = readInteger();

}