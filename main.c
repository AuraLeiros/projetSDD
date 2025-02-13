#include <unistd.h>
#include "biblioLC.h"
#include "entreeSortieLC.h"

#define MAX_USER_INPUT 8
#define NB_OPTIONS 3


int main(int argc, char** argv){


    if (argc != 3 || atoi(argv[2]) <= 0) usage(argv[0]);

    // Lecture du fichier 
    Biblio* b = charger_n_entrees(argv[1], atoi(argv[2]));
    if (!b){
        fprintf(stderr, "Erreur dans la lecture\n");
        return EXIT_FAILURE;
    }

    char buffer[MAX_USER_INPUT];
    int usrInput;

    do {
        menu();
        usrInput = atoi(read(STDIN_FILENO, buffer, MAX_USER_INPUT));
        if (userInput < 0 || userInput > MAX_USER_INPUT){
            fprintf(stderr, "Option hors range\n");
            
        }

        switch (userInput){

            case 1:
                printf("Affichage :\n");
                afficher_biblio(b);
                break;
            
            case 2:
                int num;
                char titre[MAX_TITRE_LENGTH];
                char auteur[MAX_AUTEUR_LENGTH];
                printf("Veuillez ecrire le numero le titre et l'auteur de l'ouvrage\n");







            default:
                printf("L'option demandé n'est pas disponible, veuillez selectionner une option entre 0 et %d", MAX_USER_INPUT);
                continue;

        }



    } while (usrInput != 0)
}

void menu() {
    printf("----- Options -----\n");
    printf("0 - Sortie du programme\n");
    printf("1 - Affichage\n");
    printf("2 - Inserer ouvrage\n");
    printf("-------------------\n")
}

void usage(char* nomProgramme){
    fprintf(stderr, "Probleme avec les parametres\n");
    printf("Usage : %s <nom_fichier> <nombre_lignes>", nomProgramme);
    exit(1);
}
