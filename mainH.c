#include "biblioH.h"
#include "entreeSortieH.h"
#include "utils.h"

/* Le calcul de temps est sur des instructions du preprocesseur pour compiler avec le flag -benchmark */

int main(int argc, char** argv){

    /* Test de l'input et recuperation du nombre de lignes a lire */
    int n = testInputs(argc, argv);

    /* Lecture du fichier */
    BiblioH* b = charger_n_entrees(argv[1], n);
    if (!b){
        fprintf(stderr, "Erreur dans la lecture\n");
        return EXIT_FAILURE;
    }

    int usrInput;
    char auteur[MAX_AUTEUR_LENGTH] = "";
    char titre[MAX_TITRE_LENGTH] = "";
    int num = 0;

    #ifdef BENCHMARKFLAG
        double time = 0.0;
    #endif

    LivreH* l = NULL;
    BiblioH* newBiblio = NULL;

    do {
        menu();
        usrInput = readInteger();
        if (usrInput < 0 || usrInput > NB_OPTIONS) {
            fprintf(stderr, "Option hors range ! Veuillez selectionner une autre\n\n");
            continue;
        }

        switch(usrInput){
            case 0:
                break;
                
            case 1:
                printf("--- Affichage ---\n");

                #ifdef BENCHMARKFLAG
                    benchmark(&time);
                #endif

                afficher_biblio(b);

                #ifdef BENCHMARKFLAG
                    benchmark(&time);
                    printf("Le temps de calcul pour cette option est de %lf", time);
                #endif

                printf("--- Fin affichage ---\n");

                break;

            case 2: 
                printf("--- Inserer livre ---\n");
                printf("Veuillez ecrire le numero, le titre et l'auteur de l'ouvrage :\n");

                readIdLivre(&num, auteur, titre);

                #ifdef BENCHMARKFLAG
                    benchmark(&time);
                #endif

                if (num >= 0 && auteur[0] != '\0' && titre[0] != '\0'){
                    inserer(b, num, titre, auteur);
                } else {
                    printf("Erreur format\n");
                }

                #ifdef BENCHMARKFLAG
                    benchmark(&time);
                    printf("Le temps de calcul pour cette option est de %lf", time);
                #endif

                printf("--- Fin inserer livre ---\n");

                break;

            case 3:
                printf("--- Recherche par numero ---\n");
                printf("Veuillez taper le numero:\n");

                num = readInteger();

                #ifdef BENCHMARKFLAG
                    benchmark(&time);
                #endif

                l = recherche_numero(b, num);

                #ifdef BENCHMARKFLAG
                    benchmark(&time);
                    printf("Le temps de calcul pour cette option est de %lf", time);
                #endif


                if (l) {
                    afficher_livre(l);
                } else {
                    printf("Aucun livre n'a ete trouve avec le numero indique\n");
                }


                printf("--- Fin recherche par numero ---\n");
                
                break;

            case 4:
                printf("--- Recherche par titre ---\n");
                printf("Veuillez taper le nom de l'auteur:\n");

                readTitre(titre);

                if (titre[0] != '\0'){

                    #ifdef BENCHMARKFLAG
                        benchmark(&time);
                    #endif

                    l = recherche_titre(b, titre);

                    #ifdef BENCHMARKFLAG
                        benchmark(&time);
                        printf("Le temps de calcul pour cette option est de %lf", time);
                    #endif

                    if (l){
                        afficher_livre(l);
                    } else {
                        printf("Aucun livre n'a ete trouve avec le titre indique\n");
                    }

                } else {
                    fprintf(stderr, "Erreur dans la lecture d'un titre\n");
                }

                printf("--- Fin recherche par titre ---");

                break;

            case 5:
                printf("--- Recherche auteur ---");

                readAuteur(auteur);

                if (auteur[0] != '\0'){

                    #ifdef BENCHMARKFLAG
                        benchmark(&time);
                    #endif

                    l = recherche_auteur(b, auteur);

                    #ifdef BENCHMARKFLAG
                        benchmark(&time);
                        printf("Le temps de calcul pour cette option est de %lf", time);
                    #endif

                    if (b->T){
                        printf("Aucun livre avec le nom indique à ete trouve\n");
                    }

                } else {
                    fprintf(stderr, "Erreur de lecture\n");
                }

                printf("--- Fin recherche par auteur ---\n");

                break;

            case 6:
                printf("--- Suppresion ouvrage ---\n");
                
                readIdLivre(&num, auteur, titre);

                if (num >= 0 && auteur[0] != '\0' && titre[0] != '\0'){

                    #ifdef BENCHMARKFLAG
                        benchmark(&time);
                        printf("Le temps de calcul pour cette option est de %lf", time);
                    #endif

                    suppresion_ouvrage(b, num, titre, auteur);

                    #ifdef BENCHMARKFLAG
                        benchmark(&time);
                        printf("Le temps de calcul pour cette option est de %lf", time);
                    #endif

                } else {
                    fprintf(stderr, "Erreur dans les parametres\n");
                }

                break;

            case 7:
                printf("--- Fusion libraries ---\n");

                char filename[MAX_FILENAME_LENGTH];

                readFilename(filename);
                if (filename[0] == '\0'){
                    fprintf(stderr, "Erreur dans la lecture du fichier\n");
                    break;
                }

                printf("Veuillez taper le numero de lignes à lire: ");
                num = readInteger();
                if (num == -2 || num <= 0){
                    fprintf(stderr, "Erreur dans la lecture du nombre de lignes à lire\n");
                    break;
                }

                newBiblio = charger_n_entrees(filename, num);
                if (!newBiblio || !newBiblio->T){
                    fprintf(stderr, "Erreur dans la lecture d'une nouvelle bibliotheque\n");
                    break;
                }

                #ifdef BENCHMARKFLAG
                    benchmark(&time);
                #endif

                BiblioH* fusionBibliotheques = fusion_bibliotheques(b, newBiblio);

                #ifdef BENCHMARKFLAG
                    benchmark(&time);
                    printf("Le temps de calcul pour cette option est de %lf", time);
                #endif

                if (!fusionBibliotheques || !fusionBibliotheques->T){
                    fprintf(stderr, "Erreur dans la fusion des bibliotheques\n");
                } else {
                    printf("Fusion reussie\n");
                }

                liberer_biblio(fusionBibliotheques);

                printf("--- Fin Fusion libraries ---\n");
                
            case 8:
                printf("--- Recherche Multiples ---\n");

                #ifdef BENCHMARKFLAG
                    benchmark(&time);
                #endif

                l = recherche_multiple(b);

                #ifdef BENCHMARKFLAG
                    benchmark(&time);
                    printf("Le temps de calcul pour cette option est de %lf", time);
                #endif

                printf("--- Fin Recherche Multiples ---\n");
                break;


            default:
                printf("L'option demandé n'est pas disponible, veuillez selectionner une option entre 0 et %d\n", NB_OPTIONS);
                continue;
        }  

        #ifdef BENCHMARKFLAG
            time = 0.0;
        #endif

        if (l) auxLibererListeLivres(l);
        if (newBiblio) liberer_biblio(newBiblio);

    } while (usrInput != 0);

    liberer_biblio(b);

    printf("Merci et au revoir !\n");

    return EXIT_SUCCESS;
}