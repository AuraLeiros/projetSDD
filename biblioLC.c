#include "biblioLC.h"

// Creation d'un livre
Livre* creer_livre(int num, char* titre, char* auteur){


    Livre* newLivre = (Livre*)malloc(sizeof(Livre));
    if (!newLivre) {
        fprintf(stderr, "Erreur dans l'allocation memoire d'un nouveau livre\n");
        return NULL;
    }

    newLivre->num = num;
    newLivre->titre = strdup(titre);
    newLivre->auteur = strdup(auteur);
    newLivre->suiv = NULL;

    return newLivre;
}

// Libération de la mémoire
void liberer_livre(Livre* l){
    if (!l) return;

    free(l->titre);
    free(l->auteur);
    free(l);

    return;
}

// AUX: liberation d'une liste chainee de livres
void auxLibererListeLivres(Livre* l){
    if (!l) return;

    Livre* tmp = l;

    while (l){
        tmp = l->suiv;
        liberer_livre(l);
        l = tmp;
    }

    return;

}


// Créer une bibliotheque
Biblio* creer_biblio(){

    Biblio* newBiblio = (Biblio*)malloc(sizeof(Biblio));
    if (!newBiblio) {
        fprintf(stderr, "Erreur dans l'allocation memoire d'une nouvelle bibliotheque\n");
        return NULL;
    }    

    newBiblio->L = NULL;

    return newBiblio;

}

// Liberer une bibliotheque
void liberer_biblio(Biblio* b){
    if (!b) return;

    Livre* idx;

    auxLibererListeLivres(b->L);

    free(b);

    return;
}

/* Insertion en tete d'un nouveau livre */
void inserer_en_tete(Biblio* b, int num, char* titre, char* auteur){
    if (!b) {
        fprintf(stderr, "La bibliotheque passe en parametre n'existe pas\n");
        return;
    }

    Livre* newLivre = creer_livre(num, titre, auteur);
    if (!newLivre){
        fprintf(stderr, "Erreur dans la creation et insertion en tete d'un nouveau livre\n");
        return;
    }

    newLivre->suiv = b->L;
    b->L = newLivre;

    return;
}