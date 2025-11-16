#include <stdio.h>
#include <algorithm>

int BitCounter(char slovo, int N) {
  int sum = 0, sign = 0;
  char b_jedna = 1;
  
  if(slovo < 0)
    sign = 1;
  
  for(int i = 0; i < N; i++) {
    if((slovo & b_jedna) > 0)
      sum++;

    if(sign) { //ked plus
      slovo >>= 1;
    }else { //ked minus
      b_jedna <<= 1;
    }
  }

  return sum;
}

int BER_calc(char S1, char S2) {
  char XORnute;
  int e_sum;//, N_S1 = sizeof(S1) * 8; //krat 8 lebo 1 kodove slovo ma 8 bitov
  //float BER, log_BER;

  XORnute = S1 ^ S2;
  
  e_sum = BitCounter(XORnute, 8);//N_S1);
  
  /*BER = (float)e_sum / (float)N_S1;
  
  log_BER = logf(BER);

  return log_BER;*/
  
  return e_sum;
}


int main() {
  int pocet_chyb[5], count[5], N = 5;
  float pamat_SER[5];
  std::fill_n(pocet_chyb, 5, 0);
  std::fill_n(count, 5, 8);
  std::fill_n(pamat_SER, 5, 1.0);
  
  for(int i = 0; i < 5; i++) {
    pocet_chyb[i] += BER_calc('0', '3'+i);
    
    pamat_SER[i] = float(pocet_chyb[i]) / float(count[i]);

    printf("%d %d %f\n", pocet_chyb[i], count[i], pamat_SER[i]);

    count[i] += 8;
    if(i < 4) {
      i = 0;
      N--;
    }
    if(!N)
      break;
  }
  return 0;
}
