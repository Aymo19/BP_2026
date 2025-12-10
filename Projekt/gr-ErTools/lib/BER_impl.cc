/* -*- c++ -*- */
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

BER::sptr BER::make(int N) {
  return gnuradio::make_block_sptr<BER_impl>(N);
}

// Input vector
static int is[] = { sizeof(int), sizeof(unsigned char), sizeof(unsigned char) };
static std::vector<int> isig(is, is + sizeof(is) / sizeof(int));

//The private constructor
BER_impl::BER_impl(int N)
    : gr::sync_block("BER",
                     gr::io_signature::makev(2, 3, isig),
                     gr::io_signature::make(1, 1, sizeof(output_type)))
{
  _N = N; // Pocet vzoriek EbN0 (kolko bodov na X-osi)

  // Vektory
  _count = std::vector<int>(N, 1); // Celkovy pocet bitov co sme spracovali
  _pocet_chyb = std::vector<int>(N, 0); // Celkovy pocet zistenych chyb
  _pamat_SER = std::vector<double>(N, 1.0); // Vystupne hodnoty BER (ja viem, je  tam SER)
  
  /* stare pre zoznamy
  std::fill_n(_count, N, 8);
  std::fill_n(_pocet_chyb, N, 0);
  std::fill_n(_pamat_SER, N, 1.0);*/
}

//Our virtual destructor.
BER_impl::~BER_impl() {}

//----------------------------------------------------LOGIKA-FUNKCIE--------------------------------------------------------||

//-------------------Zisti-kolky-chyb-je-v-slove---------------------|
int BitCounter(unsigned char slovo, int N) {
  int sum = 0, sign = 0;
  unsigned char b_jedna = 1;
  
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


//-------------------Zisti-ci-nastala-chyba---------------------|
int BER_calc(unsigned char S1, unsigned char S2) {
  unsigned char XORnute;
  int e_sum;
  
  // Logaritmicke premenne
  float BER, log_BER;

  // XOR-neme slovo zo signalu 1 a slovo zo signalu 2, vieme ze je chyba, ale nevieme kde a kolko chyb
  XORnute = S1 ^ S2;
  
  // Ak hej, tak nie je nulova hodnota e_sum
  e_sum = BitCounter(XORnute, 1);
  
  // Logaritmicky vystup
  //log_BER = logf(e_sum);
  
  //return log_BER;*/
  
  return e_sum;
}

int BER_impl::work(int noutput_items,
                   gr_vector_const_void_star& input_items,
                   gr_vector_void_star& output_items)
{
    int *in0 = (int *)input_items[0];
    unsigned char *in1 = (unsigned char *)input_items[1];
    unsigned char *in2 = (unsigned char *)input_items[2];
    
    auto out = static_cast<output_type*>(output_items[0]);

    /*long long int pocet_chyb[_N], count[_N];
    float pamat_SER[_N];
    std::fill_n(pocet_chyb, _N, 0);
    std::fill_n(count, _N, 8);
    std::fill_n(pamat_SER, _N, 1.0);*/
    
    //velkost input vektora z AWGN kanala
    //int L = sizeof(in0) / sizeof(in1[0]);
    int k;

    for(int i = 0; i < noutput_items; i++) {
      k = in0[i];
      
      _pocet_chyb.at(k) += BER_calc(in1[i], in2[i]);
      
      //printf("%d: %lf\n", k, _pamat_SER.at(k));
      if(_pocet_chyb.at(k) == 0) {
        _pamat_SER.at(k) = 0.00000001;
      }else {
        _pamat_SER.at(k) = double(_pocet_chyb.at(k)) / double(_count.at(k));
      }

     /* if(k%10000 == 0)
        GR_LOG_INFO(d_logger, std::string("b: ") + std::to_string(in2[i]) + std::string("\n"));
      */
      out[i] = _pamat_SER.at(k);

      _count.at(k) += 1;
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace ErTools */
} /* namespace gr */
