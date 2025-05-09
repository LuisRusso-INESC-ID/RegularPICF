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
#include <time.h>

void gprint(quadratic q)
{
  getC(q);
  gmp_printf("%Zd x^2 %+Zd * 2x %+Zd\t", q->A, q->B, C);
  putchar('\n');
}

int main(int argc, char **argv) {
  bool GaloisT = false; /* Use Galois's criteria */
  bool numeric = false; /* Show sizes instead of actual cycles */
  bool useD=false; /* Use D instead of C */
  bool timer=false; /* Run for at least 5 seconds. */

  int c;
  char *line = NULL;
  size_t len = 0;
  bool cleanQ=false; /* No need to clean-up at first */
  struct quadratic q;
  mpz_t p; /* For reading input */
  int n;
  int m;
  struct convergent f;

  while ((c = getopt (argc, argv, "nt")) != -1)
    switch (c)
      {
      case 'n':
	numeric = true;
        break;
      case 't':
	timer = true;
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

  clock_t start = clock();
  clock_t end = clock();
  unsigned long long int count = 0;

  mpz_t px, py; /* Pell's calculation */

  c = getchar();
  switch(c){
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough="
  case 'H': case 'D': useD = true;
  case 'G': if (c != 'D') GaloisT = true;
#pragma GCC diagnostic pop
  case 'F': /* Cycle */
    getline(&line, &len, stdin);
    char *pA = strtok(line, " \t\n");
    char *pB = strtok(NULL, " \t\n");
    char *pC;
    char *pD;
    if(useD)
      pD = strtok(NULL, " \t\n");
    else
      pC = strtok(NULL, " \t\n");

    do {
      count++;
      if(cleanQ) clear_mpzQ(&q);

      init_mpzQ(&q);
      mpz_set_str(q.A, pA, 10);
      mpz_set_str(q.B, pB, 10);
      if(useD){
	mpz_set_str(D, pD, 10);
	getC(&q);
      } else
	mpz_set_str(C, pC, 10);

      discriminant(&q);
      if(GaloisT)
	m = Galois(&q, !numeric);
      else
	m = Floyd(&q, !numeric);

      end = clock();
      cleanQ=true;
    } while(timer && 5.0*CLOCKS_PER_SEC >= (float)(end - start));

    if(numeric){
      if(timer) printf("%llu ", count);
      printf("%d\n", m);
    } else {
      printf("( ");
      n = Cycle(&q, !numeric);
      printf(")\n");
    }

    clear_mpzQ(&q);
    free(line);
    break; /* Quadratic equation */

  case 'B':
    initConvergent(&f);
    init_mpzQ(&q);
    mpz_init(p);
    getline(&line, &len, stdin);
    sscanf(strtok(line, " \t\n") ,"%d", &n);
    while(0 < n){
      mpz_set_str(p, strtok(NULL, " \t\n"), 10);
      addConvergent(&f, p);
      n--;
    }

    EulersQ(&f, &q);

    sscanf(strtok(NULL, " \t\n") ,"%d", &m);
    while(0 < m){
      mpz_set_str(p, strtok(NULL, " \t\n"), 10);
      unmove(&q, p);
      m--;
    }
    free(line);
    gprint(&q);

    clear_mpzQ(&q);
    mpz_clears(p, f.h[0], f.h[1], f.k[0], f.k[1], NULL);
    break; /* Convergent build */

  case 'P':
    init_mpzQ(&q);
    mpz_inits(p, px, py, NULL);
    mpz_set_ui(q.A, 1);
    getline(&line, &len, stdin);
    mpz_set_str(D, strtok(line, " \t\n"), 10);
    free(line);
    getC(&q);
    discriminant(&q); /* To get d value */

    initConvergent(&f);
    floorx(p, &q);

    do{
      floorx(p, &q);
      addConvergent(&f, p);
      move(&q, p);
      mpz_mul(px, f.h[0], f.h[0]);
      mpz_mul(py, f.k[0], f.k[0]);
      mpz_submul(px, D, py);
    }while(0 != mpz_cmp_ui(px, 1));

    gmp_printf("%Zd^2 - %Zd * %Zd^2 = 1\n", f.h[0], D, f.k[0]);

    clear_mpzQ(&q);
    mpz_clears(p, px, py,
	       f.h[0], f.h[1], f.k[0], f.k[1], NULL);

    break; /* Pell's equation */
  }

  return 0;
}
