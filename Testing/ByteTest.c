#include <stdio.h>
#include <math.h>

#define N 8 //toto treba zmenit na velkost slova

int BitCounter(char slovo) {
  int sum = 0;
  char b_jedna = 1;

  for(int i = 1; i < N; i++) {
    if(slovo & b_jedna)
      sum++;
    slovo >>= 1;
  }

  return sum;
}

int main() {
  
  int I = 1;
  char C = '1'; //0011 0001 pre nas

  int velkost_int = sizeof(I), velkost_char = sizeof(C);

  printf("Byte INT: %d B\nByte CHAR: %d B\n", velkost_int, velkost_char);
  
  //Prevod na bity
  char virt_jedna = 1; //0000 0001 pre nas
  //printf("%c\n", virt_jedna);

  // 1. XOR
  char XORnute = C ^ virt_jedna;
  printf("XOR: %d (CHAR)\n", XORnute); //malo by vypisat 0011 0000 co je '0'

  // 2. 3. a 4. AND a RBS vo FOR
  //XORnute = XORnute >>= 3;
  //printf("RBS: %d (CHAR)\n", XORnute);
  /*int sum = 0;
  int sucin;
  for(int i = 1; i < N; i++) {
    //sucin = XORnute & virt_jedna;
    //printf("sucin: %d\n", sucin);
    if(XORnute & virt_jedna)
      sum++;
    XORnute = XORnute >>= 1;
  }*/
  int e_sum = BitCounter(XORnute);
  //int b_sum = BitCounter(C);
  printf("Pocet chyb: %d, %d\n", e_sum, N);

  float BER = (float)e_sum / (float)N;
  printf("BER: %.2f%%\n", BER*100);

  float log_BER = logf(BER);
  printf("log BER: %.2f\n", log_BER);

  return 0;
}

