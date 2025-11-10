#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <complex>
int main() {

  std::default_random_engine R;
  std::default_random_engine I;
  std::normal_distribution<double> gaussian{0, 0.5};
  
  double nR, nI;
  std::complex<double> z;

  for(int i = 0; i < 10; i++) {
    printf("%lf\n", gaussian(R));
    /*nR = gaussian(R);
    nI = gaussian(I);
    printf("R: %lf\tI: %lf\n", nR, nI);
    std::complex<double> z1(nR,nI);
    std::cout << z1;
    printf("\n");*/
  }

  /*std::complex<double> z = 1 + 2i;
  std::cout << std::pow(std::abs(z), 2);
  printf("\n");*/
}
