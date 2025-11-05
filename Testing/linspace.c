#include <stdio.h>

int main() {
  float Emin, Emax, rozpatie, rozpatiePostup;
  int N;

  printf("N Emin Emax\n");
  scanf("%d %f %f", &N, &Emin, &Emax);

  float EDB[N];

  rozpatie = (Emax - Emin) / (N-1);
  rozpatiePostup = Emin;

  for(int i = 0; i < N; i++) {
    EDB[i] = rozpatiePostup;
    printf("%.2f ", EDB[i]);
    rozpatiePostup += rozpatie;
  }
  printf("\n");

  return 0;
}
