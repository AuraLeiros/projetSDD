#include "biblioH.h"

int fonctionClef(char* auteur){
    if (!auteur){
        fprintf(stderr, "Aucun nom d'auteur a ete passe en parametre\n");
        return -1;
    }

    int sum = 0;
    char* idx = auteur;

    while(*idx) {
        sum += (int)(*idx);
        idx++;
    }

    return sum;
}

//Fonction de hachage
int fonctionHachage(int cle, int m){
    
    const double A = (sqrt(5) - 1) / 2;
    double kA = cle * A;
    double multip = m * (kA - floor(kA));
    int hash = floor(multip);

    return hash;
}

// Creation d'un livre
LivreH* creer_livre(int num,char* titre,char* auteur){
    LivreH* newLivre = (LivreH*)malloc(sizeof(LivreH));
    if (!newLivre) {
        fprintf(stderr, "Erreur dans l'allocation memoire d'un nouveau livre\n");
        return NULL;
    }

    newLivre->cle = fonctionClef(auteur);
    newLivre->num = num;
    newLivre->titre = strdup(titre);
    newLivre->auteur = strdup(auteur);
    newLivre->suivant = NULL;

    return newLivre;
}

// Libération de la mémoire
void liberer_livre(LivreH* l){
    if (!l) return;

    free(l->titre);
    free(l->auteur);
    free(l);

    return;
}

// Créer une bibliotheque
BiblioH* creer_biblio(int m){

    BiblioH* newBiblio = (BiblioH*)malloc(sizeof(BiblioH));
    if (!newBiblio) {
        fprintf(stderr, "Erreur dans l'allocation memoire d'une nouvelle bibliotheque\n");
        return NULL;
    }    
    newBiblio->nE = 0;
    newBiblio->m = m;
    newBiblio->T = (LivreH**)calloc(m, sizeof(LivreH*));

    return newBiblio;
}

// Liberer une bibliotheque
void liberer_biblio(BiblioH* b){
    if (!b) return;

    LivreH* idx = NULL;
    LivreH* curr = NULL;

    for (int i = 0; i < b->m; i++){
        curr = b->T[i];
        while (curr){
            idx = curr;
            curr = curr->suivant;
            liberer_livre(idx);
        }

        b->T[i] = NULL;

    }

    free(b);

    return;
}

// Insertion en tete d'un nouveau livre
void inserer(BiblioH* b, int num, char* titre, char* auteur){
    LivreH* newLivre = creer_livre(num, titre, auteur);
    if (!newLivre){
        fprintf(stderr, "Erreur dans la creation et insertion en tete d'un nouveau livre\n");
        return;
    }

    int h = fonctionHachage(newLivre->cle, b->m);
    
    newLivre->suivant = b->T[h];
    b->T[h] = newLivre;

    return;
}