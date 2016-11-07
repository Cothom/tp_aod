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
    char c;
    int indice = 0;
    int nombre = 0;
    int somme = 0;
    bool lectureNombre = false;
    do
        {
            c = fgetc(f);
	    while (estChiffre(c)) {
		if (!lectureNombre) {
		    nombre = atoi(&c);
		    lectureNombre = true;
		} else {
		    nombre = nombre*10 + atoi(&c);
		}
		c = fgetc(f);
	    }
	    if (lectureNombre) {
		lectureNombre = false;
		printf("Nombre : %d\n", nombre);
		p[indice] = (double) nombre;
		somme += nombre;
		indice++;
	    }
        } while (c != EOF); 
    printf("Somme : %d\n Tableau: ", somme);
 
    for (int i=0; i<n; i++) {
	printf(" %f ", p[i]);
	p[i] = p[i] / (double) somme;
    }
    for (int i=0; i<n; i++) {
	printf(" %f ", p[i]);
    }
    return p;
}
   
double f(int i, int j, double probabilites[], int ***racines) {
    if (j < i) {
	return 0;
    } else if (i == j) {
	return probabilites[i];
    } else {
	int min = -1;
	int s = 0;
	int indice;
	for (int n = i; n <= j; n++) {
	    s += probabilites[n];
	}
	for (int k = i; k <= j; k++) {
	    int res = f(i, k-1, probabilites, racines) + f(k+1, j, probabilites, racines);
	    if (min == -1 || res + s < min) {
		min = res;
		indice = k;
	    }
	}
	(*racines)[i][j] = indice;
	return min;
    }
}

void abr_opt(int i, int j, int **racines, int ***abr) {
    int r = racines[i][j];
    (*abr) [r][0] = -1;
    (*abr) [r][1] = -1;

    if (i < r-1) {
	(*abr) [r][0] = racines[i][r-1];
	abr_opt(i, r-1, racines, abr);
    }

    if (r < j) {
	(*abr) [r][1] = racines[r][j];
	abr_opt(r, j, racines, abr);
	}
}

void affiche_abr(int n, int *[2]abr) {
    printf("\n{");
    for (int i = 0; i < n; i ++) {
	printf(" {%d, %d}", abr[i][0], abr[i][1]);
	if (i != n-1) {
	    printf(",");
	}
    }
    printf(" }\n");
}
