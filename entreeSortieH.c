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

    FILE* f = fopen(nomfic, "w");
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

    printf("Livre %d : Titre : %s Auteur : %s\n", l->num, l->titre, l->auteur);

    return;
}

void auxAfficherListeLivres(LivreH* l){
    if (!l) return;
    
    LivreH* idx = l;

    while (idx) {
        afficher_livre(idx);
        idx = idx->suivant;
    }

    return;

}

// Affichage bibliotheque
void afficher_biblio(BiblioH* b){ 
    if (!b) {
        fprintf(stderr, "La bibliothèque n'existe pas\n");
        return;
    }

    LivreH** cases = b->T;

    printf("Bibliotheque :\n\n");

    for (int i = 0; i < (b->m); i++){
        auxAfficherListeLivres(cases[i]);
    }

    return;

}

// Recherche par numéro (pas plus rapide car hachage ne se fait qu'avec la cle qui depend de l'auteur)
LivreH* recherche_numero(BiblioH* b, int num){
    if (!b) {
        fprintf(stderr, "La bibliotheque en parametre n'existe pas\n");
        return NULL;
    }

    LivreH** cases = b->T;
    LivreH* idx = NULL;

    for (int i = 0; i < (b->m); i++){
        idx = cases[i];
        while (idx){
            if (idx->num == num) return idx;
            idx = idx->suivant;

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

    LivreH** cases = b->T;
    LivreH* idx = NULL;

    for (int i = 0; i < (b->m); i++){
        idx = cases[i];
        while(idx){
            if (strcmp(idx->titre, titre) == 0) return idx;
            idx = idx->suivant;
        }
    }

    return NULL;
}

// Recherche un livre par auteur (plus rapide que pour une bibliotheque en liste chainee car cle de hachage definie a partir de l'auteur)
LivreH* recherche_auteur(BiblioH* b, char* auteur){
    if (!b || !auteur){
        fprintf(stderr, "Erreur dans les parametres\n");
        return NULL;
    }   

    LivreH* res = NULL;
    LivreH* head = NULL;

    int h = fonctionHachage(fonctionClef(auteur), b->m);
    LivreH* curr = b->T[h];

    while (curr){
        if (strcmp(auteur, curr->auteur) == 0){
            // Create a new LivreH node
            LivreH* newLivre = creer_livre(curr->num, curr->titre, auteur);
            
            // If head is null, assign the first result
            if (!head){
                head = newLivre;
                res = head;
            } else {
                res->suivant = newLivre; // Link the current node
                res = res->suivant;      // Move res to the next node
            }
        }
        curr = curr->suivant;
    }
    
    return head;
}


// Supprime un ouvrage dans bibliotheque
BiblioH* suppresion_ouvrage(BiblioH * b, int num, char* titre, char* auteur){
    if (!b || !titre || !auteur) {
        fprintf(stderr, "Erreur dans les parametres\n");
        return NULL;
    }

    int h = fonctionHachage(fonctionClef(auteur), b->m);

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

    if (!currentNode) fprintf(stderr, "Le livre n'a pas ete trouve dans la bibliotheque\n");

    return b;
}

void fusion_bibliotheques(BiblioH* b1, BiblioH* b2){
    /* On suppose que les deux bibliotheques utilisent la meme fonction de hachage */
    if (!b1 && !b2){
        fprintf(stderr, "Erreur dans les parametres\n");
        return;
    }

    LivreH** casesb2 = b2->T;
    LivreH* idx = NULL;

    for (int i = 0; i < (b2->m); i++){
        idx = casesb2[i];
        while (idx){
            inserer(b1, b1->nE, idx->titre, idx->auteur);
            idx = idx->suivant;
        }
    }

    liberer_biblio(b2);

    return;
}

/* 

Dans le cas des tables de hachage, pour pouvoir garantir la fusion meme avec une taille different
et pouvoir avoir un numero unique pour chaque livre il faut ajouter a nouveau chaque element dans la table
en tout cas on a fait cette implementation similaire aux listes chainees


// Fusion de deux bibliotheques
BiblioH* fusion_bibliotheques(BiblioH* b1, BiblioH* b2){
    //on suppose que les deux bibliotheques dependent de la meme fonction de hachage et ont la meme taille b->m
    if (!b1 && !b2) {
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

*/

LivreH* recherche_multiple(BiblioH* b){
    if (!b || !(b->T)) {
        fprintf(stderr, "Erreur dans les parametres\n");
        return NULL;
    }

    LivreH** cases = b->T;

    LivreH* curr = NULL;
    LivreH* res = NULL;
    LivreH* tmp = NULL;
    LivreH* head = NULL;
    LivreH* tail = NULL;

    for (int i=0; i < (b->m); i++){

        curr = cases[i];

        auxRechercheAll(curr, &head, &tail);

        if (head){
            if (!res){
                res = head;
                tmp = tail;
            } else {
                tmp->suivant = head;
                tmp = tail;
            }
        }

        head = NULL;
        tail = NULL;
    }

    return res;
}

void auxRechercheAll(LivreH* lcourant, LivreH** head, LivreH** tail){
    if (!lcourant) return;

    LivreH* idx = lcourant;

    *head = NULL;
    *tail = NULL;

    while (idx) {
        if ((lcourant->num != idx->num) && (strcmp(lcourant->titre, idx->titre) == 0) && (strcmp(lcourant->auteur, idx->auteur) == 0)) {
            if (!(*head)){
                *head = creer_livre(idx->num, idx->titre, idx->auteur);
                *tail = *head;
            } else {
                (*tail)->suivant = creer_livre(idx->num, idx->titre, idx->auteur);
                *tail = (*tail)->suivant;                
            }
        }

        idx = idx->suivant;
    }
}


// Fonctions de benchmarking


void executionRecherche(BiblioH* b, int ite, int num, char* titre, char* auteur){

    printf("Temps d'execution - Tables de hachage\n\n");

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

    BiblioH* b = NULL;
    LivreH* l = NULL;
    double time = 0.0;
    int ite = 0;
    int n = 1000;

    FILE* f = fopen("rechercheMultiplesH.txt", "w");
    if (!f){
        fprintf(stderr, "Erreur dans l'ouverture d'un fichier\n");
        return;
    }

    fprintf(f, "time\tn\n");

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

        fprintf(f, "%lf\t%d", time, n);
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