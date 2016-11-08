#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Fonction qui parse le fichier pour renvoyé le tableau des probabilités associées aux noeuds 
Remarque : On suppose que le fichier est au format adapté i.e ("o_1, o_2, ... , o_n")
Pas de controle de format. */
double* parser_fichier(int n, FILE* f);

/* Fonction qui renvoie la profondeur moyenne optimale d'un arbre et stocke l'indice des racines optimales calclées dans un tableau*/
double f(int i, int j, int n, double probabilites[], double **sommes_ij, double **res_opt, int **racines);

/* Fonction qui crée un arbre optimal à l'aide du tableau des racines */
void abr_opt(int i, int j, int n, int *racines, int (*abr)[2]);

/* Affiche un arbre */
void affiche_abr(int n, int (*abr)[2], int *racines);

#endif
