#include <cmath>
#include <iostream>
#include <random>
#include <string>
 
int main() {
 
  std::default_random_engine gen;
  std::normal_distribution<double> gaussian{0, 0.5};
  
  double number;
  
  for(int i = 0; i < 10; i++)
    printf("%lf\n", gaussian(gen));
  
}
