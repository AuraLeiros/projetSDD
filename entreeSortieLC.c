
#include "entreeSortieLC.h"


// Charger n livres depuis le fichier
Biblio* charger_n_entrees(char* nomfic, int n){


    FILE* f = fopen(nomfic, "r");
    if (!f){
        fprintf(stderr, "Erreur dans l'ouverture du fichier\n");
        return NULL;
    }

    int num;
    char* titre, auteur;

    Biblio* newBiblio = creer_biblio();
    if (!newBiblio){
        fprintf(stderr, "I/O - Erreur creation bibliotheque\n");
        return NULL;
    }

    char ligne[256];

    for (int i=0; i < n; i++){
        if (fgets(ligne, 256, f)){
            sscanf(ligne, "%d %s %s", &num, titre, auteur);
            inserer_en_tete(newBiblio, num, titre, auteur);
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
    while (b->l){
        fprintf(f, "%d %s %s\n", b->l->num, b->l->titre, b->l->auteur);
        b->l = b->l->suiv;
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

    while (b->l){
        afficher_livre(b->l);
        b->l = b->l->suiv;
    }

    return;

}

// Recherche par numéro
Livre* recherche_numero(Biblio* b, int num){
    if (!b) {
        fprintf(stderr, "La bibliothèque n'existe pas\n");
        return;
    }

    while(b->l){
        if (b->l->num == num) return b->l;
        b->l = b->l->suiv;
    }

    return NULL;
}

// Recherche titre
Livre* recherche_titre(Biblio* b, char* titre){
    if (!b) {
        fprintf(stderr, "La bibliothèque n'existe pas\n");
        return;
    }

    while ()


}

// Recherche un livre par auteur
Biblio* recherche_auteur(Biblio* b, char* auteur);

// Supprime un ouvrage dans bibliotheque
Biblio* suppresion_ouvrage(Biblio* b, int num, char* titre, char* auteur);

// Fusion de deux bibliotheques
Biblio* fusion_bibliotheques(Biblio* b1, Biblio* b2);

// Recherche de tous les ouvrages avec plusieurs exemplaires
Livre* recherche_multiple(Biblio* b);


