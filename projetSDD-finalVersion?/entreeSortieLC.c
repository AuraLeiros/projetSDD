
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
        } else {
            fprintf(stderr, "Warning : Le fichier a moins de %d lignes\n", n);
            break;
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


    FILE* f = fopen(nomfic, "w");
    Livre* idx = b->L;

    if (!f){
        fprintf(stderr, "Erreur dans l'ouverture du fichier\n");
        return;
    }

    while (idx){
        fprintf(f, "%d %s %s", idx->num, idx->titre, idx->auteur);
        if (idx->suiv){
            fprintf(f, "\n");
        }

        idx = idx->suiv;
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

    printf("Livre %d : Titre : %s Auteur : %s\n", l->num, l->titre, l->auteur);

    return;
}

/* Afficher une liste chainee de livres */
void auxAfficherListeLivres(Livre* l){
    if (!l) return;

    Livre* idx = l;
    
    while (idx){
        afficher_livre(idx);
        idx = idx->suiv;
    }

    return;
}

// Affichage bibliotheque
void afficher_biblio(Biblio* b){ 
    if (!b) {
        fprintf(stderr, "La bibliothèque n'existe pas\n");
        return;
    }

    if (!b->L){
        printf("La bibliotheque ne contient pas de livres\n");
    }

    printf("Bibliotheque :\n\n");

    auxAfficherListeLivres(b->L);

    return;

}

// Recherche par numéro
Livre* recherche_numero(Biblio* b, int num){
    if (!b) {
        fprintf(stderr, "La bibliotheque en parametre n'existe pas\n");
        return NULL;
    }

    Livre* idx = b->L; 

    while(idx){
        if (idx->num == num) return idx;
        idx = idx->suiv;
    }

    return NULL;
}

// Recherche titre
Livre* recherche_titre(Biblio* b, char* titre){
    if (!b) {
        fprintf(stderr, "La bibliotheque en parametre n'existe pas\n");
        return NULL;
    }

    Livre* idx = b->L;

    /* Cas 1: Librarie vide*/
    if (!idx) return NULL;

    while (idx) {
        if (strcmp(idx->titre, titre) == 0) return idx;
        idx = idx->suiv;
    }

    
    return NULL;
}

// Recherche un livre par auteur
Biblio* recherche_auteur(Biblio* b, char* auteur){

    if (!b || !auteur){
        fprintf(stderr, "Erreur dans les parametres\n");
        return b;
    }

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

    if (!b->L){
        printf("Le livre n'est pas dans la bibliotheque\n");
    }

    return newBiblio;

}

// Supprime un ouvrage dans bibliotheque
void suppresion_ouvrage(Biblio* b, int num, char* titre, char* auteur){
    if (!b || !titre || !auteur) {
        fprintf(stderr, "Erreur dans les parametres\n");
        return;
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
            return;
        }

        previousNode = currentNode;
        currentNode = currentNode->suiv;
    }

    if (!currentNode) fprintf(stderr, "Le livre n'a pas ete trouve dans la librarie\n");
}

// Fusion de deux bibliotheques
void fusion_bibliotheques(Biblio* b1, Biblio* b2){
    if (!b1 && !b2){
        fprintf(stderr, "Erreur dans les parametres\n");
        return;
    }

    Livre* idx = b1->L;
    int num = 0;

    if (!idx) {
        b1->L = b2->L;        
    } else {
        while (idx->suiv) {
            idx = idx->suiv;
            num++;
        } 

        idx->suiv = b2->L;
        idx = idx->suiv;
    }

    while (idx){
        idx->num = (num + 1);
        num++;
        idx = idx->suiv;
    }

    free(b2);
    return;
}

Livre* recherche_multiple(Biblio* b){
    if (!b) {
        fprintf(stderr, "Erreur dans les parametres\n");
        return NULL;
    }

    Livre* lcourant = b->L;
    Livre* res = NULL;
    Livre* tmp = NULL;
    Livre* head = NULL;
    Livre* tail = NULL;

    /* Traitement de chaque livre dans la liste */
    while (lcourant){

        auxRechercheAll(b->L, lcourant, &head, &tail);

        if (head){
            if (!res){
                res = head;
                tmp = tail;
            } else {
                tmp->suiv = head;
                tmp = tail;
            }
        }

        head = NULL;
        tail = NULL;
        lcourant = lcourant->suiv;

    }

    return res;

}


void auxRechercheAll(Livre* l, Livre* lcourant, Livre** head, Livre** tail){
    /*
    @brief Fonction auxiliaire qui trouve tous les livres avec meme titre et auteur mais numero different
    si la fonction trouve de duplicatas enregistre le livre courant dans le param head et ajoute a la liste
    tous les elements trouves.
    */
    
    if (!l || !lcourant){
        return;
    }

    while (l){
        if ((lcourant->num != l->num) && (strcmp(lcourant->titre, l->titre) == 0) && (strcmp(lcourant->auteur, l->auteur) == 0)){
            if (!*head){
                *head = creer_livre(lcourant->num, lcourant->titre, lcourant->auteur);
                *tail = *head;
            } else {
                (*tail)->suiv = creer_livre(l->num, l->titre, l->auteur);
                *tail = (*tail)->suiv;
            }

        }

        l = l->suiv;
    }
}

void executionRecherche(Biblio* b, int ite, int num, char* titre, char* auteur){

    printf("Temps d'execution - Listes chainees\n\n");

    printf("Nombre d'iterations : %d\n\n", ite);

    double time = 0.0;
    double sum = 0.0;
    double* array = newArray(ite);

    /* Recherche par numero */
    for (int i=0; i < ite; i++){
        benchmark(&time);
        recherche_numero(b, num);
        benchmark(&time);
        
        sum += time;
        array[i] = time;

        time = 0.0;
    }

    qsort(array, ite, sizeof(double), comparaisonDouble);
    printf("recherche_numero\nITR: %d\nMOY: %lf\nMED: %lf\n\n", ite, (sum / ite), mediane(array, ite));

    /* Recherche par titre */
    for (int i=0; i < ite; i++){
        benchmark(&time);
        recherche_titre(b, titre);
        benchmark(&time);
        
        sum += time;
        array[i] = time;

        time = 0.0;
    }

    qsort(array, ite, sizeof(double), comparaisonDouble);
    printf("recherche_titre\nITR: %d\nMOY: %lf\nMED: %lf\n\n", ite, (sum / ite), mediane(array, ite));

    /* Recherche auteur */
    for (int i=0; i < ite; i++){
        benchmark(&time);
        recherche_auteur(b, auteur);
        benchmark(&time);
        
        sum += time;
        array[i] = time;

        time = 0.0;
    }

    qsort(array, ite, sizeof(double), comparaisonDouble);
    printf("recherche_auteur\nITR: %d\nMOY: %lf\nMED: %lf\n\n", ite, (sum / ite), mediane(array, ite));

    
    free(array);
}

void executionRechercheMultiple(char* nomfic){

    Biblio* b = NULL;
    Livre* l = NULL;
    double time = 0.0;
    int ite = 0;
    int n = 1000;

    FILE* f = fopen("rechercheMultiplesLC.txt", "w");
    if (!f){
        fprintf(stderr, "Erreur dans l'ouverture d'un fichier\n");
        return;
    }

    fprintf(f, "n\ttime\n");

    while (n <= 50000){
        
        b = charger_n_entrees(nomfic, n);
        if (!b){
            fprintf(stderr, "Erreur dans le chargement de %d entrees", n);
            fclose(f);
            return;
        }

        benchmark(&time);
        l = recherche_multiple(b);
        benchmark(&time);

        fprintf(f, "%d\t%lf", n, time);
        if ((n + 2500) < 50000){
            fprintf(f, "\n");
        }


        liberer_biblio(b);
        auxLibererListeLivres(l);

        time = 0.0;
        ite++;
        printf("ITE: %d\n", ite);
        n += 2500;
    }

    printf("Execution reussie, %d iterations\n", ite);

    fclose(f);
    return;
}