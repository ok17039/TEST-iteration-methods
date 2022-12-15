/*
 * Projekt:
 * Autor:
 * Datum:
 */

#include "gvid.h"       // par drobnosti pro zjednoduseni prace
#include <stdio.h>
#include <stdlib.h>
// #include <string.h>  // pro praci s textovymi retezci
#include <stdbool.h> // pro praci s typem bool a konstantami true a false
// #include <ctype.h>   // isalpha, isspace, islower, isupper, ...
#include <math.h>    // funkce z matematicke knihovny
// #include <float.h>   // konstanty pro racionalni typy DBL_MAX, DBL_DIG, ...
// #include <limits.h>  // konstanty pro celociselne typy INT_MAX, INT_MIN, ...
// #include <time.h>    // funkce time a dalsi pro praci s casem


float horner(float koef[], int n, float x) {

  float sum = koef[0];

  for (int i = 1; i <= n; i++) {
    sum = sum * x + koef[i];
  }

  return sum;
}

float f1(float x) {
  float koef[] = {-5.0, 3.2, 7.5};
  return horner(koef, 2, x);
}

float f2(float x) {
  float koef[] = {1, -2, -3};
  return horner(koef, 2, x);
}

typedef float (*Func)(float);

float tetivyC (float a, float b, Func f) {
  return ( (fabs(f(a)) * b + fabs(f(b)) * a) / (fabs(f(b)) + fabs(f(a))) );
}

float bisekce(float a, float b, Func f, float eps) {
  if (a == b) return 0.0/0.0;
  // printf("f(a): %g\nf(b): %g\n\n", f(a), f(b));
  if (f(a) * f(b) > 0) return 0.0/0.0;

  float c = (a+b)/2.0;

  while (true) {
    if (b - a < eps) return c;
    if (fabs(f(c)) < eps) return c;
    c = (a+b)/2.0;

    // printf("a: %g\nb: %g\nc: %g\n\n", a, b, c);

    if (f(a) * f(c) < 0) {
      b = c;
    } else {
      a = c;
    }
  }
}

float tetivy(float a, float b, Func f, float eps) {
  if (a == b) return 0.0/0.0;
  // printf("f(a): %g\nf(b): %g\n\n", f(a), f(b));
  if (f(a) * f(b) > 0) return 0.0/0.0;

  float c = tetivyC(a, b, f);

  while (true) {
    if (b - a < eps) return c;
    if (fabs(f(c)) < eps) return c;
    c = tetivyC(a, b, f);

    // printf("a: %g\nb: %g\nc: %g\n\n", a, b, c);

    if (f(a) * f(c) < 0) {
      b = c;
    } else {
      a = c;
    }
  }
}

//int main(int argc, char *argv[])  // pro parametry prikazoveho radku
int main(void)
{
  // printf("%g\n", f2(1.0));
  printf("Bisekce: x ~= %g\n\n", bisekce(1, 2, f1, 0.00001));
  printf("Tetivy: x ~= %g\n\n", tetivy(1, 2, f1, 0.00001));

  return 0;
}
