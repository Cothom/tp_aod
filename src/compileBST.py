#! /usr/bin/env python3

import sys
import math

def parser(filename) :
    f = open(filename, 'r');
    proba_array = f.readline().split("  ");
    proba_array = [ int(elt) for elt in proba_array ];
    sum = 0;
    for elt in proba_array :
        sum += elt;
    for i in range(len(proba_array)) :
        proba_array[i] /= sum;

    return proba_array;

def abr_opt_it(proba_array, n) :
    e = [ [ math.inf for i in range(n+1) ] for j in range(n+2) ];
    w = [ [ 0 for i in range(n+1) ] for j in range(n+1) ];
    racines = [ [ 0 for i in range(n+1) ] for j in range(n+1) ];
    e[n+1][n] = 0;
    for i in range(1, n+1) :
        e[i][i-1] = 0;
        e[i][i] = proba_array[i-1];
        w[i][i] = proba_array[i-1];

    for l in range(1, n) :
        for i in range(1, n-l+1) :
            j = i + l;
            w[i][j] = w[i][j-1] + proba_array[j-1];
            for r in range(i, j) :
                t = e[i][r-1] + e[r+1][j] + w[i][j];
                if t < e[i][j] :
                    e[i][j] = t;
                    racines[i][j] = r;

    print(proba_array);
    disp_arr_of_arr(racines);
    disp_abr(n, e);

def f(i, j, n, proba_array, racines) :
    if j < i :
        return 0;
    elif i == j :
        racines[i][j] = i
        return proba_array[i];
    else :
        mini = -1;
        s = 0;
        for a in range(i, j+1) :
            s += proba_array[a];
        for k in range(i, j+1) :
            res = f(i, k-1, n, proba_array, racines) + f(k+1, j, n, proba_array, racines);
            if mini == -1 or res + s < mini :
                mini = res + s;
                indice = k;

        racines[i][j] = indice;
        return mini;

def abr_opt(i, j, n, racines, abr) :
    r = racines[i][j];
    if i < r-1 :
        abr[r][0] = racines[i][r-1];
        abr_opt(i, r-1, n, racines, abr);
    if r+1 < j :
        abr[r][1] = racines[r][j];
        abr_opt(r+1, j, n, racines, abr);

    return 

def disp_arr_of_arr(a) :
    for x in a :
        for y in x :
            print(y, end=' ');
        print();

def disp_abr(n, abr) :
    print("{", end='');
    for i in range(n) :
        print(" {" + str(abr[i][0]) + ", " + str(abr[i][1]) + "}", end='');
        if i != n-1 :
            print(",");

    print(" }");

def main() :
    n = int(sys.argv[1]);
    filename = sys.argv[2];
    proba_array = parser(filename);

    abr = [ [-1, -1] for i in range(n) ];
    racines = [[ -1 for i in range(n) ] for j in range(n) ];

    f(0, n-1, n, proba_array, racines);
    abr_opt_it(proba_array, n);
    #disp_abr(n, abr);


main()
