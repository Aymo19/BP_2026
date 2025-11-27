/* -*- c++ -*- */
/*
 * Copyright 2025 Marek Hetteš.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "BER_impl.h"
#include <gnuradio/io_signature.h>

#include <cmath>
#include <random>
#include <complex>
#include <algorithm>

namespace gr {
namespace ErTools {

//using input_type = float;
using output_type = float;

BER::sptr BER::make(int N) { return gnuradio::make_block_sptr<BER_impl>(N); }

static int is[] = { sizeof(int), sizeof(unsigned char), sizeof(unsigned char) };
static std::vector<int> isig(is, is + sizeof(is) / sizeof(int));

//The private constructor
BER_impl::BER_impl(int N)
    : gr::sync_block("BER",
                     gr::io_signature::makev(2, 3, isig),
                     gr::io_signature::make(1, 1, sizeof(output_type)))
{
  _N = N;
  _count = std::vector<int>(N, 8);
  _pocet_chyb = std::vector<int>(N, 1);
  _pamat_SER = std::vector<double>(N, 1.0);
  /*
  std::fill_n(_count, N, 8);
  std::fill_n(_pocet_chyb, N, 0);
  std::fill_n(_pamat_SER, N, 1.0);*/
}

//Our virtual destructor.
BER_impl::~BER_impl() {}

//spocita vsetky chybne bity po x(t) XOR x(t)+n(t)
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

int BER_calc(unsigned char S1, unsigned char S2) {
  unsigned char XORnute;
  int e_sum;//, N_S1 = sizeof(S1) * 8; //krat 8 lebo 1 kodove slovo ma 8 bitov
  //float BER, log_BER;

  XORnute = S1 ^ S2;
  
  e_sum = BitCounter(XORnute, 8);//N_S1);
  /*BER = (float)e_sum / (float)N_S1;
  
  log_BER = logf(BER);

  return log_BER;*/
  
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
      _pamat_SER.at(k) = double(_pocet_chyb.at(k)) / double(_count.at(k));
      /*if(k%2 == 0)
        GR_LOG_INFO(d_logger, std::string("e: ") + std::to_string(_pocet_chyb.at(k)));
*/
      out[i] = _pamat_SER.at(k);

      _count.at(k) += 8;
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace ErTools */
} /* namespace gr */
