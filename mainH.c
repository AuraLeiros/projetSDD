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
    double time = 0.0;
    int num = 0;

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
            case 1:
                printf("--- Affichage ---\n");

                #ifndef BENCHMARKFLAG
                    benchmark(&time);
                #endif

                afficher_biblio(b);


                #ifndef BENCHMARKFLAG
                    benchmark(&time);
                    printf("Le temps de calcul pour cette option est de %lf", time);
                #endif

                break;
                printf("--- Fin affichage ---\n");

            case 2: 
                printf("--- Inserer livre ---\n");
                printf("Veuillez ecrire le numero, le titre et l'auteur de l'ouvrage\n");

                readIdLivre(&num, auteur, titre);

                #ifndef BENCHMARKFLAG
                    benchmark(&time);
                #endif

                if (num >= 0 && auteur[0] != '\0' && titre[0] != '\0'){
                    inserer(b, num, titre, auteur);
                } else {
                    printf("Erreur format\n");
                }

                #ifndef BENCHMARKFLAG
                    benchmark(&time);
                    printf("Le temps de calcul pour cette option est de %lf", time);
                #endif

                printf("--- Fin inserer livre ---\n");

                break;

            case 3:
                printf("--- Recherche par numero ---\n");
                printf("Veuillez taper le numero:\n");

                num = readInteger();

                #ifndef BENCHMARKFLAG
                    benchmark(&time);
                #endif

                l = recherche_numero(b, num);

                #ifndef BENCHMARKFLAG
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

                    #ifndef BENCHMARKFLAG
                        benchmark(&time);
                    #endif

                    l = recherche_titre(b, titre);

                    #ifndef BENCHMARKFLAG
                        benchmark(&time);
                        printf("Le temps de calcul pour cette option est de %lf", time);
                    #endif

                } else {
                    fprintf(stderr, "Erreur dans la lecture d'un titre\n");
                }

                printf("--- Fin recherche par titre ---");

                break;

            case 5:
                printf("--- Recherche auteur ---");

                readAuteur(auteur);

                if (auteur[0] != '\0'){

                    #ifndef BENCHMARKFLAG
                        benchmark(&time);
                    #endif

                    l = recherche_auteur(b, auteur);


                    #ifndef BENCHMARKFLAG
                        benchmark(&time);
                        printf("Le temps de calcul pour cette option est de %lf", time);
                    #endif

                    if (!b->T){
                        fprintf(stderr, "Aucun livre avec le nom indique à ete trouve\n");
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

                    #ifndef BENCHMARKFLAG
                        benchmark(&time);
                        printf("Le temps de calcul pour cette option est de %lf", time);
                    #endif

                    suppresion_ouvrage(b, num, titre, auteur);


                    #ifndef BENCHMARKFLAG
                        benchmark(&time);
                        printf("Le temps de calcul pour cette option est de %lf", time);
                    #endif

                } else {
                    fprintf(stderr, "Erreur dans les parametres\n");
                }

                break;

            case 7:
                printf("--- Fusion libraries ---\n");

                #ifndef BENCHMARKFLAG
                    benchmark(&time);
                #endif

                //TO-DO

                #ifndef BENCHMARKFLAG
                    benchmark(&time);
                    printf("Le temps de calcul pour cette option est de %lf", time);
                #endif

                printf("--- Fin Fusion libraries ---\n");
                
            case 8:
                printf("--- Recherche Multiples ---\n");

                #ifndef BENCHMARKFLAG
                    benchmark(&time);
                #endif

                l = recherche_multiple(b);


                #ifndef BENCHMARKFLAG
                    benchmark(&time);
                    printf("Le temps de calcul pour cette option est de %lf", time);
                #endif

                printf("--- Fin Recherche Multiples ---\n");


            default:
                printf("L'option demandé n'est pas disponible, veuillez selectionner une option entre 0 et %d", NB_OPTIONS);
                continue;
        }

    } while (usrInput != 0);


    liberer_biblio(b);
    if (l) liberer_livre(l);
    if (newBiblio) liberer_biblio(newBiblio);

    printf("Merci et au revoir !\n");

    return EXIT_SUCCESS;
}