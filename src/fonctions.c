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

double f(int i, int j, int n, double probabilites[], double **sommes_ij, double **res_opt, int **racines) {
    if (j < i) {
        return 0;
   } else if (i == j) {
	//(*racines)[i][j] = i;     
	//*((*racines) + i*n + j) = i;
	(*racines) [i*n + j] = i;
	(*res_opt) [i*n + j] = probabilites[i];
	return probabilites[i];

    } else if ((*res_opt)[i*n + j] != 0) {
	return (*res_opt)[i*n + j];
    } else {
        double min = -1;
        double s = 0;
        int indice;
	if ((*sommes_ij)[i*n + j] != -1) {
	    s = (*sommes_ij)[i*n + j];
	} else {
	    for (int a = i; a <= j; a++) {
		s += probabilites[a];
	    }
	    (*sommes_ij)[i*n + j] = s;
	}
	double res;
        for (int k = i; k <= j; k++) {
            res = f(i, k-1, n, probabilites, sommes_ij, res_opt, racines) + f(k+1, j, n, probabilites, sommes_ij, res_opt, racines) + s;
            if (min == -1 || res < min) {
		min = res;
                indice = k;
            }
	    //printf(" res : %f", res);
	    //printf(" s : %f", s);
        }
	(*res_opt) [i*n + j] = min;
	//*((*res_opt) + i*n + j) = min;
        //*((*racines) + i*n + j) = indice;
	(*racines) [i*n + j] = indice;
        return min;
    }
}

void abr_opt(int i, int j, int n, int *racines, int (*abr)[2]) {
    int r = racines[i*n + j];
    if (r==-1) return;
    //(*abr) [r] = -1;
    //(*abr) [r + 1] = -1;
    //printf("\n %d %d %d %d\n", r, n, i, j);
    if (i <= r-1) {
        //(*abr)[r][0] = racines[i*n + r-1]; // Fils gauche
        (abr)[r][0] = racines[i*n + r-1];
	abr_opt(i, r-1, n, racines, abr);
    }

    if (r+1 <= j) {
        //(*abr)[r][1] = racines[r*n + j]; // Fils droite
	//	printf("\n %d %d %d\n", r, n, j);
        (abr)[r][1] = racines[(r+1)*n + j];
	abr_opt(r+1, j, n, racines, abr);
    }
}

void affiche_abr(int n, int (*abr)[2], int *racines) {

    printf("static int BSTroot = %d;\n", racines[n-1]);
    printf("static int BSTtree[%d][2] = {\n", n);
    for (int i = 0; i < n; i++) {
        printf(" {%d, %d}", abr[i][0], abr[i][1]);
        if (i != n-1) {
            printf(",\n");
        }
    }
    printf(" };\n");
}
