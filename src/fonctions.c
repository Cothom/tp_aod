#include <stdbool.h> 
#include "fonctions.h"

bool estChiffre(char c) {
    switch (c) {
        case '0' ... '9':
            return true;
        default :
            return false;	
    }    
}

/* Fonction qui parse le fichier pour renvoyé le tableau des probabilités associées aux noeuds 
Remarque : On suppose que le fichier est au format adapté i.e ("o_1, o_2, ... , o_n")
Pas de controle de format. */
double* parser_fichier(int n, FILE* f) {
    /*
       - requiert : f non NULL
       */

    /* Tableau des probabilites */
    double *p = malloc(n * sizeof(double));
    int c;
    int somme = 0;
    for (int i = 0; i < n; i++) {
        fscanf(f, "%d ", &c);
        p[i] = c;
        somme += c;
    }
    printf("Somme : %d\nTableau: ", somme);
    for (int i=0; i<n; i++) {
        printf(" %f ", p[i]);
        p[i] = p[i] / (double) somme;
    }
    for (int i=0; i<n; i++) {
        printf(" %f ", p[i]);
    }
    printf("\n");
    return p;
}

double f(int i, int j, int n, double probabilites[], int **racines) {
    if (j < i) {
        return 0;
    } else if (i == j) {
	//(*racines)[i][j] = i;     
	*((*racines) + i*n + j) = i;
        return probabilites[i];
    } else {
        int min = -1;
        int s = 0;
        int indice;
        for (int a = i; a <= j; a++) {
            s += probabilites[a];
        }
        for (int k = i; k <= j; k++) {
            int res = f(i, k-1, n, probabilites, racines) + f(k+1, j, n, probabilites, racines);
            if (min == -1 || res + s < min) {
                min = res + s;
                indice = k;
            }
        }
        *((*racines) + i*n + j) = indice;
        return min;
    }
}

void abr_opt(int i, int j, int n, int *racines, int ***abr) {
    int r = racines[i*n + j];
    //(*abr) [r] = -1;
    //(*abr) [r + 1] = -1;

    if (i < r-1) {
        (*abr)[r][0] = racines[i*n + r-1]; // Fils gauche
        abr_opt(i, r-1, n, racines, abr);
    }

    if (r+1 < j) {
        (*abr)[r][1] = racines[r*n + j]; // Fils droite
        abr_opt(r+1, j, n, racines, abr);
    }
}

void affiche_abr(int n, int (*abr)[2]) {
    printf("\n{");
    for (int i = 0; i < n; i++) {
        printf(" {%d, %d}", abr[i][0], abr[i][1]);
        if (i != n-1) {
            printf(",");
        }
    }
    printf(" }\n");
}
