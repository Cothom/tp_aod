#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool estChiffre(char c);

double* parser_fichier(int n, FILE* f);

double f(int i, int j, double probabilites[], int ***racines);

void abr_opt(int i, int j, int **racines, int ***abr);

void affiche_abr(int n, int (*)[2]abr);

#endif
