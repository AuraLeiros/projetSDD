#include "entreeSortieH.h"


// Charger n livres depuis le fichier
BiblioH* charger_n_entrees(char* nomfic, int n){


    FILE* f = fopen(nomfic, "r");
    if (!f){
        fprintf(stderr, "Erreur dans l'ouverture du fichier\n");
        return NULL;
    }

    int num;
    char titre[MAX_TITRE_LENGTH];
    char auteur[MAX_AUTEUR_LENGTH];

    BiblioH* newBiblio = creer_biblio(MAX_HACHAGE_LENGTH);
    if (!newBiblio){
        fprintf(stderr, "I/O - Erreur creation bibliotheque\n");
        return NULL;
    }

    char ligne[MAX_LINE_LENGTH];

    for (int i=0; i < n; i++){
        if (fgets(ligne, MAX_LINE_LENGTH, f)){
            if (sscanf(ligne, "%d %s %s", &num, titre, auteur) == 3){
                inserer(newBiblio, num, titre, auteur);
            } else {
                fprintf(stderr, "Erreur de lecture d'une ligne\n");
            }
        }
    }

    fclose(f);

    return newBiblio;

}

// Enregistrer la bibliotheque dans un fichier
void enregistrer_biblio(BiblioH *b, char* nomfic){
    if (!b){
        fprintf(stderr, "La bibliotheque passé en parametre n'existe pas\n");
        return;
    }


    FILE* f = fopen(nomfic, "a");
    if (!f){
        fprintf(stderr, "Erreur dans l'ouverture du fichier\n");
        return;
    }


    for(int i = 0; i < (b->m); i++){
        while (b->T[i]){
            fprintf(f, "%d %s %s\n", b->T[i]->num, b->T[i]->titre, b->T[i]->auteur);
            b->T[i] = b->T[i]->suivant;
        }
    }
    

    fclose(f);

    return;
}

// Afficher un livre
void afficher_livre(LivreH* l){
    if (!l){
        fprintf(stderr, "Le livre n'existe pas\n");
        return;
    }

    printf("Livre %d : Titre : %s Auteur : %s", l->num, l->titre, l->auteur);

    return;
}

// Affichage bibliotheque
void afficher_biblio(BiblioH* b){ 
    if (!b) {
        fprintf(stderr, "La bibliothèque n'existe pas\n");
        return;
    }

    printf("Bibliotheque :\n\n");

    for(int i = 0; i < (b->m); i++){
        while (b->T[i]){
            afficher_livre(b->T[i]);
            b->T[i] = b->T[i]->suivant;
        }
    }

    return;

}

// Recherche par numéro (pas plus rapide car hachage ne se fait qu'avec la cle qui depend de l'auteur)
LivreH* recherche_numero(BiblioH* b, int num){
    if (!b) {
        fprintf(stderr, "La bibliotheque en parametre n'existe pas\n");
        return NULL;
    }

    for(int i = 0; i < (b->m); i++){
        while (b->T[i]){
            if( b->T[i]->num == num ) return b->T[i];
            b->T[i] = b->T[i]->suivant;
        }
    }

    return NULL;
}

// Recherche titre (meme chose que pour le numero)
LivreH* recherche_titre(BiblioH* b, char* titre){
    if (!b) {
        fprintf(stderr, "La bibliotheque en parametre n'existe pas\n");
        return NULL;
    }

    for (int i = 0; i < b->m; i++){
        LivreH* idx = b->T[i];

        /* Cas 1: Librarie vide*/
        if (!idx) return NULL;

        while (idx) {
            if (strcmp(idx->titre, titre) == 0) return idx;
            idx = idx->suivant;
        }
    }

    return NULL;
}

// Recherche un livre par auteur (plus rapide que pour une bibliotheque en liste chainee car cle de hachage definie a partir de l'auteur)
BiblioH* recherche_auteur(BiblioH* b, char* auteur){

    if (!b || !auteur){
        fprintf(stderr, "Erreur dans les parametres\n");
        return b;
    }

    int h = fonction_hachage(fonction_cle(auteur), b->m);
    
    return b->T[h];

}

// Supprime un ouvrage dans bibliotheque
BiblioH* suppresion_ouvrage(BiblioH * b, int num, char* titre, char* auteur){
    if (!b || !titre || !auteur) {
        fprintf(stderr, "Erreur dans les parametres\n");
        return NULL;
    }

    int h = fonction_hachage(fonction_cle(auteur), b->m);

    LivreH* previousNode = NULL;
    LivreH* currentNode = b->T[h];

    while (currentNode) {
        if ((currentNode->num == num) && (strcmp(currentNode->titre, titre) == 0)) {
            if (!previousNode) {
                b->T[h] = currentNode->suivant;
            } else {
                previousNode->suivant = currentNode->suivant;
            }

            liberer_livre(currentNode);
            break;
        }

        previousNode = currentNode;
        currentNode = currentNode->suivant;
    }

    if (!currentNode) fprintf(stderr, "Le livre n'a pas ete trouve dans la librarie\n");

    return b;
}

// Fusion de deux bibliotheques
BiblioH* fusion_bibliotheques(BiblioH* b1, BiblioH* b2){
    //on suppose que les deux bibliotheques dependent de la meme fonction de hachage et ont la meme taille b->m
    if (!b1 || !b2) {
        fprintf(stderr, "Erreur dans les parametres\n");
        return NULL;
    }

    for(int i = 0; i < b1->m; i++){
        LivreH* idx = b1->T[i];

        if (!idx) {
            b1->T[i] = b2->T[i];        
        } else {
            while (idx->suivant) idx = idx->suivant;
            idx->suivant = b2->T[i];
        }
    }

    free(b2);
    return b1;
}

// Recherche de tous les ouvrages avec plusieurs exemplaires
LivreH* recherche_multiple(BiblioH* b){
    if (!b) {
        fprintf(stderr, "Erreur dans les parametres\n");
        return NULL;
    }


    LivreH* idx;
    LivreH* res;
    LivreH** tete;
    LivreH** fin;

    for(int i = 0; i < b->m; i++){
        LivreH* courant = b->T[i];
        
        /* Cas 1: Aucun ouvrage present dans la bibliotheque */
        if (!courant) return NULL;
    
        /* Traitement de chaque livre dans la liste */
        while (courant){
            auxRechercheAll(b->T[i], courant, tete, fin);
            if ((res != NULL) && (*tete)) {
                res = (*tete);
                idx = (*fin);
            } else if ((*tete) && (*fin)){
                idx->suivant = (*tete);
                idx = (*fin);
            }

            *tete = NULL;
            *fin = NULL;
            courant = courant->suivant;
        }
    }
    

    return res;
}

void auxRechercheAll(LivreH* l, LivreH* lcourant, LivreH** tete, LivreH** fin){
    /*
    @brief Fonction auxiliaire qui trouve tous les livres avec meme titre et auteur mais numero different
    si la fonction trouve de duplicatas enregistre le livre courant dans le param tete et ajoute a la liste
    tous les elements trouves.
    */
    
    if (!l || !lcourant){
        return NULL;
    }

    LivreH* res = NULL;

    while (l){
        if ((lcourant->num != l->num) && (strcmp(lcourant->titre, l->titre) == 0) && (strcmp(lcourant->auteur, l->auteur) == 0)){
            if (!res){
                res = creer_livre(lcourant->num, lcourant->titre, lcourant->auteur);
                tete = &res;
            }

            res->suivant = creer_livre(l->num, l->titre, l->auteur);
            res = res->suivant;

        }

        l = l->suivant;
    }

    fin = &res;
}
