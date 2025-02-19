#include "biblioH.h"

//Creation de cle par hachage
int fonction_cle(char* auteur){
    int sum = 0;
    int i = 0;
    while((auteur + i)){
        sum += atoi((auteur + i));
        i++;
    }
    return sum;
}

//Fonction de hachage
int fonction_hachage(int cle, int m){
    return floor(m * ((cle * ((sqrt(5)-1)/2)) % 1));
}

// Creation d'un livre
LivreH* creer_livre(int num,char* titre,char* auteur){
    LivreH* newLivre = (LivreH*)malloc(sizeof(LivreH));
    if (!newLivre) {
        fprintf(stderr, "Erreur dans l'allocation memoire d'un nouveau livre\n");
        return NULL;
    }

    newLivre->cle = fonction_cle(auteur);
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
    newBiblio->T = (LivreH*)malloc(m * sizeof(LivreH));

    return newBiblio;
}

// Liberer une bibliotheque
void liberer_biblio(BiblioH* b){
    if (!b) return;

    LivreH* idx;

    for(int i = 0; i < (b->m); i++){
        while(b->T[i]){
            idx = b->T[i];
            b->T = b->T[i]->suivant;
            liberer_livre(idx);
        }
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

    int h = fonction_hachage(newLivre->cle, b->m);
    
    newLivre->suivant = b->T[h];
    b->T[h] = newLivre;

    return;
}

