#include <stdbool.h> 
#include "fonctions.h"

/**
 * parser_fichier
 * \brief Read file fonctions.h
 * \param n  The number of numbers to read in the file f
 * \param f  File to read 
 * \warning Must be called with f != NULL
 * \returns { a table of where the probabilities of each element are registered }
 */
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
    for (int i=0; i<n; i++) {
        p[i] = p[i] / (double) somme;
    }
    return p;
}

/**
 * f
 * \brief Read file fonctions.h
 * \param i  The first element of the roots (from i to j)
 * \param j  The last element of the (from i to j)
 * \param n  The number of elements in the BST
 * \param probabilites  The table of probabilities of each element
 * \param sommes_ij  Table of the sums of probabilities, from i to j 
 * \param res_opt  Table of the last results of f : You read and write in this table
 * \param racines  Table where you register the roots of the BST
 * \returns { the average depth of the BST }
 */
double f(int i, int j, int n, double probabilites[], double **sommes_ij, double **res_opt, int **racines) {
    if (j < i) {
        return 0;
   } else if (i == j) {
	(*racines) [i*n + j] = i;
	(*res_opt) [i*n + j] = probabilites[i];
	return probabilites[i];

    } else if ((*res_opt)[i*n + j] != 0) {
	return (*res_opt)[i*n + j];
    } else {
        double min = -1;
        double s = 0;
        int indice;
	if ((*sommes_ij)[i*n + j] != 0) {
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
        }
	(*res_opt) [i*n + j] = min;
	(*racines) [i*n + j] = indice;
        return min;
    }
}


/**
 * abr_opt
 * \brief Read file fonctions.h
 * \param i  The first element of the roots (from i to j)
 * \param j  The last element of the (from i to j)
 * \param n  The number of elements in the BST
 * \param racines  Table where you register the roots of the BST
 * \param abr  The BST
 * \returns { void }
 */
void abr_opt(int i, int j, int n, int *racines, int (*abr)[2]) {
    int r = racines[i*n + j];
    if (r==-1) return;
    if (i <= r-1) {
        (abr)[r][0] = racines[i*n + r-1]; // Fils gauche
	abr_opt(i, r-1, n, racines, abr);
    }

    if (r+1 <= j) {
        (abr)[r][1] = racines[(r+1)*n + j]; // Fils droite
	abr_opt(r+1, j, n, racines, abr);
    }
}

/**
 * abr_opt
 * \brief Read file fonctions.h
 * \param n  The number of elements in the BST
 * \param abr  The BST
 * \param racines  Table where you register the roots of the BST
 * \returns { void }
 */
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
