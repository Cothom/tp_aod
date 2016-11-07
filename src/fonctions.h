#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

bool estChiffre(char c);

double* parser_fichier(int n, FILE* f);

double f(int i, int j, int n, double probabilites[], int **racines);

void abr_opt(int i, int j, int n, int *racines, int (*abr)[2]);

void affiche_abr(int n, int (*abr)[2], int *racines);

#endif
