#include <math.h>
#include "prime.h"

// retorna:
// 1 para primo
// 0 se não for primo
// -1 se for indefinido (i.e, x < 2)
int is_prime(const int x) {
    if (x < 2) return -1;
    if (x < 4) return 1;
    if ((x % 2) == 0) return 0;
    for ( int i = 3; i <= floor(sqrt((double) x)); i+=2) {
        if ((x % i) == 0) return 0;
    }
    return 1;
}

// retorna o proximo primo
int next_prime(int x) {
    while (is_prime(x) != 1) x++;
    return x;
}