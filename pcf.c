#define _GNU_SOURCE
#include "pcf.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <gmp.h>

mpz_t C;
mpz_t D; /* Reduced discriminant */
static mpz_t d; /* square root of D */
static mpz_t dp1; /* (square root of D) + 1 */
static mpz_t ac; /* Temporary value and AC after getC call */

static bool equals(quadratic t, quadratic h);
static void copy(quadratic qy, quadratic q);

void init_mpzQ(quadratic q)
{
  mpz_inits(q->A, q->B, C, D, dp1, ac, NULL);
}

void clear_mpzQ(quadratic q)
{
  mpz_clears(q->A, q->B, C, D, dp1, ac, NULL);
}

void getC(quadratic q)
{ /* Needs A, B and D */
  mpz_mul(ac, q->B, q->B);
  mpz_sub(ac, ac, D);

  assert(mpz_divisible_p(ac, q->A) && "Invalid config");
  mpz_divexact(C, ac, q->A);
}

void floorx(mpz_t p, quadratic q)
{ /* Set p to the integer part of x */
  mpz_t *rd = &d; /* use floor */
  if(-1 == mpz_sgn(q->A)) rd = &dp1; /* use ceilling */
  mpz_sub(p, *rd, q->B);
  mpz_fdiv_q(p, p, q->A);
  assert(1 == mpz_sgn(p) && "Invalid integer part");
}

void move(quadratic q, mpz_t p)
{
  floorx(p, q);
  /* get B' */
  mpz_addmul(q->B, q->A, p);
  mpz_neg(q->B, q->B);
  /* get A' */
  getC(q); /* -A' */
  mpz_neg(q->A, C);
}

bool equals(quadratic t, quadratic h)
{
  if(0 != mpz_cmp(h->A, t->A)) return false;
  if(0 != mpz_cmp(h->B, t->B)) return false;
  return true;
}

void copy(quadratic qy, quadratic q)
{
  mpz_set(qy->A, q->A);
  mpz_set(qy->B, q->B);
}

void discriminant(quadratic q)
{
  mpz_mul(D, q->B, q->B); /* B^2 */
  mpz_submul(D, q->A, C); /* B^2 - AC */

  assert(1 == mpz_sgn(D) && "No real solutions.");

  mpz_sqrt(d, D);
  mpz_add_ui(dp1, d, 1);
}

unsigned long int Floyd(quadratic q, bool show)
{ /* Run Floyd's algorithm */
  unsigned long int m = 0;
  struct quadratic h, t; /* hare and turtle */
  mpz_t p; /* integer parts */

  mpz_inits(h.A, h.B, t.A, t.B, p, NULL);
  copy(&t, q); copy(&h, q);

  do{
    move(&t, p); /* Turtle moves once */
    move(&h, p); move(&h, p); /* Hare moves twice */
  }while(!equals(&t, &h)); /* Found cycle */

  copy(&h, q); /* Hare traces prefix */
  while(!equals(&t, &h)){
    m++;
    move(&t, p); /* Turtle moves once */
    move(&h, p); /* Hare moves once */
    if(show) gmp_printf("%Zd ", p);
  }

  copy(q, &h); /* Copy information to caller */
  mpz_clears(h.A, h.B, t.A, t.B, p, NULL);

  return m;
}

unsigned long int Galois(quadratic q, bool show)
{ /* Run Galois's criteria */
  unsigned long int m = 0;
  mpz_t e; /* integer parts and temporary */

  mpz_init(e);
  while(true){ /* Ends in break */
    if(1 == mpz_sgn(q->A)){
      getC(q);
      if(-1 == mpz_sgn(C)){
	mpz_mul_si(e, q->B, -2);
	mpz_add(e, e, q->A);
	mpz_add(e, e, C);
	if(1 == mpz_sgn(e)) break; /* Found */
      }
    }

    m++;
    move(q, e);
    if(show) gmp_printf("%Zd ", e);
  }

  mpz_clear(e);

  return m;
}

unsigned long int Cycle(quadratic h, bool show)
{
  struct quadratic t; /* turtle */
  unsigned long int n = 0;
  mpz_t p; /* integer parts */

  mpz_inits(t.A, t.B, p, NULL);
  copy(&t, h); /* Hare traces prefix */

  do{ /* Hare traces cycle */
    n++;
    move(h, p); /* Hare moves once */
    if(show) gmp_printf("%Zd ", p);
  }while(!equals(&t, h));

  mpz_clears(t.A, t.B, p, NULL);

  return n;
}

void initConvergent(convergent f)
{
  mpz_inits(f->h[0], f->h[1], f->k[0], f->k[1], NULL);
  mpz_set_ui(f->h[0], 1);
  mpz_set_ui(f->k[1], 1);
}

void addConvergent(convergent f, mpz_t p)
{
  mpz_addmul(f->h[1], f->h[0], p);
  mpz_swap(f->h[0], f->h[1]);
  mpz_addmul(f->k[1], f->k[0], p);
  mpz_swap(f->k[0], f->k[1]);
}

void EulersQ(convergent f, quadratic q)
{
  mpz_t g; /* Greatest common divisor */

  mpz_set(q->A, f->k[0]);
  mpz_mul_ui(q->A, q->A, 2);
  mpz_sub(q->B, f->k[1], f->h[0]);
  mpz_neg(C, f->h[1]);
  mpz_mul_ui(C, C, 2);

  mpz_init(g);

  mpz_gcd(g, q->A, q->B); /* CGD simplify */
  mpz_gcd(g, g, C);
  mpz_divexact(q->A, q->A, g);
  mpz_divexact(q->B, q->B, g);
  mpz_divexact(C, C, g);

  mpz_clear(g);

  discriminant(q); /* To get D value */
}

void unmove(quadratic q, mpz_t a)
{
  getC(q);
  mpz_submul(q->B, C, a);
  mpz_neg(q->B, q->B); /* got B */
  mpz_neg(q->A, C); /* got A = -C' */
}
