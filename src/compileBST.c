/*! \file compileBST.c
 *  \brief	   This implements the applyPatch program.
 *  \author    Lucie Pansart
 *  \author    Jean-Louis Roch
 *  \version   1.0
 *  \date      30/9/2016
 *  \warning   Usage: compileBST n originalFile 
 *  \copyright GNU Public License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <assert.h>
#include <string.h>

#include "fonctions.h"

/**
 * Main function
 * \brief Main function
 * \param argc  A count of the number of command-line arguments
 * \param argv  An argument vector of the command-line arguments.
 * \warning Must be called with a positive long integer, n,  and a filename, freqFile, as commandline parameters and in the given order.
 * \returns { 0 if succeeds and prints C code implementing an optimal ABR on stdout; exit code otherwise}
 */
int main (int argc, char *argv[]) {
    long n = 0 ; // Number of elements in the dictionary  FILE *freqFile = NULL ; // File that contains n positive integers defining the relative frequence of dictinary elements 

    if(argc != 3){
        fprintf(stderr, "!!!!! Usage: ./compileBST n  originalFile !!!!!\n");
        exit(EXIT_FAILURE); /* indicate failure.*/
    }

    { // Conversion of parameter n in a long 
        int codeRetour = EXIT_SUCCESS;
        char *posError;
        long resuLong;
        n = atol(argv[1] ) ;

        assert(argc >= 2);
        // Conversion of argv[1] en long
        resuLong = strtol(argv[1], &posError, 10);
        // Traitement des erreurs
        switch (errno)
        {
            case EXIT_SUCCESS :
                // Conversion du long en int
                if (resuLong > 0)
                {
                    n = (long)resuLong;
                    fprintf(stderr, "Number of elements in the dictionary: %ld\n", n);         
                }
                else
                {
                    (void)fprintf(stderr, "%s cannot be converted into a positive integer matching the number of elements in the dicionary.\n", argv[1]) ; 
                    codeRetour = EXIT_FAILURE;
                }
                break;

            case EINVAL :
                perror(__func__);
                (void)fprintf(stderr, "%s does not match a long integer value. \n", argv[1]);
                codeRetour = EXIT_FAILURE;
                break;

            case ERANGE :
                perror(__func__);
                (void)fprintf(stderr, "%s does not fit in a long int :\n" "out of bound [%ld;%ld]\n",
                        argv[1], LONG_MIN, LONG_MAX);
                codeRetour = EXIT_FAILURE;
                break;
            default :
                perror(__func__);
                codeRetour = EXIT_FAILURE;
        } // switch (errno)
        if  (codeRetour != EXIT_SUCCESS) return codeRetour ;
    }

    FILE* freqFile = fopen(argv[2] , "r" ); // freqFile = fopen(argv[2] , "r" );
    if (freqFile==NULL) {fprintf (stderr, "!!!!! Error opening originalFile !!!!!\n"); exit(EXIT_FAILURE);}

    // TO BE COMPLETED

    /* Debut Modification */
    double* probabilites = parser_fichier((int) n, freqFile);
    fflush(stdout);
    printf(" p2 :  ");
    for (int i=0; i<n; i++) {
       printf(" %f ", probabilites[i]);
    }
    fflush(stdout);
//    int *abr = malloc(2 * n * sizeof(int));
    int abr[n][2];
    for (int i = 0; i < n; i ++) {
        abr[i][0] = -1;
        abr[i][1] = -1;
    }
    //int racines[n][n];
    int *racines = (int *) malloc(n * n * sizeof(int));
    memset((void*) racines, -1, n * n * sizeof(int));
    /*
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j++) {
            racines[i*n + j] = -1;
        }
    } */
    double *sommes_ij = (double *) malloc(n * n * sizeof(double));
    memset((void*) sommes_ij, -1, n * n * sizeof(double));
    double sum;
    int taille = (int) n;
    for (int i=0; i<taille; i++){
	for (int j=i; j<taille; j++){
	    sum = 0;
	    for (int k=i; k<j+1; k++){
		sum += probabilites[k];
	    }
	    sommes_ij[i*n + j] = sum;
	}
    }
    double *res_opt = (double *) malloc(n * n * sizeof(double));
    memset((void*) res_opt, 0, n * n * sizeof(double));

    
    printf("\n Debut f \n");
    f(0, ((int) n) - 1, (int) n, probabilites, &sommes_ij, &res_opt, &racines);
    printf("\n Fin f \n");
    printf("\n Racines : \n");
    /*
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j++) {
            printf(" %d ", racines[i*n + j]);
        }
	printf("\n");
    }*/
    abr_opt(0, (int) n - 1, (int) n, (int*) racines, abr);
    affiche_abr((int) n, abr, racines);
    /* Fin Modification */

    fclose(freqFile);


    return 0;
}

