#include "biblioLC.h"
#include "entreeSortieLC.h"
#include "utils.h"

int main(int argc, char** argv){

    /* Test de l'input et recuperation du nombre de lignes a lire */
    int n = testInputs(argc, argv);

    /* Lecture du fichier */
    Biblio* b = charger_n_entrees(argv[1], n);
    if (!b){
        fprintf(stderr, "Erreur dans la lecture\n");
        return EXIT_FAILURE;
    }

    int usrInput;

    char nomBiblio2[MAX_FILENAME_LENGTH] = "";
    int numberBooks = 0; //nombre de livres à fusionner
    char auteur[MAX_AUTEUR_LENGTH] = "";
    char titre[MAX_TITRE_LENGTH] = "";
    double time = 0.0;
    int num = 0;

    Livre* l = NULL;
    Biblio* newBiblio = NULL;
    Biblio* biblio2 = NULL;

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
                    printf("Le temps de calcul pour cette option est de %lf\n", time);
                    time = 0.0;
                #endif

                break;
                printf("--- Fin affichage ---\n\n");

            case 2: 
                printf("--- Inserer livre ---\n");


                readIdLivre(&num, auteur, titre);

                if (num >= 0 && auteur[0] != '\0' && titre[0] != '\0'){

                    #ifndef BENCHMARKFLAG
                        benchmark(&time);
                    #endif

                    inserer_en_tete(b, num, titre, auteur);


                    #ifndef BENCHMARKFLAG
                        benchmark(&time);
                        printf("Le temps de calcul pour cette option est de %lf\n", time);
                        time = 0.0;
                    #endif

                } else {
                    printf("Erreur format\n");
                }

                printf("--- Fin inserer livre ---\n\n");

                break;

            case 3:
                printf("--- Recherche par numero ---\n");
                printf("Veuillez taper le numero:\n");

                num = readInteger();
                l = recherche_numero(b, num);

                if (l) {


                    #ifndef BENCHMARKFLAG
                        benchmark(&time);
                    #endif

                    afficher_livre(l);


                    #ifndef BENCHMARKFLAG
                        benchmark(&time);
                        printf("Le temps de calcul pour cette option est de %lf\n", time);
                        time = 0.0;
                    #endif

                } else {
                    printf("Aucun livre n'a ete trouve avec le numero indique\n");
                }

                printf("--- Fin recherche par numero ---\n\n");
                
                break;

            case 4:
                printf("--- Recherche par titre ---\n");
                printf("Veuillez taper le titre du livre:\n");

                readTitre(titre);

                if (titre[0] != '\0'){


                    #ifndef BENCHMARKFLAG
                        benchmark(&time);
                    #endif

                    l = recherche_titre(b, titre);

                    #ifndef BENCHMARKFLAG
                        benchmark(&time);
                        printf("Le temps de calcul pour cette option est de %lf\n", time);
                        time = 0.0;
                    #endif

                } else {
                    fprintf(stderr, "Erreur dans la lecture d'un titre\n");
                }

                printf("--- Fin recherche par titre ---\n\n");

                break;


            case 5:
                printf("--- Recherche auteur ---\n");

                readAuteur(auteur);

                if (auteur[0] != '\0'){


                    #ifndef BENCHMARKFLAG
                        benchmark(&time);
                    #endif

                    newBiblio = recherche_auteur(b, auteur);


                    #ifndef BENCHMARKFLAG
                        benchmark(&time);
                        printf("Le temps de calcul pour cette option est de %lf\n", time);
                        time = 0.0;
                    #endif

                    if (!b->L){
                        fprintf(stderr, "Aucun livre avec le nom indique à ete trouve\n");
                    }
                    
                } else {
                    fprintf(stderr, "Erreur de lecture\n");
                }

                printf("--- Fin recherche par auteur ---\n\n");

                break;
            
            case 6:
                printf("--- Suppression ouvrage ---\n");
                readIdLivre(&num, auteur, titre);

                if (num >= 0 && auteur[0] != '\0' && titre[0] != '\0'){

                    #ifndef BENCHMARKFLAG
                        benchmark(&time);
                    #endif

                    suppresion_ouvrage(b, num, titre, auteur);


                    #ifndef BENCHMARKFLAG
                        benchmark(&time);
                        printf("Le temps de calcul pour cette option est de %lf\n", time);
                        time = 0.0;
                    #endif

                } else {
                    fprintf(stderr, "Erreur dans les parametres\n");
                }

                break;
        
            case 7:
                printf("--- Fusion libraries ---\n");
                
                readNameBiblio(nomBiblio2, &numberBooks);
                if (auteur[0] != '\0' && numberBooks >= 0){

                    biblio2 = charger_n_entrees(nomBiblio2, numberBooks);
                    if (!biblio2){
                        fprintf(stderr, "Erreur dans la lecture\n");
                        return EXIT_FAILURE;
                    }

                    #ifndef BENCHMARKFLAG
                        benchmark(&time);
                    #endif

                    newBiblio = fusion_bibliotheques(b, biblio2);

                    #ifndef BENCHMARKFLAG
                        benchmark(&time);
                        printf("Le temps de calcul pour cette option est de %lf\n", time);
                        time = 0.0;
                    #endif

                    enregistrer_biblio(newBiblio, "BibliothequeFusion.txt");
                    printf("Vous trouverez la bibliothèque fusionnée dans le fichier intitulé 'BibliothequeFusion.txt'\n");
                } else {
                    fprintf(stderr, "Erreur dans les parametres\n");
                }

                printf("--- Fin Fusion libraries ---\n\n");

                break;

            case 8:
                printf("--- Recherche Multiples ---\n");

                #ifndef BENCHMARKFLAG
                    benchmark(&time);
                #endif

                l = recherche_multiple(b);


                #ifndef BENCHMARKFLAG
                    benchmark(&time);
                    printf("Le temps de calcul pour cette option est de %lf\n", time);
                    time = 0.0;
                #endif

                printf("--- Fin Recherche Multiples ---\n\n");

            default:
                printf("L'option demandé n'est pas disponible, veuillez selectionner une option entre 0 et %d", NB_OPTIONS);
                continue;
        }

    } while (usrInput != 0);

    /* Liberation de memoire */
    liberer_biblio(b);
    if (l) liberer_livre(l);
    if (newBiblio) liberer_biblio(newBiblio);

    printf("Merci et au revoir !\n");

    return EXIT_SUCCESS;
}