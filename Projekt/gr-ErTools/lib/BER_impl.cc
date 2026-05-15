/*
 * Copyright 2025 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "BER_impl.h"
#include <gnuradio/io_signature.h>

// Pridane kniznice
#include <cmath>

namespace gr {
namespace ErTools {

// Typ vystupu
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
  _N = N; // Pocet bodov EbN0 v rozostupe
  _M = M; // Pocet bitov v informacnom slove

  // Vektory
  _count = std::vector<int>(N, M);          // Celkovy pocet bitov co sme spracovali
  _pocet_chyb = std::vector<int>(N, 0);     // Celkovy pocet zistenych chyb
  _pamat_BER = std::vector<double>(N, 0.0); // Vystupne hodnoty BER
}

//Our virtual destructor.
BER_impl::~BER_impl() {}

//----FUNKCIE----||

// Zisti, kolko chyb je v slove
int BitCounter(unsigned char slovo, int n) {
  int sum = 0;
  unsigned char b_jedna = 1; // Testovacia bitova jednotka
  
  // Pracuje sa cisto s kladnými hodnotami, lebo GR dátový typ Byte je totožný s unsigned char v C++  
  for(int i = 0; i < n; i++) {
    if(slovo & b_jedna)
      sum++;

    slovo >>= 1;
  }

  return sum;
}


// Zisti, ci nastala chyba
int BER_calc(unsigned char S1, unsigned char S2, int k) {
  unsigned char XORnute;
  int e_sum;
  
  // XOR-neme infomačné slovo c.1 a informacne slovo c.2, vieme ze je chyba, ale nevieme este kde a kolko chyb
  XORnute = S1 ^ S2;
  
  // Ak hej, tak nie je nulova hodnota e_sum
  e_sum = BitCounter(XORnute, k);
  
  return e_sum;
}

//----WORK----||
int BER_impl::work(int noutput_items,
                   gr_vector_const_void_star& input_items,
                   gr_vector_void_star& output_items)
{
    
    // Inicializacia I/O
    // INPUT
    int *in0 = (int *)input_items[0];
    unsigned char *in1 = (unsigned char *)input_items[1];
    unsigned char *in2 = (unsigned char *)input_items[2];
    
    // OUTPUT
    auto out = static_cast<output_type*>(output_items[0]);


    // LOGIKA
    // Prejdeme vsetkymi I/O items
    for(int i = 0; i < noutput_items; i++) {
      index = in0[i];
      
      // Zistime, ci nastala chyba v slove
      _pocet_chyb.at(index) += BER_calc(in1[i], in2[i], _M);
      
      // Vykona sa len vtedy, ak bola chyba
      if(_pocet_chyb.at(index) != 0) {
        _pamat_BER.at(index) = double(_pocet_chyb.at(index)) / double(_count.at(index));
      }

      // Float vystup = pravdepodobnost chyby na bit pre dane EbN0
      out[i] = _pamat_BER.at(index);
      
      //GR_LOG_INFO(d_logger, "COUNT: " + std::to_string(_count.at(index)));
      
      // Inkrementujeme celkovy pocet bitov na dane EbN0
      _count.at(index) += _M;
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace ErTools */
} /* namespace gr */
