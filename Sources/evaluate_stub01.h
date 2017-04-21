#ifndef EVALUATE_STUB01_H
#define EVALUATE_STUB01_H

#include <limits.h>
#include <math.h>

#include "common.h"

typedef int T_INT;
typedef double T_FLO;

#define T_INT_MIN INT_MIN
#define T_INT_MAX INT_MAX

#define MACRO_NUMPLACES_NONEGCHECK(n) \
    (((n) < 10) ? 1 : \
    (((n) < 100) ? 2 : \
    (((n) < 1000) ? 3 : \
    (((n) < 10000) ? 4 : \
    (((n) < 100000) ? 5 : \
    (((n) < 1000000) ? 6 : \
    (((n) < 10000000) ? 7 : \
    (((n) < 100000000) ? 8 : \
    (((n) < 1000000000) ? 9 : 10)))))))))

#define MACRO_NUMPLACES(n) \
    (((n) < 0) ? MACRO_NUMPLACES_NONEGCHECK((-1)*(n)) : \
    (((n) < 10) ? 1 : \
    (((n) < 100) ? 2 : \
    (((n) < 1000) ? 3 : \
    (((n) < 10000) ? 4 : \
    (((n) < 100000) ? 5 : \
    (((n) < 1000000) ? 6 : \
    (((n) < 10000000) ? 7 : \
    (((n) < 100000000) ? 8 : \
    (((n) < 1000000000) ? 9 : 10))))))))))

// http://stackoverflow.com/questions/1068849/how-do-i-determine-the-number-of-digits-of-an-integer-in-c
T_INT numPlaces(T_INT n);

// change which "numPlaces"-function is used here:
#define NUMPLACES(n) MACRO_NUMPLACES(n)

#define OP_ADD(a,b) ((a)+(b))
#define OP_SUB(a,b) ((a)-(b))
#define OP_MUL(a,b) ((a)*(b))
#define OP_CON(a,b) ((a)*pow(10,NUMPLACES((T_INT)round(b)))+(b))

#define L_INT(n) ((T_INT)(n))
#define L_FLO(n) ((T_FLO)(n))
// change type of numbers here:
#define L(n) L_FLO(n)
#define L0 L(0)
#define L1 L(1)
#define L2 L(2)
#define L3 L(3)
#define L4 L(4)
#define L5 L(5)
#define L6 L(6)
#define L7 L(7)
#define L8 L(8)
#define L9 L(9)

void evaluate_trees();

#endif /* EVALUATE_STUB01_H */