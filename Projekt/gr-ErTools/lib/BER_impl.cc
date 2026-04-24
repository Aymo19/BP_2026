/*
 * Copyright 2025 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "BER_impl.h"
#include <gnuradio/io_signature.h>

// Pridane kniznice
#include <cmath>
#include <random>
#include <complex>
#include <algorithm>

namespace gr {
namespace ErTools {

using output_type = float;

BER::sptr BER::make(int N, int M) {
  return gnuradio::make_block_sptr<BER_impl>(N, M);
}

// Input vector
static int is[] = { sizeof(int), sizeof(unsigned char), sizeof(unsigned char) };
static std::vector<int> isig(is, is + sizeof(is) / sizeof(int));

// The private constructor
BER_impl::BER_impl(int N, int M)
    : gr::sync_block("BER",
                     gr::io_signature::makev(2, 3, isig),
                     gr::io_signature::make(1, 1, sizeof(output_type)))
{
  _N = N; // Pocet vzoriek EbN0 (kolko bodov na X-osi)
  _M = M;

  k = std::log2(M);

  p = 0;

  // Vektory
  _count = std::vector<int>(N, k);          // Celkovy pocet bitov co sme spracovali
  _pocet_chyb = std::vector<int>(N, 0);     // Celkovy pocet zistenych chyb
  _pamat_BER = std::vector<double>(N, 1.0); // Vystupne hodnoty BER

  counter = 0;
}

//Our virtual destructor.
BER_impl::~BER_impl() {}

//----------------------------------------------------LOGIKA-FUNKCIE--------------------------------------------------------||

//-------------------Zisti-kolko-chyb-je-v-slove---------------------| prerobim este
int BitCounter(unsigned char slovo, int n) {
  int sum = 0;
  unsigned char b_jedna = 1;
  
  // Pracuje sa cisto s kladnými hodnotami, lebo GR dátový typ Byte je totožný s unsigned char v C++  
  for(int i = 0; i < n; i++) {
    if(slovo & b_jedna)
      sum++;

    slovo >>= 1;
  }

  return sum;
}


//-------------------Zisti-ci-nastala-chyba---------------------|
int BER_calc(unsigned char S1, unsigned char S2, int k) {
  unsigned char XORnute;
  int e_sum;
  
  // XOR-neme slovo zo signalu 1 a slovo zo signalu 2, vieme ze je chyba, ale nevieme kde a kolko chyb
  XORnute = S1 ^ S2;
  
  // Ak hej, tak nie je nulova hodnota e_sum
  e_sum = BitCounter(XORnute, k);
  
  return e_sum;
}

//-------------------------------------------------------------------------------------------------------------------------||
//---------------------------------------------------------WORK------------------------------------------------------------||

int BER_impl::work(int noutput_items,
                   gr_vector_const_void_star& input_items,
                   gr_vector_void_star& output_items)
{
    
    //-----------------------Inicializacia-I/O--------------------------|
    // INPUT
    int *in0 = (int *)input_items[0];
    unsigned char *in1 = (unsigned char *)input_items[1];
    unsigned char *in2 = (unsigned char *)input_items[2];
    
    // OUTPUT
    auto out = static_cast<output_type*>(output_items[0]);

    //-----------------------LOGIKA--------------------------|
    //-------------------Prvotne-vypocty---------------------|
    
    //-----------------------Prejdeme-vsetkymi-I/O-items--------------------------|
    //GR_LOG_INFO(d_logger, "index: " + std::to_string(in0[0]));
    //GR_LOG_INFO(d_logger, "Singal: " + std::to_string(in1[0]));
    //GR_LOG_INFO(d_logger, "AWGN: " + std::to_string(in2[0]));
    for(int i = 0; i < noutput_items; i++) {
      index = in0[i];
      
      // Zistime, ci nastala chyba v slove
      _pocet_chyb.at(index) += BER_calc(in1[i], in2[i], k);
      
      // Nastavenia pre logaritmus v pripade ze nenastala chyba
      // GR nedokaze zobrazit v QT GUI nekonecna
      if(_pocet_chyb.at(index) == 0) {
        _pamat_BER.at(index) = 0;
      }else {
        _pamat_BER.at(index) = double(_pocet_chyb.at(index)) / double(_count.at(index));
      }

      // Float vystup = pravdepodobnost chyby na bit v danom Eb/N0
      out[i] = _pamat_BER.at(index);
      
      //GR_LOG_INFO(d_logger, "INDEX--------------------: " + std::to_string(index));
      //GR_LOG_INFO(d_logger, "BER: " + std::to_string(_pamat_BER.at(index)));
      //GR_LOG_INFO(d_logger, "ERR: " + std::to_string(_pocet_chyb.at(index)));
      //GR_LOG_INFO(d_logger, "COUNT: " + std::to_string(_count.at(index)));
      // Inkrementujeme celkovy pocet bitov
      _count.at(index) += k;

      if(counter < 4) {
        counter++;
      }else{
        if(p < _N-1){
          p++;
        }else{
          p = 0;
        }
        counter = 0;
      }
    }
    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace ErTools */
} /* namespace gr */
