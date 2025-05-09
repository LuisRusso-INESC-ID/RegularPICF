#define _GNU_SOURCE
#include "pcf.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <gmp.h>
#include <unistd.h>
#include <ctype.h>


void gprint(quadratic q)
{
  getC(q);
  gmp_printf("%Zd %Zd %Zd", q->A, q->B, C);
  putchar('\n');
}

int main(int argc, char **argv) {
  bool longCycleT = true;
  bool longTailT = false;
  bool randomC = false;

  int c;
  struct quadratic q;
  struct convergent f;
  int n;
  mpz_t p; /* For reading input */

  while ((c = getopt (argc, argv, "tr")) != -1)
    switch (c)
      {
      case 'r':
	longCycleT = false;
	randomC = true;
        break;
      case 't':
	longCycleT = false;
	longTailT = true;
        break;
      case '?':
	if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
	exit(1);
      default:
	exit(1);
      }

  c = getchar();

  if(longCycleT){
    unsigned long int inc = 1e3;
    for(unsigned long int i = inc; i < 50*inc; i+=inc){
      initConvergent(&f);
      init_mpzQ(&q);
      mpz_init(p);

      mpz_set_ui(p, 1);
      n=i-1;
      while(0 < n){
	addConvergent(&f, p);
	n--;
      }
      mpz_set_ui(p, 2);
      addConvergent(&f, p);

      EulersQ(&f, &q);

      printf("%lu ", i);
      putchar(c);
      putchar(' ');
      gprint(&q);

      clear_mpzQ(&q);
      mpz_clears(p, f.h[0], f.h[1], f.k[0], f.k[1], NULL);

    }
  }

  if(longTailT){
    for(unsigned long int i = 1e3; i <= 1e5; i+=1e3){
    /* for(unsigned long int i = 1; i <= 2; i++){ */
      initConvergent(&f);
      init_mpzQ(&q);
      mpz_init(p);

      mpz_set_ui(p, 2);
      addConvergent(&f, p);

      EulersQ(&f, &q);

      mpz_set_ui(p, 1);
      int m=i;
      while(0 < m){
	unmove(&q, p);
	m--;
      }

      printf("%lu ", i);
      putchar(c);
      putchar(' ');
      gprint(&q);

      clear_mpzQ(&q);
      mpz_clears(p, f.h[0], f.h[1], f.k[0], f.k[1], NULL);
    }
  }

  if(randomC){
    gmp_randstate_t state;
    gmp_randinit_default(state);
    /* mpz_t seed; */
    /* gmp_randseed(state, seed); */

    init_mpzQ(&q);

    mpz_urandomb(q.A, state, 100);
    mpz_urandomb(C, state, 100);

    

    clear_mpzQ(&q);
    return 1;
  }

  return 0;
}
