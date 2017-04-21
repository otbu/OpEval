#include "evaluate_stub01.h"

T_INT numPlaces(T_INT n) {
    if (n < 0) n = (n == T_INT_MIN) ? T_INT_MAX : -n;
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    if (n < 1000000) return 6;
    if (n < 10000000) return 7;
    if (n < 100000000) return 8;
    if (n < 1000000000) return 9;
    /*      2147483647 is 2^31-1 - add more ifs as needed
    and adjust this final return as well. */
    return 10;
}

void evaluate_trees() {

    T_INT n = 0;
    T_FLO* res = malloc(10 * sizeof(T_FLO));

    res[n++] = OP_ADD(OP_MUL(L1, OP_CON(L2, L3)), OP_MUL(OP_CON(L4, OP_CON(L5, L6)), OP_ADD(L7, OP_ADD(L8, L9))));
    res[n++] = OP_ADD(OP_MUL(L1, OP_CON(L2, L3)), OP_MUL(OP_CON(L4, OP_CON(L5, L6)), OP_ADD(L7, OP_ADD(L8, L9))));
    res[n++] = OP_ADD(OP_MUL(L1, OP_CON(L2, L3)), OP_MUL(OP_CON(L4, OP_CON(L5, L6)), OP_ADD(L7, OP_ADD(L8, L9))));
    res[n++] = OP_ADD(OP_MUL(L1, OP_CON(L2, L3)), OP_MUL(OP_CON(L4, OP_CON(L5, L6)), OP_ADD(L7, OP_ADD(L8, L9))));
    res[n++] = OP_ADD(OP_MUL(L1, OP_CON(L2, L3)), OP_MUL(OP_CON(L4, OP_CON(L5, L6)), OP_ADD(L7, OP_ADD(L8, L9))));
    res[n++] = OP_ADD(OP_MUL(L1, OP_CON(L2, L3)), OP_MUL(OP_CON(L4, OP_CON(L5, L6)), OP_ADD(L7, OP_ADD(L8, L9))));
    res[n++] = OP_ADD(OP_MUL(L1, OP_CON(L2, L3)), OP_MUL(OP_CON(L4, OP_CON(L5, L6)), OP_ADD(L7, OP_ADD(L8, L9))));
    res[n++] = OP_ADD(OP_MUL(L1, OP_CON(L2, L3)), OP_MUL(OP_CON(L4, OP_CON(L5, L6)), OP_ADD(L7, OP_ADD(L8, L9))));
    res[n++] = OP_ADD(OP_MUL(L1, OP_CON(L2, L3)), OP_MUL(OP_CON(L4, OP_CON(L5, L6)), OP_ADD(L7, OP_ADD(L8, L9))));
    res[n++] = OP_ADD(OP_MUL(L1, OP_CON(L2, L3)), OP_MUL(OP_CON(L4, OP_CON(L5, L6)), OP_ADD(L7, OP_ADD(L8, L9))));



}