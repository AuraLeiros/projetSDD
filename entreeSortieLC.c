
#include "entreeSortieLC.h"


// Charger n livres depuis le fichier
Biblio* charger_n_entrees(char* nomfic, int n){


    FILE* f = fopen(nomfic, "r");
    if (!f){
        fprintf(stderr, "Erreur dans l'ouverture du fichier\n");
        return NULL;
    }

    int num;
    char titre[MAX_TITRE_LENGTH];
    char auteur[MAX_AUTEUR_LENGTH];

    Biblio* newBiblio = creer_biblio();
    if (!newBiblio){
        fprintf(stderr, "I/O - Erreur creation bibliotheque\n");
        return NULL;
    }

    char ligne[MAX_LINE_LENGTH];

    for (int i=0; i < n; i++){
        if (fgets(ligne, MAX_LINE_LENGTH, f)){
            if (sscanf(ligne, "%d %s %s", &num, titre, auteur) == 3){
                inserer_en_tete(newBiblio, num, titre, auteur);
            } else {
                fprintf(stderr, "Erreur de lecture d'une ligne\n");
            }
        }
    }

    fclose(f);

    return newBiblio;

}

// Enregistrer la bibliotheque dans un fichier
void enregistrer_biblio(Biblio *b, char* nomfic){
    if (!b){
        fprintf(stderr, "La bibliotheque passé en parametre n'existe pas\n");
        return;
    }


    FILE* f = fopen(nomfic, "a");
    if (!f){
        fprintf(stderr, "Erreur dans l'ouverture du fichier\n");
        return;
    }


    //TODO : check if the fprintf puts a newline automatically
    while (b->L){
        fprintf(f, "%d %s %s\n", b->L->num, b->L->titre, b->L->auteur);
        b->L = b->L->suiv;
    }

    fclose(f);

    return;
}

// Afficher un livre
void afficher_livre(Livre* l){
    if (!l){
        fprintf(stderr, "Le livre n'existe pas\n");
        return;
    }

    printf("Livre %d : Titre : %s Auteur : %s", l->num, l->titre, l->auteur);

    return;
}

// Affichage bibliotheque
void afficher_biblio(Biblio* b){ 
    if (!b) {
        fprintf(stderr, "La bibliothèque n'existe pas\n");
        return;
    }

    printf("Bibliotheque :\n\n");

    while (b->L){
        afficher_livre(b->L);
        b->L = b->L->suiv;
    }

    return;

}

// Recherche par numéro
Livre* recherche_numero(Biblio* b, int num){
    if (!b) {
        fprintf(stderr, "La bibliotheque en parametre n'existe pas\n");
        return NULL;
    }

    while(b->L){
        if (b->L->num == num) return b->L;
        b->L = b->L->suiv;
    }

    return NULL;
}

// Recherche titre
Livre* recherche_titre(Biblio* b, char* titre){
    if (!b) {
        fprintf(stderr, "La bibliotheque en parametre n'existe pas\n");
        return NULL;
    }

    return NULL;
}

// Recherche un livre par auteur
Biblio* recherche_auteur(Biblio* b, char* auteur){

    if (!b || !auteur){
        fprintf(stderr, "Erreur dans les parametres\n");
        return b;
    }

    /* TO-ASK: We suppose that we return a library even if the list is empty ?*/
    Biblio* newBiblio = creer_biblio();
    if (!newBiblio){
        fprintf(stderr, "Erreur dans la creation d'une nouvelle bibliotheque\n");
        return NULL;
    }

    Livre* idx = b->L;

    while (idx) {
        if (strcmp(idx->auteur, auteur) == 0) {
            inserer_en_tete(newBiblio, idx->num, idx->titre, idx->auteur);
        }

        idx = idx->suiv;
    }

    return newBiblio;

}

// Supprime un ouvrage dans bibliotheque
Biblio* suppresion_ouvrage(Biblio* b, int num, char* titre, char* auteur){
    // TO-ASK: We need to find the library using the three or we can just use num?
    if (!b || !titre || !auteur) {
        fprintf(stderr, "Erreur dans les parametres\n");
        return NULL;
    }

    Livre* previousNode = NULL;
    Livre* currentNode = b->L;

    while (currentNode) {
        if ((currentNode->num == num) && (strcmp(currentNode->titre, titre) == 0) && (strcmp(currentNode->auteur, auteur) == 0)) {
            if (!previousNode) {
                b->L = currentNode->suiv;
            } else {
                previousNode->suiv = currentNode->suiv;
            }

            liberer_livre(currentNode);
            break;
        }

        previousNode = currentNode;
        currentNode = currentNode->suiv;
    }

    if (!currentNode) fprintf(stderr, "Le livre n'a pas ete trouve dans la librarie\n");

    return b;
}

// Fusion de deux bibliotheques
Biblio* fusion_bibliotheques(Biblio* b1, Biblio* b2){
    if (!b1 || !b2) {
        fprintf(stderr, "Erreur dans les parametres\n");
        return NULL;
    }

    Livre* idx = b1->L;

    if (!idx) {
        b1->L = b2->L;        
    } else {
        while (idx->suiv) idx = idx->suiv;
        idx->suiv = b2->L;
    }

    free(b2);
    return b1;
}

// Recherche de tous les ouvrages avec plusieurs exemplaires
Livre* recherche_multiple(Biblio* b){
    if (!b) {
        fprintf(stderr, "Erreur dans les parametres\n");
        return NULL;
    }

    Livre* idx = b->L;
    Livre* newLivre;

    if (!idx) return NULL;

    while (idx) {

    }

}


