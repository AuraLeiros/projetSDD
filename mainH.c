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
    char filename[MAX_FILENAME_LENGTH] = "";
    int num = 0;
    int ite = 0;

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

                afficher_biblio(b);

                printf("--- Fin affichage ---\n");

                break;

            case 2: 
                printf("--- Inserer livre ---\n");

                readTitre(titre);
                readAuteur(auteur);

                if (auteur[0] != '\0' && titre[0] != '\0'){
                    inserer(b, (b->nE), titre, auteur);
                } else {
                    printf("Erreur format\n");
                }

                printf("--- Fin inserer livre ---\n");

                break;

            case 3:
                printf("--- Recherche par numero ---\n");
                printf("Veuillez taper le numero:\n");

                num = readInteger();

                l = recherche_numero(b, num);

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

                    l = recherche_titre(b, titre);

                    if (l){
                        afficher_livre(l);
                        auxLibererListeLivres(l);
                    } else {
                        printf("Aucun livre n'a ete trouve avec le titre indique\n");
                    }

                } else {
                    fprintf(stderr, "Erreur dans la lecture d'un titre\n");
                }

                printf("--- Fin recherche par titre ---\n");

                break;

            case 5:
                printf("--- Recherche auteur ---\n");

                readAuteur(auteur);

                if (auteur[0] != '\0'){

                    l = recherche_auteur(b, auteur);

                    if (l){
                        auxAfficherListeLivres(l);
                        auxLibererListeLivres(l);
                    } else {
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

                    suppresion_ouvrage(b, num, titre, auteur);

                } else {
                    fprintf(stderr, "Erreur dans les parametres\n");
                }

                break;

            case 7:
                printf("--- Fusion libraries ---\n");

                readFilename(filename);
                if (filename[0] == '\0'){
                    fprintf(stderr, "Erreur dans la lecture du fichier\n");
                    break;
                }

                printf("Veuillez taper le numero de lignes à lire: ");
                fflush(stdout);

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

                fusion_bibliotheques(b, newBiblio);

                printf("--- Fin Fusion libraries ---\n");
                break;
                
            case 8:
                printf("--- Recherche Multiples ---\n");

                l = recherche_multiple(b);

                if (l){
                    auxAfficherListeLivres(l);
                } else {
                    printf("Aucun livre dupliquee n'a pas ete trouve\n");
                }

                printf("--- Fin Recherche Multiples ---\n");
                break;

            case 9:
                printf("--- Enregistrer bibliotheque ---\n");
                enregistrer_biblio(b, argv[1]);
                printf("--- Fin Enregistrer biblioteque ---\n");

                break;
            
            case 10:
                printf("--- Temps d'execution ---\n");
                printf("Veuillez ecrire le nombre d'iterations souhaitées : ");
                ite = readInteger();
                readIdLivre(&num, auteur, titre);

                executionRecherche(b, ite, num, auteur, titre);
                printf("--- Fin temps d'execution ---\n");
                break;

            case 11:
                printf("--- Temps d'execution ---\n");
                executionRechercheMultiple(argv[1]);
                printf("--- Fin temps d'execution ---\n");
                break;



            default:
                printf("L'option demandé n'est pas disponible, veuillez selectionner une option entre 0 et %d\n", NB_OPTIONS);
                continue;
        }  

        #ifdef BENCHMARKFLAG
            time = 0.0;
        #endif

    } while (usrInput != 0);

    liberer_biblio(b);
    if (newBiblio) liberer_biblio(newBiblio);

    printf("Merci et au revoir !\n");

    return EXIT_SUCCESS;
}