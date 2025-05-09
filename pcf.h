#ifndef PCF_H
#define PCF_H

#include <gmp.h>
#include <stdbool.h>

typedef struct quadratic *quadratic;
struct quadratic {
  mpz_t A;
  mpz_t B;
};
extern mpz_t C; /* The corresponding C value */
extern mpz_t D; /* Reduced discriminant */

typedef struct convergent *convergent;
struct convergent{
  mpz_t h[2];
  mpz_t k[2];
};

void init_mpzQ(quadratic q);
void clear_mpzQ(quadratic q);

void getC(quadratic q);
void floorx(mpz_t p, quadratic q);
void discriminant(quadratic q);

unsigned long int Floyd(quadratic q, bool show);
unsigned long int Galois(quadratic q, bool show);
unsigned long int Cycle(quadratic h, bool show);

void initConvergent(convergent f);
void addConvergent(convergent f, mpz_t p);
void EulersQ(convergent f, quadratic q);

void move(quadratic q, mpz_t p);
void unmove(quadratic q, mpz_t a);

void gprint(quadratic q);

#endif /* PCF_H */
