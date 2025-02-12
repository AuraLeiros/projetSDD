#include "biblioLC.h"
#include "entreeSortieLC.h"

int main(int argc, char** argv){

    if (argc != 3){
        fprintf(stderr, "Le nombre de paramètres n'est pas correct\n");
        printf("Usage : %s, <nom_fichier> <nombre_lignes>", argv[0]);
        return EXIT_FAILURE;
    }

    // Lecture du fichier 

    Biblio* b = charger_n_entrees(argv[1], argv[2]);
    if (!b){
        fprintf(stderr, "Erreur dans la lecture\n");
        return EXIT_FAILURE;
    }

    



}